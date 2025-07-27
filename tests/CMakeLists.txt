FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

add_executable(Tests
    identifier_tests.cpp
    repository_tests.cpp
)

target_include_directories(Tests PRIVATE
    ${CMAKE_SOURCE_DIR}/Identifier/include
    ${CMAKE_SOURCE_DIR}/IRepository/include
)

target_link_libraries(Tests PRIVATE
    IdentifierLib
    InterfaceRepository
    GTest::gtest_main
    spdlog::spdlog
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(Tests)