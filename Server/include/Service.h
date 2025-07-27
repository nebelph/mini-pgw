#pragma once

#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "Config.h"
#include "IRepository.h"
#include "LoggerTypes.h"
#include "Repository.h"

class Service {
public:
    Service( logger_ptr &, const std::shared_ptr<Config> &, logger_ptr &, std::shared_ptr<Repository> & );

    [[nodiscard]] bool add_imsi( const std::string & );
    [[nodiscard]] bool is_imsi_active( const std::string & );
    [[nodiscard]] bool graceful_shutdown();
    void cleanup_expired_sessions();

    [[nodiscard]] bool is_running() const;

private:
    logger_ptr m_pgw_logger;
    logger_ptr m_cdr_logger;
    std::shared_ptr<IRepository> m_repo;
    const std::shared_ptr<Config> m_cfg;

    std::atomic<bool> m_is_running;
};