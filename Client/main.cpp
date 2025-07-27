#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "Client.h"
#include "Config.h"
#include "Identifier.h"

const std::string JSON_FILE = "cfg.json";

int main( int argc, char **argv )
{
    if ( argc != 2 ) {
        std::cerr << "Usage: " << argv[0] << " <IMSI>\n";
        return -1;
    }

    try {
        std::shared_ptr<spdlog::logger> client_logger;

        std::shared_ptr<Config> cfg = std::make_shared<Config>();
        cfg->parse( JSON_FILE );

        client_logger = spdlog::basic_logger_mt( "client_logger", cfg->get_log_file(), true );
        spdlog::set_level( cfg->get_log_level() );
        client_logger->flush_on( spdlog::level::info );

        client_logger->debug( "Config {} succesfully loaded! ", JSON_FILE );

        Identifier imsi( client_logger );
        if ( imsi.set_imsi( argv[1], F_ASCII ) ) {
            Client cli( client_logger, cfg );
            cli.run( imsi.get_bcd_imsi() );
        }

    } catch ( std::exception &e ) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}