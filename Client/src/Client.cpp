#include "Client.h"

Client::Client( std::shared_ptr<spdlog::logger> &file_logger, const std::shared_ptr<Config> &cfg ) : m_logger( file_logger ),
                                                                                                     m_cfg( cfg )
{
}

Client::~Client()
{
    close( m_socket );
}

void Client::run( const std::string &imsi )
{
    m_socket = socket( AF_INET, SOCK_DGRAM, 0 );
    if ( m_socket != -1 ) {
        m_logger->debug( "UDP socket={} created.", m_socket );
    } else {
        m_logger->critical( "Can not create UDP socket!" );
        throw std::runtime_error( "Can not create UDP socket!" );
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons( m_cfg->get_server_port() );
    inet_pton( AF_INET, m_cfg->get_server_ip().c_str(), &server_addr.sin_addr );

    if ( sendto( m_socket, imsi.c_str(), imsi.size(), 0, (sockaddr *)&server_addr, sizeof( server_addr ) ) != -1 ) {
        m_logger->info( "IMSI sent: {}.", imsi );
    } else {
        m_logger->critical( "Can not send IMSI!" );
        throw std::runtime_error( "Can not send IMSI!" );
    }

    char buffer[BUFFER_SIZE];
    int bytes_received;
    socklen_t server_addr_len = sizeof( server_addr );
    bytes_received = recvfrom( m_socket, buffer, sizeof( buffer ) - 1, 0, (sockaddr *)&server_addr, &server_addr_len );
    if ( bytes_received != -1 ) {
        buffer[bytes_received] = '\0';
        m_logger->info( "Response received: {}.", buffer );
    } else {
        m_logger->critical( "Can not receive response!" );
        throw std::runtime_error( "Can not receive response!" );
    }
}