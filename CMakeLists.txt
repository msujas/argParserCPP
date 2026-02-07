cmake_minimum_required(VERSION 3.23)

project(argParserExample)

add_executable(example)
target_sources(example
PRIVATE
argParseExample.cpp
)
target_link_libraries(example
PRIVATE
    argParser
)

add_subdirectory(argParser)