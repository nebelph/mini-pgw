#pragma once

#include <iostream>
#include <shared_mutex>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <thread>
#include <unordered_map>

class IRepository {
public:
    IRepository( std::shared_ptr<spdlog::logger> &pgw_logger, std::shared_ptr<spdlog::logger> &cdr_logger ) : m_pgw_logger( pgw_logger ),
                                                                                                              m_cdr_logger( cdr_logger ) { }

    virtual void add_session( const std::string & ) = 0;
    virtual bool remove_session( const std::string & ) = 0;
    virtual bool is_session_active( const std::string & ) = 0;
    virtual void cleanup_expired_sessions( const uint8_t & ) = 0;
    virtual bool graceful_shutdown( const uint8_t & ) = 0;

protected:
    std::shared_ptr<spdlog::logger> m_pgw_logger;
    std::shared_ptr<spdlog::logger> m_cdr_logger;
    std::unordered_map<std::string, std::chrono::steady_clock::time_point> m_sessions;
    std::shared_mutex m_mutex;
};