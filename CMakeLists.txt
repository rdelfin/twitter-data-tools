cmake_minimum_required(VERSION 3.3)
project(twitter_data_tools)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Requirements
find_package(Armadillo REQUIRED)

# Include directories. Should contain the include folder, as well as libraries
include_directories(include
                    ${ARMADILLO_INCLUDE_DIRS})

# Source file variables
set(TAGGER_SOURCE_FILES data-tagger/src/tagger.cpp data-tagger/src/CsvReader.cpp data-tagger/src/CsvRecord.cpp)

# Executable and linking
add_executable(data-tagger ${TAGGER_SOURCE_FILES})
target_link_libraries(data-tagger ${ARMADILLO_LIBRARIES})