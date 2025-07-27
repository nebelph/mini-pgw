#include "UdpServer.h"

UdpServer::UdpServer( logger_ptr &pgw_logger, std::shared_ptr<Config> &cfg, std::shared_ptr<Service> &serv ) : m_pgw_logger( pgw_logger ),
                                                                                                               m_cfg( cfg ),
                                                                                                               m_service( serv )
{
}

UdpServer::~UdpServer()
{
    close( m_socket );
}

void UdpServer::run()
{
    m_socket = socket( AF_INET, SOCK_DGRAM, 0 );
    if ( m_socket != -1 ) {
        m_pgw_logger->debug( "UDP socket={} created.", m_socket );
    } else {
        m_pgw_logger->critical( "Can not create UDP socket!" );
        throw std::runtime_error( "socket()" );
    }

    if ( set_nonblocking( m_socket ) != -1 ) {
        m_pgw_logger->debug( "NONBLOCK flag is set." );
    } else {
        m_pgw_logger->error( "Can not set NONBLOCK flag!" );
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons( m_cfg->get_udp_port() );
    server_addr.sin_addr.s_addr = inet_addr( m_cfg->get_udp_ip().c_str() );

    if ( bind( m_socket, (sockaddr *)&server_addr, sizeof( server_addr ) ) == 0 ) {
        m_pgw_logger->info( "UDP server started on ip={}, port={}", m_cfg->get_udp_ip(), m_cfg->get_udp_port() );
    } else {
        m_pgw_logger->critical( "Can not bind UDP socket!" );
        throw std::runtime_error( "bind()" );
    }

    while ( m_service->is_running() ) {
        char buffer[BUFFER_SIZE];
        int bytes_received;
        sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof( client_addr );
        bytes_received = recvfrom( m_socket, buffer, sizeof( buffer ) - 1, 0, (sockaddr *)&client_addr, &client_addr_len );
        if ( bytes_received > 0 ) {
            buffer[bytes_received] = '\0';
            m_pgw_logger->info( "IMSI received: {}.", buffer );
        } else if ( bytes_received == -1 && ( errno == EAGAIN || errno == EWOULDBLOCK ) ) {
            std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
            continue;
        } else {
            m_pgw_logger->critical( "Can not receive IMSI!" );
            continue;
        }

        Identifier imsi( m_pgw_logger );
        if ( ! imsi.set_imsi( buffer, F_BCD ) ) {
            continue;
        }

        std::string response = m_service->add_imsi( imsi.get_ascii_imsi() ) ? "created" : "rejected";

        if ( sendto( m_socket, response.c_str(), response.size(), 0, (sockaddr *)&client_addr, client_addr_len ) != -1 ) {
            m_pgw_logger->info( "Response sent: {}.", response );
        } else {
            m_pgw_logger->critical( "Can not send response!" );
            throw std::runtime_error( "sendto()" );
        }
    }
}

void UdpServer::cleanup_expired_sessions()
{
    while ( m_service->is_running() ) {
        m_service->cleanup_expired_sessions();
        std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    }
}

int UdpServer::set_nonblocking( int fd )
{
    int flags = fcntl( fd, F_GETFL, 0 );
    if ( flags == -1 )
        return -1;
    return fcntl( fd, F_SETFL, flags | O_NONBLOCK );
}