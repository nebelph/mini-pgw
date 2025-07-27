#include "Service.h"

Service::Service( logger_ptr &pgw_logger, const std::shared_ptr<Config> &cfg, logger_ptr &cdr_logger, std::shared_ptr<Repository> &repo ) : m_pgw_logger( pgw_logger ),
                                                                                                                                            m_cfg( cfg ),
                                                                                                                                            m_repo( repo ),
                                                                                                                                            m_is_running( true )
{
}

bool Service::add_imsi( const std::string &imsi )
{
    if ( m_cfg->get_blacklist()->contains( imsi ) ) {
        m_pgw_logger->info( "Blacklist contains IMSI={}!", imsi );
        return false;
    }

    m_repo->add_session( imsi );
    return true;
}

bool Service::is_imsi_active( const std::string &imsi )
{
    return m_repo->is_session_active( imsi );
}

bool Service::graceful_shutdown()
{
    m_pgw_logger->info( "Executed graceful shutdown!" );
    if ( ! m_is_running ) {
        m_pgw_logger->warn( "Server is already down!" );
        return false;
    }

    m_is_running = false;

    return m_repo->graceful_shutdown( m_cfg->get_graceful_shutdown_rate() );
}

void Service::cleanup_expired_sessions()
{
    m_repo->cleanup_expired_sessions( m_cfg->get_session_timeout_sec() );
}

bool Service::is_running() const
{
    return m_is_running;
}