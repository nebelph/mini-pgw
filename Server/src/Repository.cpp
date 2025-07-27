#include "Repository.h"

void Repository::add_session( const std::string &imsi )
{
    std::unique_lock lock( m_mutex );

    if ( m_sessions.contains( imsi ) ) {
        m_sessions.at( imsi ) = std::chrono::steady_clock::now();
        m_cdr_logger->info( "IMSI={} session is extended.", imsi );
    } else {
        m_sessions.try_emplace( imsi, std::chrono::steady_clock::now() );
        m_cdr_logger->info( "IMSI={} session is added.", imsi );
    }
}

bool Repository::remove_session( const std::string &imsi )
{
    std::unique_lock lock( m_mutex );

    if ( m_sessions.contains( imsi ) ) {
        m_sessions.erase( imsi );
        m_cdr_logger->info( "IMSI={} session is removed.", imsi );
        return true;
    }

    return false;
}

bool Repository::is_session_active( const std::string &imsi )
{
    std::shared_lock lock( m_mutex );

    if ( m_sessions.contains( imsi ) ) {
        m_pgw_logger->debug( "IMSI={} session is active.", imsi );
        return true;
    }

    m_pgw_logger->debug( "IMSI={} session is not active.", imsi );
    return false;
}

void Repository::cleanup_expired_sessions( const uint8_t &timeout )
{
    std::unique_lock lock( m_mutex );

    auto current_time = std::chrono::steady_clock::now();
    for ( auto it = m_sessions.begin(); it != m_sessions.end(); ) {
        if ( it->second + std::chrono::seconds( timeout ) < current_time ) {
            m_cdr_logger->info( "IMSI={} session is expired.", it->first );
            it = m_sessions.erase( it );
        } else {
            it++;
        }
    }
}

bool Repository::graceful_shutdown( const uint8_t &shutdown_rate )
{
    std::unique_lock lock( m_mutex );

    size_t counter = 0;
    auto start_time = std::chrono::steady_clock::now();
    for ( auto it = m_sessions.begin(); it != m_sessions.end(); ) {
        if ( counter == shutdown_rate ) {
            std::this_thread::sleep_until( start_time + std::chrono::seconds( 1 ) );
            counter = 0;
            start_time = std::chrono::steady_clock::now();
        }

        m_cdr_logger->info( "Gracefully offloading IMSI={} session.", it->first );
        it = m_sessions.erase( it );
        counter++;
    }

    return true;
}