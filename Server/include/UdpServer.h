#pragma once

#include <arpa/inet.h>
#include <chrono>
#include <fcntl.h>
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <thread>

#include "Config.h"
#include "HttpServer.h"
#include "IConfig.h"
#include "Identifier.h"
#include "LoggerTypes.h"
#include "Service.h"

const size_t BUFFER_SIZE = 64;

class UdpServer {
public:
    UdpServer( logger_ptr &, std::shared_ptr<Config> &, std::shared_ptr<Service> & );
    ~UdpServer();

    void run();
    void cleanup_expired_sessions();

private:
    logger_ptr m_pgw_logger;
    std::shared_ptr<Config> m_cfg;
    std::shared_ptr<Service> m_service;

    int m_socket;

    [[nodiscard]] static int set_nonblocking( int );
};