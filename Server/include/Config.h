#pragma once

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "IConfig.h"

class Config : public IConfig {
public:
    void parse( const std::string & ) override;

    std::string get_udp_ip() const;
    uint16_t get_udp_port() const;
    uint8_t get_session_timeout_sec() const;
    std::string get_cdr_file() const;
    std::string get_http_ip() const;
    uint16_t get_http_port() const;
    uint8_t get_graceful_shutdown_rate() const;
    std::unordered_set<std::string> get_blacklist() const;

private:
    std::string m_udp_ip;
    uint16_t m_udp_port;
    uint8_t m_session_timeout_sec;
    std::string m_cdr_file;
    std::string m_http_ip;
    uint16_t m_http_port;
    uint8_t m_graceful_shutdown_rate;
    std::unordered_set<std::string> m_blacklist;
};