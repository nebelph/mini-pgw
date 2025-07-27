#pragma once

#include <cstdint>
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include <vector>

/*
contains:
    - IMSI (ASCII);
    - IMSI (BCD).

size of MCC  =  3
size of MSN  =  2
size of MSIN =  1-10
*/

#define F_ASCII 0
#define F_BCD 1

class Identifier {
public:
    Identifier( std::shared_ptr<spdlog::logger> & );

    [[nodiscard]] bool set_imsi( const std::string &, const int & );

    [[nodiscard]] std::string get_ascii_imsi() const;
    [[nodiscard]] std::string get_bcd_imsi() const;

private:
    std::shared_ptr<spdlog::logger> m_logger;

    const size_t ASCII_IMSI_MIN_SIZE = 6;
    const size_t ASCII_IMSI_MAX_SIZE = 15;
    const size_t BCD_IMSI_MIN_SIZE = 12;
    const size_t BCD_IMSI_MAX_SIZE = 22;

    std::string m_ascii_imsi_str;
    std::string m_bcd_imsi_str;

    void encode_in_bcd();
    void decode_in_ascii();

    [[nodiscard]] bool imsi_is_valid( const std::string &, const int & );
    [[nodiscard]] bool is_digit( const char & );
    [[nodiscard]] uint8_t char_to_int( const char & ) const;
    [[nodiscard]] char int_to_char( const uint8_t & ) const;
    [[nodiscard]] std::string int_to_hex( const uint8_t & ) const;
};