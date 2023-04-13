#include "profiler/Profiler.h"
#include "profiler/data.h"

void Profiler::onHook(lua_State *L, lua_Debug *ar)
{
    switch (ar->event)
    {
    case LUA_HOOKCALL:
    {
        Profiler::getInstance()->onHookCall(L, ar);
        break;
    }
    case LUA_HOOKRET:
    {
        Profiler::getInstance()->onHookReturn(L, ar);
        break;
    }
    default:
        break;
    }
}
bool Profiler::init(lua_State *L)
{
    lua_sethook(L, onHook, LUA_MASKCALL | LUA_MASKRET, 0);
    return true;
}

static Profiler *instance = nullptr;
Profiler *Profiler::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Profiler();
    }
    return instance;
}

void Profiler::onHookCall(lua_State *L, lua_Debug *ar)
{
    CallTreeItem item;
    /* const char* sourceFile = luaL_tolstring(L, 1, NULL);
     printf("source: %s\n", sourceFile);
     lua_pop(L, 1);*/
    item.getStack(L);
    lua_getinfo(L, "nSl", ar);
    item.getInfo(ar);
    this->items.push_back(item);
}

void Profiler::onHookReturn(lua_State *L, lua_Debug *ar)
{
}