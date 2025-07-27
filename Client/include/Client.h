#pragma once

#include <arpa/inet.h>
#include <cstdint>
#include <fcntl.h>
#include <iostream>
#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "Config.h"
#include "LoggerTypes.h"

const size_t BUFFER_SIZE = 64;

class Client {
public:
    Client( logger_ptr &, const std::shared_ptr<Config> & );
    ~Client();

    void run( const std::string & );

private:
    logger_ptr m_logger;
    const std::shared_ptr<Config> m_cfg;

    int m_socket;
};