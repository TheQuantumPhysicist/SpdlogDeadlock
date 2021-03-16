cmake_minimum_required(VERSION 3.5)

project(spdlog_deadlock LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/spdlog/include)

add_executable(spdlog_deadlock main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

target_link_libraries(spdlog_deadlock -lpthread -lboost_system -lboost_filesystem)
