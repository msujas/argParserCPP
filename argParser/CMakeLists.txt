cmake_minimum_required(VERSION 3.23)
set( CMAKE_CXX_STANDARD 17 )
project(argParser)

add_library(argParser)
target_sources(argParser
PRIVATE
    argParser.cpp
PUBLIC
    FILE_SET HEADERS
    FILES
        argParser.h
)
