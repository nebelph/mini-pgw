#include "Config.h"

bool Config::parse( const std::string &filename )
{
    if ( !IConfig::parse( filename ) ) {
        return false;
    }

    if ( m_data.contains( "udp_ip" ) ) {
        m_udp_ip = m_data.at( "udp_ip" );
    } else {
        std::cerr << "Missing required config key: udp_ip.\n";
        return false;
    }

    if ( m_data.contains( "udp_port" ) ) {
        m_udp_port = m_data.at( "udp_port" );
    } else {
        std::cerr << "Missing required config key: udp_port.\n";
        return false;
    }

    if ( m_data.contains( "session_timeout_sec" ) ) {
        m_session_timeout_sec = m_data.at( "session_timeout_sec" );
    } else {
        std::cerr << "Missing required config key: session_timeout_sec.\n";
        return false;
    }

    if ( m_data.contains( "cdr_file" ) ) {
        m_cdr_file = m_data.at( "cdr_file" );
    } else {
        std::cerr << "Missing required config key: cdr_file.\n";
        return false;
    }

    if ( m_data.contains( "http_ip" ) ) {
        m_http_ip = m_data.at( "http_ip" );
    } else {
        std::cerr << "Missing required config key: http_ip.\n";
        return false;
    }

    if ( m_data.contains( "http_port" ) ) {
        m_http_port = m_data.at( "http_port" );
    } else {
        std::cerr << "Missing required config key: http_port.\n";
        return false;
    }

    if ( m_data.contains( "graceful_shutdown_rate" ) ) {
        m_graceful_shutdown_rate = m_data.at( "graceful_shutdown_rate" );
    } else {
        std::cerr << "Missing required config key: graceful_shutdown_rate.\n";
        return false;
    }

    if ( m_data.contains( "blacklist" ) ) {
        m_blacklist = std::make_shared<std::unordered_set<std::string>>( m_data.at( "blacklist" ) );
    } else {
        std::cerr << "Missing required config key: blacklist.\n";
        return false;
    }

    return true;
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

std::shared_ptr<std::unordered_set<std::string>> Config::get_blacklist() const
{
    return m_blacklist;
}