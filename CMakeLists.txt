cmake_minimum_required(VERSION 3.28)
project(mini-pgw)

set(CMAKE_CXX_STANDARD 20) # unordered_map::contains
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG v1.10.0
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)

add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(Identifier)
add_subdirectory(IConfig)
add_subdirectory(IRepository)
add_subdirectory(tests)