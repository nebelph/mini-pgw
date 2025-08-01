#pragma once

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "IConfig.h"

class Config : public IConfig {
public:
    bool parse( const std::string & ) override;

    [[nodiscard]] std::string get_server_ip() const;
    [[nodiscard]] uint16_t get_server_port() const;

private:
    std::string m_server_ip;
    uint16_t m_server_port;
};