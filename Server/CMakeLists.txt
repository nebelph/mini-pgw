FetchContent_Declare(
    cpp-httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
    GIT_TAG v0.23.1
)
FetchContent_MakeAvailable(cpp-httplib)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(server_prog
    main.cpp    
    ${SOURCES}
)

target_include_directories(server_prog PRIVATE
    include
    ${cpp-httplib_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Identifier/include
    ${CMAKE_SOURCE_DIR}/IConfig/include
)

target_link_libraries(server_prog PRIVATE
    spdlog::spdlog
    nlohmann_json::nlohmann_json
    IdentifierLib
    InterfaceConfig
)

add_custom_command(TARGET server_prog POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/Server/cfg.json
            $<TARGET_FILE_DIR:server_prog>/cfg.json
)
