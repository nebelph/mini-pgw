#pragma once

#include "IIdentifier.h"

/*
contains:
    - IMSI (ASCII);
    - IMSI (BCD).

size of MCC  =  3
size of MSN  =  2
size of MSIN =  1-10
*/

static constexpr uint8_t CHAR_ZERO = 48;
static constexpr uint8_t CHAR_NINE = 57;

static constexpr size_t ASCII_IMSI_MIN_SIZE = 6;
static constexpr size_t ASCII_IMSI_MAX_SIZE = 15;
static constexpr size_t BCD_IMSI_MIN_SIZE = 12;
static constexpr size_t BCD_IMSI_MAX_SIZE = 22;

class Identifier : public IIdentifier {
public:
    Identifier( logger_ptr & );

    [[nodiscard]] bool set_imsi( const std::string &, const int & ) override;

    [[nodiscard]] std::string get_ascii_imsi() const override;
    [[nodiscard]] std::string get_bcd_imsi() const override;

private:
    logger_ptr m_logger;

    std::string m_ascii_imsi_str;
    std::string m_bcd_imsi_str;

    void encode_in_bcd();
    void decode_in_ascii();

    [[nodiscard]] bool imsi_is_valid( const std::string &, const int & ) const;
    [[nodiscard]] static bool is_digit( const char & );
    [[nodiscard]] static uint8_t char_to_int( const char & );
    [[nodiscard]] static char int_to_char( const uint8_t & );
    [[nodiscard]] static std::string int_to_hex( const uint8_t & );
};