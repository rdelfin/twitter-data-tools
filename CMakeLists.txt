cmake_minimum_required(VERSION 3.2)
project(twitter_data_tools)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Requirements
find_package (Threads REQUIRED)

set(LINK-DIRS ${CMAKE_THREAD_LIBS_INIT})

# Include directories. Should contain the include folder, as well as libraries
include_directories(include
                    ${Jsoncpp_INCLUDE_DIR})

set(NEURAL-NETWORK_SRC neural-network/src/WordNeuralNetwork.cpp)
set(REPRESENTATION-PARSER_SRC representation-parser/src/dictionary-generator.cpp
                              representation-parser/src/Tweet.cpp
                              representation-parser/src/Dictonary.cpp
                              representation-parser/src/DictionaryEntry.cpp
                              representation-parser/src/TweetLoader.cpp
                              representation-parser/src/Configuration.cpp
                              representation-parser/src/OutputGenerator.cpp)
set(TOOLS-LIB_SRC tools-lib/src/Process.cpp
                  tools-lib/src/StringUtils.cpp)
set(NN-PARSER_SRC nn-parser/src/main.cpp)

# Dictionary executable and linking
add_executable(dictionary ${REPRESENTATION-PARSER_SRC} ${TOOLS-LIB_SRC})
target_link_libraries(dictionary ${LINK-DIRS})

# Neural network representation executable and linking
message("NEURAL NETWORK SRC: ${NERUAL-NETWORK_SRC}")
message("NN PARSER SRC: ${NN-PARSER_SRC}")
message("TOOLS LIB SRC: ${TOOLS-LIB_SRC}")
add_executable(nn-representation ${NEURAL-NETWORK_SRC} ${TOOLS-LIB_SRC} ${NN-PARSER_SRC})
target_link_libraries(nn-representation ${LINK-DIRS})


# Copy configuration files
add_custom_target(CopyConfig ${CMAKE_COMMAND} -E copy_directory
                  ${CMAKE_CURRENT_SOURCE_DIR}/config
                  ${CMAKE_CURRENT_BINARY_DIR}/config)
add_dependencies(dictionary CopyConfig)


#CMAKE_RUNTIME_OUTPUT_DIRECTORY