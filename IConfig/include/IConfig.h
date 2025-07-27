#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <unordered_map>

class IConfig {
public:
    [[nodiscard]] virtual bool parse( const std::string & ) = 0;

    [[nodiscard]] std::string get_log_file() const;
    [[nodiscard]] spdlog::level::level_enum get_log_level() const;

protected:
    nlohmann::json_abi_v3_12_0::json m_data;

    std::string m_log_file;
    spdlog::level::level_enum m_log_level;
};