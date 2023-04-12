cmake_minimum_required(VERSION 3.0.0)
set(app "cpp-lua")
project(${app} VERSION 0.1.0)

include_directories(${CMAKE_CURRENT_LIST_DIR}/src/lua)
set(app_src)

file(GLOB_RECURSE lua_src ${CMAKE_CURRENT_LIST_DIR}/src/lua/*.h ${CMAKE_CURRENT_LIST_DIR}/src/lua/*.c ${CMAKE_CURRENT_LIST_DIR}/src/lua/*.cpp)
list(APPEND app_src ${lua_src})

file(GLOB_RECURSE script_src ${CMAKE_CURRENT_LIST_DIR}/src/scripts/*.lua)
list(APPEND app_src ${script_src})

list(APPEND app_src ./src/main.cpp)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR}/src FILES ${app_src})
add_executable(${app} ${app_src})