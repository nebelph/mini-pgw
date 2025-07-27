FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

add_executable(IdentifierTests
    identifier_tests.cpp
)

target_include_directories(IdentifierTests PRIVATE
    ${CMAKE_SOURCE_DIR}/Identifier/include
)

target_link_libraries(IdentifierTests PRIVATE
    IdentifierLib
    GTest::gtest_main
    spdlog::spdlog
)

include(GoogleTest)
gtest_discover_tests(IdentifierTests)