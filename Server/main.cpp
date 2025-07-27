#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "Config.h"
#include "httplib.h"
#include "HttpServer.h"
#include "UdpServer.h"

const std::string JSON_FILE = "cfg.json";

int main()
{
    try {
        std::shared_ptr<spdlog::logger> pgw_logger;
        std::shared_ptr<spdlog::logger> cdr_logger;

        std::shared_ptr<Config> cfg = std::make_shared<Config>();
        cfg->parse( JSON_FILE );

        pgw_logger = spdlog::basic_logger_mt( "pgw_logger", cfg->get_log_file(), true );
        spdlog::set_level( cfg->get_log_level() );
        pgw_logger->flush_on(spdlog::level::info);

        pgw_logger->debug( "Config {} succesfully loaded! ", JSON_FILE );

        cdr_logger = spdlog::basic_logger_mt( "cdr_logger", cfg->get_cdr_file(), true );
        cdr_logger->flush_on(spdlog::level::info);
        
        std::shared_ptr<Service> serv = std::make_shared<Service>( pgw_logger, cfg, cdr_logger );

        std::shared_ptr<HttpServer> http_server = std::make_shared<HttpServer>( pgw_logger, cfg, serv );

        // http://127.0.0.1:8080/check_subscriber?imsi=6753562
        // curl -X POST http://127.0.0.1:8080/stop -d "noop=1"

        UdpServer udp_server( pgw_logger, cfg, serv, http_server );
        udp_server.start();
    } catch ( std::exception &e ) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}