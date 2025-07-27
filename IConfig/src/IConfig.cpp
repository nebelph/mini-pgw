#include "IConfig.h"

bool IConfig::parse( const std::string &filename )
{
    std::ifstream f( filename );
    if ( ! f ) {
        return false;
    }

    m_data = nlohmann::json::parse( f );

    if ( m_data.contains( "log_file" ) ) {
        m_log_file = m_data.at( "log_file" );
    } else {
        std::cerr << "Missing required config key: log_file.\n";
        return false;
    }

    std::string log_level;
    if ( m_data.contains( "log_level" ) ) {
        log_level = m_data.at( "log_level" );
    } else {
        std::cerr << "Missing required config key: log_level.\n";
        return false;
    }

    if ( log_level == "DEBUG" )
        m_log_level = spdlog::level::debug;
    else if ( log_level == "INFO" )
        m_log_level = spdlog::level::info;
    else if ( log_level == "WARN" )
        m_log_level = spdlog::level::warn;
    else if ( log_level == "CRITICAL" )
        m_log_level = spdlog::level::critical;
    else if ( log_level == "ERROR" )
        m_log_level = spdlog::level::err;
    else {
        std::cerr << "Invalid log_level.\n";
        return false;
    }

    return true;
}

std::string IConfig::get_log_file() const
{
    return m_log_file;
}

spdlog::level::level_enum IConfig::get_log_level() const
{
    return m_log_level;
}