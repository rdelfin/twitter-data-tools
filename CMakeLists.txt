cmake_minimum_required(VERSION 3.2)
project(twitter_data_tools)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Requirements
find_package(Armadillo REQUIRED)

set(link-dirs ${ARMADILLO_LIBRARIES})

# Include directories. Should contain the include folder, as well as libraries
include_directories(include
                    ${ARMADILLO_INCLUDE_DIRS})


# Executable and linking
add_executable(dictionary representation-parser/src/dictionary-generator.cpp)

target_link_libraries(dictionary ${link-dirs})

# Copy configuration files
add_custom_target(CopyConfig ${CMAKE_COMMAND} -E copy_directory
                  ${CMAKE_CURRENT_SOURCE_DIR}/config
                  ${CMAKE_CURRENT_BINARY_DIR}/config)
add_dependencies(dictionary CopyConfig)
#file(COPY
#     ${CMAKE_CURRENT_SOURCE_DIR}/config
#     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


#CMAKE_RUNTIME_OUTPUT_DIRECTORY