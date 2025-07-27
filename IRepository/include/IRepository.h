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
    virtual ~IRepository() = default;

    virtual void add_session( const std::string & ) = 0;
    [[nodiscard]] virtual bool remove_session( const std::string & ) = 0;
    [[nodiscard]] virtual bool is_session_active( const std::string & ) = 0;
    virtual void cleanup_expired_sessions( const uint8_t & ) = 0;
    [[nodiscard]] virtual bool graceful_shutdown( const uint8_t & ) = 0;
};