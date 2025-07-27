#include "Config.h"

bool Config::parse( const std::string &filename )
{
    if ( ! IConfig::parse( filename ) ) {
        return false;
    }

    if ( m_data.contains( "server_ip" ) ) {
        m_server_ip = m_data.at( "server_ip" );
    } else {
        std::cerr << "Missing required config key: server_ip.\n";
        return false;
    }

    if ( m_data.contains( "server_port" ) ) {
        m_server_port = m_data.at( "server_port" );
    } else {
        std::cerr << "Missing required config key: server_port.\n";
        return false;
    }

    return true;
}

std::string Config::get_server_ip() const
{
    return m_server_ip;
}

uint16_t Config::get_server_port() const
{
    return m_server_port;
}
