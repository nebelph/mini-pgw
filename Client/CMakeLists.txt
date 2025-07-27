file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(client_prog
    main.cpp    
    ${SOURCES}
)

target_include_directories(client_prog PRIVATE
    include
    ${CMAKE_SOURCE_DIR}/Identifier/include
    ${CMAKE_SOURCE_DIR}/IConfig/include
)

target_link_libraries(client_prog PRIVATE
    spdlog::spdlog
    nlohmann_json::nlohmann_json
    IdentifierLib
    InterfaceConfig
)

add_custom_command(TARGET client_prog POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/Client/cfg.json
            $<TARGET_FILE_DIR:client_prog>/cfg.json
)