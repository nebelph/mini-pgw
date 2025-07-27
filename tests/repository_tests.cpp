#include "MockRepository.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST( MockRepositoryTest, AddSessionCalledWithCorrectIMSI )
{
    MockRepository mock;

    EXPECT_CALL( mock, add_session( "123456789" ) ).Times( ::testing::Exactly( 1 ) );

    mock.add_session( "123456789" );
}

TEST( MockRepositoryTest, RemoveSessionReturnsTrue )
{
    MockRepository mock;

    EXPECT_CALL( mock, remove_session( "imsi1" ) ).WillOnce( ::testing::Return( true ) );

    EXPECT_TRUE( mock.remove_session( "imsi1" ) );
}

TEST( MockRepositoryTest, RemoveSessionReturnsFalse )
{
    MockRepository mock;

    EXPECT_CALL( mock, remove_session( "imsi2" ) ).WillOnce( ::testing::Return( false ) );

    EXPECT_FALSE( mock.remove_session( "imsi2" ) );
}

TEST( MockRepositoryTest, IsSessionActiveReturnsTrue )
{
    MockRepository mock;

    EXPECT_CALL( mock, is_session_active( "imsi-active" ) ).WillOnce( ::testing::Return( true ) );

    EXPECT_TRUE( mock.is_session_active( "imsi-active" ) );
}

TEST( MockRepositoryTest, IsSessionActiveReturnsFalse )
{
    MockRepository mock;

    EXPECT_CALL( mock, is_session_active( "imsi-inactive" ) ).WillOnce( ::testing::Return( false ) );

    EXPECT_FALSE( mock.is_session_active( "imsi-inactive" ) );
}

TEST( MockRepositoryTest, CleanupExpiredSessionsCalledOnce )
{
    MockRepository mock;

    EXPECT_CALL( mock, cleanup_expired_sessions( 10 ) ).Times( ::testing::Exactly( 1 ) );

    mock.cleanup_expired_sessions( 10 );
}

TEST( MockRepositoryTest, GracefulShutdownReturnsTrue )
{
    MockRepository mock;

    EXPECT_CALL( mock, graceful_shutdown( 2 ) ).WillOnce( ::testing::Return( true ) );

    EXPECT_TRUE( mock.graceful_shutdown( 2 ) );
}