#pragma once

#include "IIdentifier.h"
#include <gmock/gmock.h>

class MockIdentifier : public IIdentifier {
public:
    MOCK_METHOD( bool, set_imsi, (const std::string &, const int &), ( override ) );
    MOCK_METHOD( std::string, get_ascii_imsi, (), ( const, override ) );
    MOCK_METHOD( std::string, get_bcd_imsi, (), ( const, override ) );
};
