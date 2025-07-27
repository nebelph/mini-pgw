#pragma once

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "IConfig.h"

class Config : public IConfig {
public:
    void parse( const std::string & ) override;

    std::string get_server_ip() const;
    uint16_t get_server_port() const;

private:
    std::string m_server_ip;
    uint16_t m_server_port;
};