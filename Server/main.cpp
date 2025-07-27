#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "Config.h"
#include "httplib.h"
#include "HttpServer.h"
#include "Repository.h"
#include "ServerLauncher.h"
#include "Service.h"
#include "UdpServer.h"

const std::string JSON_FILE = "cfg.json";

int main()
{
    try {
        std::shared_ptr<spdlog::logger> pgw_logger;                // pgw logger
        std::shared_ptr<spdlog::logger> cdr_logger;                // cdr logger
        std::shared_ptr<Config> cfg = std::make_shared<Config>();  // config parser
        if ( !cfg->parse( JSON_FILE ) ) {
            throw std::runtime_error( "Invalid config!" );
        }

        pgw_logger = spdlog::basic_logger_mt( "pgw_logger", cfg->get_log_file(), true );
        spdlog::set_level( cfg->get_log_level() );
        pgw_logger->flush_on( spdlog::level::info );

        pgw_logger->debug( "Config {} succesfully loaded! ", JSON_FILE );

        cdr_logger = spdlog::basic_logger_mt( "cdr_logger", cfg->get_cdr_file(), true );
        cdr_logger->flush_on( spdlog::level::info );

        std::shared_ptr<Repository> repo = std::make_shared<Repository>( pgw_logger, cdr_logger );        // session repository
        std::shared_ptr<Service> serv = std::make_shared<Service>( pgw_logger, cfg, cdr_logger, repo );   // business logic
        std::shared_ptr<UdpServer> udp_server = std::make_shared<UdpServer>( pgw_logger, cfg, serv );     // udp server
        std::shared_ptr<HttpServer> http_server = std::make_shared<HttpServer>( pgw_logger, cfg, serv );  // http server
        ServerLauncher launcher( udp_server, http_server );                                               // server launcher
        launcher.launch();
    } catch ( std::exception &e ) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}