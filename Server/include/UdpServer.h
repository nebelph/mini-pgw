#pragma once

#include <arpa/inet.h>
#include <chrono>
#include <fcntl.h>
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <thread>

#include "Config.h"
#include "IConfig.h"
#include "Identifier.h"
#include "Service.h"
#include "HttpServer.h"

class UdpServer {
public:
    UdpServer( std::shared_ptr<spdlog::logger> &, std::shared_ptr<Config> &, std::shared_ptr<Service> &, std::shared_ptr<HttpServer> & );
    ~UdpServer();

    void start();

private:
    std::shared_ptr<spdlog::logger> m_pgw_logger;
    std::shared_ptr<Config> m_cfg;
    std::shared_ptr<Service> m_service;
    std::shared_ptr<HttpServer> m_http_server;

    int m_socket;

    void run();
    void cleanup_expired_sessions();
    int set_nonblocking( int );
};