#pragma once

#include "IRepository.h"
#include <gmock/gmock.h>

class MockRepository : public IRepository {
public:
    MOCK_METHOD( void, add_session, (const std::string &), ( override ) );
    MOCK_METHOD( bool, remove_session, (const std::string &), ( override ) );
    MOCK_METHOD( bool, is_session_active, (const std::string &), ( override ) );
    MOCK_METHOD( void, cleanup_expired_sessions, (const uint8_t &), ( override ) );
    MOCK_METHOD( bool, graceful_shutdown, (const uint8_t &), ( override ) );

    // MOCK_METHOD(bool, set_imsi, (const std::string&, const int&), (override));
    // MOCK_METHOD(std::string, get_ascii_imsi, (), (const, override));
    // MOCK_METHOD(std::string, get_bcd_imsi, (), (const, override));
};
