cmake_minimum_required(VERSION 3.0.0)
set(app "cpp-lua")
project(${app} VERSION 0.1.0)

# windows系统动态库生成lib文件命令
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(./lua501/CMakeLists.txt)
include(./lua501-clib/CMakeLists.txt)

include_directories(${CMAKE_CURRENT_LIST_DIR}/src)
set(app_src)

file(GLOB_RECURSE script_src ${CMAKE_CURRENT_LIST_DIR}/src/scripts/*.lua)
list(APPEND app_src ${script_src})

file(GLOB_RECURSE profiler_src
    ${CMAKE_CURRENT_LIST_DIR}/src/profiler/*.h
    ${CMAKE_CURRENT_LIST_DIR}/src/profiler/*.c
    ${CMAKE_CURRENT_LIST_DIR}/src/profiler/*.cpp
)
list(APPEND app_src ${profiler_src})

list(APPEND app_src ./src/main.cpp ./src/case.h)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR}/src FILES ${app_src})
add_executable(${app} ${app_src})
target_link_libraries(${app} PUBLIC ${LuaLib} dbg)

# 设置工作目录为lua脚本所在目录
set_target_properties(${app} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/scripts")