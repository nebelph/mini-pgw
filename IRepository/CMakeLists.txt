add_library(InterfaceRepository STATIC
    src/IRepository.cpp
)

target_include_directories(InterfaceRepository PRIVATE
    include
    PUBLIC ${CMAKE_SOURCE_DIR}
)

target_link_libraries(InterfaceRepository PRIVATE
    spdlog::spdlog
)