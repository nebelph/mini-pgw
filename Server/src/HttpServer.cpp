#include "HttpServer.h"

HttpServer::HttpServer( std::shared_ptr<spdlog::logger> &pgw_logger, const std::shared_ptr<Config> &cfg, std::shared_ptr<Service> &serv ) : m_pgw_logger( pgw_logger ),
                                                                                                                                            m_cfg( cfg ),
                                                                                                                                            m_service( serv )
{
}

void HttpServer::run()
{
    post_request();
    get_request();

    m_pgw_logger->info( "HTTP server started on ip={}, port={}", m_cfg->get_http_ip(), m_cfg->get_http_port() );
    m_server.listen( m_cfg->get_http_ip(), m_cfg->get_http_port() );
}

void HttpServer::get_request()
{
    m_server.Get( "/check_subscriber", [this]( const httplib::Request &req, httplib::Response &res ) {
        m_pgw_logger->info( "Received GET-request=/check_subscriber" );
        std::string imsi = req.has_param( "imsi" ) ? req.get_param_value( "imsi" ) : "UNKNOWN";
        std::string response = m_service->is_imsi_active( imsi ) ? "active" : "not active";
        res.set_content( response, "text/plain" );
    } );
}

void HttpServer::post_request()
{
    m_server.Post( "/stop", [this]( const httplib::Request &, httplib::Response &res ) {
        m_pgw_logger->info( "Received POST-request=/stop" );
        std::thread( [this]() {
            m_service->graceful_shutdown();
            m_server.stop();
        } ).detach();
    } );
}