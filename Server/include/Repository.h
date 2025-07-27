#pragma once

#include "IRepository.h"

class Repository : public IRepository {
public:
    Repository( logger_ptr &pgw_logger, logger_ptr &cdr_logger ) : m_pgw_logger( pgw_logger ),
                                                                   m_cdr_logger( cdr_logger ) { }

    void add_session( const std::string & ) override;
    [[nodiscard]] bool remove_session( const std::string & ) override;
    [[nodiscard]] bool is_session_active( const std::string & ) override;
    void cleanup_expired_sessions( const uint8_t & ) override;
    [[nodiscard]] bool graceful_shutdown( const uint8_t & ) override;

private:
    logger_ptr m_pgw_logger;
    logger_ptr m_cdr_logger;
    std::unordered_map<std::string, std::chrono::steady_clock::time_point> m_sessions;
    std::shared_mutex m_mutex;
};