#include "IConfig.h"

void IConfig::parse( const std::string &filename )
{
    std::ifstream f( filename );
    if ( ! f ) {
        throw std::runtime_error( "Couldn't open json file!" );
    }

    m_data = nlohmann::json::parse( f );

    m_log_file = m_data.at( "log_file" );

    std::string log_level = m_data.at( "log_level" );
    if ( log_level == "DEBUG" )
        m_log_level = spdlog::level::debug;
    else if ( log_level == "WARN" )
        m_log_level = spdlog::level::warn;
    else if ( log_level == "CRITICAL" )
        m_log_level = spdlog::level::critical;
    else if ( log_level == "ERROR" )
        m_log_level = spdlog::level::err;
    else
        m_log_level = spdlog::level::info;
}

std::string IConfig::get_log_file() const
{
    return m_log_file;
}

spdlog::level::level_enum IConfig::get_log_level() const
{
    return m_log_level;
}