#pragma once

#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "Config.h"
#include "IRepository.h"
#include "Repository.h"

class Service {
public:
    Service( std::shared_ptr<spdlog::logger> &, const std::shared_ptr<Config> &, std::shared_ptr<spdlog::logger> &, std::shared_ptr<Repository> & );

    bool add_imsi( const std::string & );
    bool is_imsi_active( const std::string & );
    bool graceful_shutdown();
    void cleanup_expired_sessions();

    bool is_running() const;

private:
    std::shared_ptr<spdlog::logger> m_pgw_logger;
    std::shared_ptr<spdlog::logger> m_cdr_logger;
    std::shared_ptr<IRepository> m_repo;
    const std::shared_ptr<Config> m_cfg;

    std::atomic<bool> m_is_running;
};