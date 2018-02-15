cmake_minimum_required(VERSION 3.5)

project(xautocode)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

file(GLOB_RECURSE XAUTOCODE_SRC_LIST ./src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(/usr/local/lib/boost)

add_executable(${PROJECT_NAME} ${XAUTOCODE_SRC_LIST})

target_link_libraries(${PROJECT_NAME} boost_program_options boost_filesystem boost_system pthread)
