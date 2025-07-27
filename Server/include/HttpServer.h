#pragma once

#include "httplib.h"
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "Config.h"
#include "Service.h"

class HttpServer {
public:
    HttpServer( std::shared_ptr<spdlog::logger> &, const std::shared_ptr<Config> &, std::shared_ptr<Service> & );

    void run();

private:
    std::shared_ptr<spdlog::logger> m_pgw_logger;
    const std::shared_ptr<Config> m_cfg;
    std::shared_ptr<Service> m_service;
    httplib::Server m_server;

    void get_request();
    void post_request();
};