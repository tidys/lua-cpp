set(LuaLib lua5.1)

set(LUA_DIR ${CMAKE_CURRENT_LIST_DIR})
include_directories(${LUA_DIR})
file(GLOB_RECURSE lua_src ${LUA_DIR}/*.h ${LUA_DIR}/*.c ${LUA_DIR}/*.cpp)
add_library(${LuaLib} SHARED ${lua_src})
