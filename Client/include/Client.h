#pragma once

#include <arpa/inet.h>
#include <cstdint>
#include <fcntl.h>
#include <iostream>
#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include "Config.h"

class Client {
public:
    Client( std::shared_ptr<spdlog::logger> &, const std::shared_ptr<Config> & );
    ~Client();

    void run( const std::string & );

private:
    std::shared_ptr<spdlog::logger> m_logger;
    const std::shared_ptr<Config> m_cfg;

    int m_socket;
};