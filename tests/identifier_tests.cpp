#include "MockIdentifier.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST( IdentifierTest, AsciiIsInvalid1 )
{
    MockIdentifier mock;

    EXPECT_CALL( mock, set_imsi( "222", F_ASCII ) ).WillOnce( testing::Return( false ) );

    bool result = mock.set_imsi( "222", F_ASCII );
    EXPECT_FALSE( result );
}

TEST( IdentifierTest, AsciiIsInvalid2 )
{
    MockIdentifier mock;

    EXPECT_CALL( mock, set_imsi( "1234567890123456", F_ASCII ) ).WillOnce( testing::Return( false ) );

    bool result = mock.set_imsi( "1234567890123456", F_ASCII );
    EXPECT_FALSE( result );
}

TEST( IdentifierTest, AsciiIsValid1 )
{
    MockIdentifier mock;

    EXPECT_CALL( mock, set_imsi( "2247822", F_ASCII ) ).WillOnce( testing::Return( true ) );

    bool result = mock.set_imsi( "2247822", F_ASCII );
    EXPECT_TRUE( result );
}

TEST( IdentifierTest, AsciiIsValid2 )
{
    MockIdentifier mock;

    EXPECT_CALL( mock, set_imsi( "123456789012345", F_ASCII ) ).WillOnce( testing::Return( true ) );

    bool result = mock.set_imsi( "123456789012345", F_ASCII );
    EXPECT_TRUE( result );
}

TEST( IdentifierTest, BcdIsInvalid1 )
{
    MockIdentifier mock;

    EXPECT_CALL( mock, set_imsi( "222", F_BCD ) ).WillOnce( testing::Return( false ) );

    bool result = mock.set_imsi( "222", F_BCD );
    EXPECT_FALSE( result );
}

TEST( IdentifierTest, BcdIsInvalid2 )
{
    MockIdentifier mock;

    EXPECT_CALL( mock, set_imsi( "01030011", F_BCD ) ).WillOnce( testing::Return( false ) );

    bool result = mock.set_imsi( "01030011", F_BCD );
    EXPECT_FALSE( result );
}

TEST( IdentifierTest, BcdIsValid1 )
{
    MockIdentifier mock;

    EXPECT_CALL( mock, set_imsi( "01020012f3", F_BCD ) ).WillOnce( testing::Return( true ) );

    bool result = mock.set_imsi( "01020012f3", F_BCD );
    EXPECT_TRUE( result );
}

TEST( IdentifierTest, BcdIsValid2 )
{
    MockIdentifier mock;

    EXPECT_CALL( mock, set_imsi( "01080012345678901234f5", F_BCD ) ).WillOnce( testing::Return( true ) );

    bool result = mock.set_imsi( "01080012345678901234f5", F_BCD );
    EXPECT_TRUE( result );
}

TEST( IdentifierTest, EncodeInBcd1 )
{
    MockIdentifier mock;

    EXPECT_CALL( mock, set_imsi( "123456789", F_ASCII ) ).WillOnce( testing::Return( true ) );
    EXPECT_CALL( mock, get_bcd_imsi() ).WillOnce( testing::Return( "01050021436587f9" ) );

    bool result = mock.set_imsi( "123456789", F_ASCII );
    EXPECT_TRUE( result );

    std::string bcd = mock.get_bcd_imsi();
    EXPECT_EQ( bcd, "01050021436587f9" );
}

TEST( IdentifierTest, EncodeInBcd2 )
{
    MockIdentifier mock;

    EXPECT_CALL( mock, set_imsi( "47329247420", F_ASCII ) ).WillOnce( testing::Return( true ) );
    EXPECT_CALL( mock, get_bcd_imsi() ).WillOnce( testing::Return( "0106007423297423f0" ) );

    bool result = mock.set_imsi( "47329247420", F_ASCII );
    EXPECT_TRUE( result );

    std::string bcd = mock.get_bcd_imsi();
    EXPECT_EQ( bcd, "0106007423297423f0" );
}

TEST( IdentifierTest, DecodeInAscii1 )
{
    MockIdentifier mock;

    EXPECT_CALL( mock, set_imsi( "01050084910587f9", F_BCD ) ).WillOnce( testing::Return( true ) );
    EXPECT_CALL( mock, get_ascii_imsi() ).WillOnce( testing::Return( "481950789" ) );

    bool result = mock.set_imsi( "01050084910587f9", F_BCD );
    EXPECT_TRUE( result );

    std::string ascii = mock.get_ascii_imsi();
    EXPECT_EQ( ascii, "481950789" );
}

TEST( IdentifierTest, DecodeInAscii2 )
{
    MockIdentifier mock;

    EXPECT_CALL( mock, set_imsi( "010300520018", F_BCD ) ).WillOnce( testing::Return( true ) );
    EXPECT_CALL( mock, get_ascii_imsi() ).WillOnce( testing::Return( "250081" ) );

    bool result = mock.set_imsi( "010300520018", F_BCD );
    EXPECT_TRUE( result );

    std::string ascii = mock.get_ascii_imsi();
    EXPECT_EQ( ascii, "250081" );
}
