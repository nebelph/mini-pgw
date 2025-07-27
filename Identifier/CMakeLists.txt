add_library(IdentifierLib STATIC
    src/Identifier.cpp
)

target_include_directories(IdentifierLib PRIVATE
    include
)

target_link_libraries(IdentifierLib PRIVATE
    spdlog::spdlog
)