#pragma once

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "IConfig.h"

class Config : public IConfig {
public:
    [[nodiscard]] bool parse( const std::string & ) override;

    [[nodiscard]] std::string get_udp_ip() const;
    [[nodiscard]] uint16_t get_udp_port() const;
    [[nodiscard]] uint8_t get_session_timeout_sec() const;
    [[nodiscard]] std::string get_cdr_file() const;
    [[nodiscard]] std::string get_http_ip() const;
    [[nodiscard]] uint16_t get_http_port() const;
    [[nodiscard]] uint8_t get_graceful_shutdown_rate() const;
    [[nodiscard]] std::shared_ptr<std::unordered_set<std::string>> get_blacklist() const;

private:
    std::string m_udp_ip;
    uint16_t m_udp_port;
    uint8_t m_session_timeout_sec;
    std::string m_cdr_file;
    std::string m_http_ip;
    uint16_t m_http_port;
    uint8_t m_graceful_shutdown_rate;
    std::shared_ptr<std::unordered_set<std::string>> m_blacklist;
};