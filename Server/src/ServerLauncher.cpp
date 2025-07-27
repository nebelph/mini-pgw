#include "ServerLauncher.h"

ServerLauncher::ServerLauncher( std::shared_ptr<UdpServer> &udp_serv, std::shared_ptr<HttpServer> &http_serv ) : m_udp_server( udp_serv ),
                                                                                                                  m_http_server( http_serv )
{
}


void ServerLauncher::launch()
{
    std::thread udp_thread( &UdpServer::run, m_udp_server.get() );
    std::thread http_thread( &HttpServer::run, m_http_server.get() );
    std::thread session_cleaner_thread( &UdpServer::cleanup_expired_sessions, m_udp_server.get() );

    udp_thread.join();
    http_thread.join();
    session_cleaner_thread.join();
}