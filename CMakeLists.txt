cmake_minimum_required(VERSION 3.9)

project(xautocode)

file(GLOB_RECURSE XAUTOCODE_SRC_LIST ./src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(/usr/local/lib/boost)

add_executable(${PROJECT_NAME} ${XAUTOCODE_SRC_LIST})

target_link_libraries(${PROJECT_NAME} boost_program_options pthread)
