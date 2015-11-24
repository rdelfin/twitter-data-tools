cmake_minimum_required(VERSION 3.3)
project(twitter_data_tools)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Requirements
find_package(Armadillo REQUIRED)

set(link-dirs ${ARMADILLO_LIBRARIES})

# Include directories. Should contain the include folder, as well as libraries
include_directories(include
                    ${ARMADILLO_INCLUDE_DIRS})

# Source file variables

# Executable and linking