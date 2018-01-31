cmake_minimum_required(VERSION 3.9)

project(xautocode)

file(GLOB_RECURSE XAUTOCODE_SRC_LIST ./src/*.cpp)
add_executable(${PROJECT_NAME} ${XAUTOCODE_SRC_LIST})

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(/usr/local/lib)
target_link_libraries(${PROJECT_NAME} gflags pthread)
