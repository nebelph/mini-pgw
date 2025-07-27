add_library(InterfaceConfig STATIC
    src/IConfig.cpp
)

target_include_directories(InterfaceConfig PRIVATE
    include
)

target_link_libraries(InterfaceConfig PRIVATE
    spdlog::spdlog
    nlohmann_json::nlohmann_json
)