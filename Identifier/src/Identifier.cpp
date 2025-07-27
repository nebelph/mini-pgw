#include "Identifier.h"

Identifier::Identifier( std::shared_ptr<spdlog::logger> &file_logger ) : m_logger( file_logger )
{
}

bool Identifier::set_imsi( const std::string &imsi, const int &flag )
{
    if ( ( flag != F_ASCII && flag != F_BCD ) || ! imsi_is_valid( imsi, flag ) ) {
        return false;
    }
    switch ( flag ) {
    case F_ASCII: {
        m_ascii_imsi_str = imsi;
        encode_in_bcd();
    } break;
    case F_BCD: {
        m_bcd_imsi_str = imsi;
        decode_in_ascii();
    } break;
    }
    return true;
}

std::string Identifier::get_ascii_imsi() const
{
    return m_ascii_imsi_str;
}

std::string Identifier::get_bcd_imsi() const
{
    return m_bcd_imsi_str;
}

void Identifier::encode_in_bcd()
{
    std::vector<uint8_t> imsi_v;/* = {
        0x01u,  // type == 1
        0x08u,  // length == 3-8 (number of octets)
        0x00u,  // spare == 0, instance == 0
        0x00u,  // octet 1
        0x00u,  // octet 2
        ...
        0xF0u   // octet n
    }*/
    size_t ascii_imsi_size = m_ascii_imsi_str.size();
    imsi_v.push_back( 0x01 );
    imsi_v.push_back( ascii_imsi_size % 2 == 0 ? ascii_imsi_size / 2 : ascii_imsi_size / 2 + 1 );
    imsi_v.push_back( 0x00 );
    for ( size_t i = 0; i < ascii_imsi_size / 2; i++ ) {
        uint8_t octet = 0x00u;
        octet |= char_to_int( m_ascii_imsi_str.at( i * 2 ) );
        octet |= ( char_to_int( m_ascii_imsi_str.at( i * 2 + 1 ) ) << 4 );
        imsi_v.push_back( octet );
    }
    if ( ascii_imsi_size % 2 == 1 ) {
        uint8_t last_octet = 0xF0u;
        last_octet |= m_ascii_imsi_str.at( ascii_imsi_size - 1 );
        imsi_v.push_back( last_octet );
    }

    for ( auto &i : imsi_v ) {
        m_bcd_imsi_str += int_to_hex( i );
    }

    m_logger->debug( "IMSI={} (BCD) encoded!", m_bcd_imsi_str );
}

void Identifier::decode_in_ascii()
{
    size_t bcd_imsi_size = m_bcd_imsi_str.size();
    for ( size_t i = 6; i < bcd_imsi_size; i += 2 ) {
        m_ascii_imsi_str.push_back( m_bcd_imsi_str.at( i + 1 ) );
        if ( m_bcd_imsi_str.at( i ) != 'f' ) {
            m_ascii_imsi_str.push_back( m_bcd_imsi_str.at( i ) );
        }
    }

    m_logger->debug( "IMSI={} (ASCII) decoded!", m_ascii_imsi_str );
}

bool Identifier::imsi_is_valid( const std::string &imsi, const int &flag )
{
    size_t imsi_size = imsi.size();

    switch ( flag ) {
    case F_ASCII: {
        if ( imsi_size >= ASCII_IMSI_MIN_SIZE && imsi_size <= ASCII_IMSI_MAX_SIZE ) {
            m_logger->debug( "IMSI length={} is valid.", imsi_size );
        } else {
            m_logger->error( "IMSI length={} is invalid.", imsi_size );
            return false;
        }
        for ( const char &ch : imsi ) {
            if ( ! is_digit( ch ) ) {
                m_logger->error( "IMSI={} (ASCII) is invalid!", ch );
                return false;
            }
        }
        m_logger->debug( "IMSI={} (ASCII) is valid.", imsi );
    } break;
    case F_BCD: {
        if ( imsi_size >= BCD_IMSI_MIN_SIZE && imsi_size <= BCD_IMSI_MAX_SIZE && imsi_size % 2 == 0 ) {
            m_logger->debug( "IMSI length={} is valid.", imsi_size );
        } else {
            m_logger->error( "IMSI length={} is invalid.", imsi_size );
            return false;
        }
        for ( size_t i = 0; i < imsi_size; i++ ) {
            if ( ! is_digit( imsi.at( i ) ) ) {
                if ( i != imsi_size - 2 || imsi.at( i ) != 'f' ) {
                    m_logger->error( "IMSI={} (BCD) is invalid!", imsi.at( i ) );
                    return false;
                }
            }
        }
        m_logger->debug( "IMSI={} (BCD) is valid.", imsi );
    } break;
    }
    return true;
}

bool Identifier::is_digit( const char &ch )
{
    return ch >= 48 && ch <= 57 ? true : false;
}

uint8_t Identifier::char_to_int( const char &ch ) const
{
    return ch - 48;
}

char Identifier::int_to_char( const uint8_t &i ) const
{
    return i + 48;
}

std::string Identifier::int_to_hex( const uint8_t &number ) const
{
    std::stringstream ss;
    ss << std::hex << (uint)number;
    return number > 15 ? ss.str() : "0" + ss.str();
}