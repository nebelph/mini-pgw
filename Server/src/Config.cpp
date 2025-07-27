#include "Config.h"

void Config::parse( const std::string & filename)
{
    IConfig::parse( filename );

    m_udp_ip = m_data.at( "udp_ip" );
    m_udp_ip = m_data.at( "udp_ip" );
    m_udp_port = m_data.at( "udp_port" );
    m_session_timeout_sec = m_data.at( "session_timeout_sec" );
    m_cdr_file = m_data.at( "cdr_file" );
    m_http_ip = m_data.at( "http_ip" );
    m_http_port = m_data.at( "http_port" );
    m_graceful_shutdown_rate = m_data.at( "graceful_shutdown_rate" );
    m_blacklist = m_data.at( "blacklist" );
}

std::string Config::get_udp_ip() const
{
    return m_udp_ip;
}

uint16_t Config::get_udp_port() const
{
    return m_udp_port;
}

uint8_t Config::get_session_timeout_sec() const
{
    return m_session_timeout_sec;
}

std::string Config::get_cdr_file() const
{
    return m_cdr_file;
}

std::string Config::get_http_ip() const
{
    return m_http_ip;
}

uint16_t Config::get_http_port() const
{
    return m_http_port;
}

uint8_t Config::get_graceful_shutdown_rate() const
{
    return m_graceful_shutdown_rate;
}

std::unordered_set<std::string> Config::get_blacklist() const
{
    return m_blacklist;
}