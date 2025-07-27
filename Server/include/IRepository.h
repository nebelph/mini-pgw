#pragma once

#include <iostream>
#include <shared_mutex>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <thread>
#include <unordered_map>

#include "LoggerTypes.h"

class IRepository {
public:
    IRepository( logger_ptr &pgw_logger, logger_ptr &cdr_logger ) : m_pgw_logger( pgw_logger ),
                                                                    m_cdr_logger( cdr_logger ) { }

    virtual void add_session( const std::string & ) = 0;
    [[nodiscard]] virtual bool remove_session( const std::string & ) = 0;
    [[nodiscard]] virtual bool is_session_active( const std::string & ) = 0;
    virtual void cleanup_expired_sessions( const uint8_t & ) = 0;
    [[nodiscard]] virtual bool graceful_shutdown( const uint8_t & ) = 0;

protected:
    logger_ptr m_pgw_logger;
    logger_ptr m_cdr_logger;
};