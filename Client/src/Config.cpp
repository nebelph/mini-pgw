#include "Config.h"

void Config::parse( const std::string & filename)
{
    IConfig::parse( filename );

    m_server_ip = m_data.at( "server_ip" );
    m_server_port = m_data.at( "server_port" );
}

std::string Config::get_server_ip() const
{
    return m_server_ip;
}

uint16_t Config::get_server_port() const
{
    return m_server_port;
}
