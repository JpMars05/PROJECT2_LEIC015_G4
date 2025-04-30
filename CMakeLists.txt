cmake_minimum_required(VERSION 3.26)

project(PROJECT2_LEIC015_G4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )

add_executable(PROJECT2_LEIC015_G4
        src/main.cpp
        src/DatasetReader.cpp
)