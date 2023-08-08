#include <lua.h>					 
#include <lauxlib.h>					 
#include <stdio.h>
 
 
/**
 * 定义在lua中可调用的函数，要遵循规范：返回值必须为int，需传入lua_State
 */
static int test(lua_State *L);
 
int luaopen_dbg(lua_State *L);