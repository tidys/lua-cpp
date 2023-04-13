#ifndef __Profiler_H__
#define __Profiler_H__
#include "profiler/data.h"
#include <iostream>
#include <vector>
using namespace std;
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class Profiler
{
public:
    static void onHook(lua_State *L, lua_Debug *ar);
    void onHookCall(lua_State *L, lua_Debug *ar);
    void onHookReturn(lua_State *L, lua_Debug *ar);

    bool init(lua_State *L);
    static Profiler *getInstance();
private:
    std::vector<CallTreeItem> items;
};

#endif