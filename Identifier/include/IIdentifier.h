#pragma once

#include <cstdint>
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include <vector>

#include "LoggerTypes.h"

#define F_ASCII 0
#define F_BCD 1

class IIdentifier {
public:
    virtual ~IIdentifier() = default;

    [[nodiscard]] virtual bool set_imsi( const std::string &, const int & ) = 0;

    [[nodiscard]] virtual std::string get_ascii_imsi() const = 0;
    [[nodiscard]] virtual std::string get_bcd_imsi() const = 0;
};