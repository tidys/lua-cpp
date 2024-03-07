#include <iostream>
using namespace std;
#include "profiler/Profiler.h"
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

bool loadLuaFile(lua_State *L, const char *file)
{
    int ret = luaL_loadfile(L, file);
    if (ret)
    {
        cout << "load " << file << " failed" << endl;
        return false;
    }
    ret = lua_pcall(L, 0, 0, 0);
    if (ret)
    {
        cout << "pcall error" << endl;
        if (lua_isstring(L, -1))
        {
            string str = lua_tostring(L, -1);
            cout << str.c_str() << endl;
        }
        return false;
    }
    return true;
}

// 堆栈操作
void test1()
{
    lua_State *L = luaL_newstate();
    lua_pushstring(L, "i am string");
    lua_pushnumber(L, 100);

    if (lua_isstring(L, 1))
    {
        cout << lua_tostring(L, 1) << endl;
    }
    if (lua_isnumber(L, 2))
    {
        cout << lua_tonumber(L, 2) << endl;
    }
    lua_close(L);
}

void cppCallLuaTable()
{
    lua_State* L = luaL_newstate();
    luaL_dofile(L, "cppCallLuaTable.lua");

    lua_getglobal(L, "tbl"); // len=1

    if (false)
    {
        lua_getfield(L, -1, "name"); // len=2
        cout << "tbl.name=" << luaL_checkstring(L, -1) << endl;
    }

    if (true)
    {
        lua_pushstring(L, "11");   // 这个是干扰项，len=2
        lua_pushstring(L, "name"); // len=3

        // 从栈顶取出一个元素(name)并且返回把查找到的值压入栈顶
        lua_gettable(L, 1); // len=3

        cout << lua_tostring(L, -1);
    }
    if (false){
        lua_rawgeti(L, -1, 1);
        cout << "tbl[1]=" << lua_tointeger(L, -1) << endl;
        lua_pop(L, 1);

        lua_rawgeti(L, -1, 2);
        bool a = lua_istable(L, -1);
        if (a)
        {
            lua_getfield(L, -1, "id");
            cout << lua_tointeger(L, -1);
        }
    }

    lua_close(L);
}

void cppCallLuaFunction()
{
    lua_State *L = luaL_newstate();
    luaL_dofile(L, "cppCallLuaFunction.lua");

    // 读取函数
    lua_getglobal(L, "add"); // len=1
    lua_pushnumber(L, 10);   // len=2
    lua_pushnumber(L, 20);   // len=3

    // 2表示参数数量，1表示返回值个数，0表示错误处理函数在栈中的索引值，压入结果前会弹出函数和参数
    // 弹出函数地址和所有参数，并将返回值压入栈顶
    int ret = lua_pcall(L, 2, 1, 0); // len=1
    cout << "add result is: " << luaL_checkinteger(L, -1) << endl;

    lua_close(L);
}
// CPP调用lua
void cppCallLuaVar()
{
    lua_State *L = luaL_newstate();
    luaL_dofile(L, "cppCallLuaVar.lua");
    if (true)   {
        // 读取全局变量，并将其放入栈顶
        lua_getglobal(L, "str");
        // 从栈顶取出字符串数据
        cout << "str=" << luaL_checkstring(L, -1) << endl;
        lua_getglobal(L, "int");
        cout << "int=" << luaL_checkinteger(L, -1) << endl;

        cout << "len=" << lua_gettop(L) << endl;
    }
    else
    {
        cout << "len=" << lua_gettop(L) << endl;
        lua_getglobal(L, "str");
        cout << "len=" << lua_gettop(L) << endl;
        lua_getglobal(L, "int");
        cout << "len=" << lua_gettop(L) << endl;
        cout << "str=" << luaL_checkstring(L, 1) << endl;
        cout << "int=" << luaL_checkinteger(L, 2) << endl;
    }
    lua_close(L);
}

int add(lua_State *L)
{
    int n = lua_gettop(L);
    double a = lua_tonumber(L, -1);
    double b = lua_tonumber(L, -2);

    lua_pushnumber(L, a + b);
    lua_pushnumber(L, a * b);
    return 2;
}
int print(lua_State *L)
{
    if (lua_isstring(L, -1))
    {
        string str = lua_tostring(L, -1);
        cout << "[LUA] " << str.c_str() << endl;
    }
    else if (lua_isfunction(L, -1))
    {
        auto f = lua_gettop(L);
        cout << "[LUA] "
             << "func:" << endl;
    }
    else if (lua_isnumber(L, -1))
    {
        cout << "[LUA] " << lua_tonumber(L, -1) << endl;
    }
    else if (lua_istable(L, -1))
    {
        cout << "[LUA] "
             << "table:" << endl;
    }
    else
    {
        cout << "[LUA] "
             << "unknow value" << endl;
    }
    return 0;
}
void testRunEncodeLuaFile()
{
    lua_State* L = luaL_newstate();
    luaopen_base(L);
    luaL_openlibs(L);
    //lua_register(L, "print", print);
    int a = luaL_dofile(L, "test-encode.lua");
    lua_close(L);
}
int returnTable(lua_State *L)
{
    cout << "len=" << lua_gettop(L) << endl;
    lua_newtable(L);
    cout << "len=" << lua_gettop(L) << endl;
    
    lua_pushstring(L, "100cm");
    lua_pushstring(L, "200cm"); // 只会使用这个值
    cout << "len=" << lua_gettop(L) << endl;
    lua_setfield(L, -3, "height");
    lua_pop(L,1); // 把100cm pop出去
    cout << "len=" << lua_gettop(L) << endl;


    lua_pushstring(L, "age");
    cout << "len=" << lua_gettop(L) << endl;
    lua_pushstring(L, "120");
    cout << "len=" << lua_gettop(L) << endl;
    lua_rawset(L, -3);
    cout << "len=" << lua_gettop(L) << endl;


    lua_pushstring(L, "name");
    cout << "len=" << lua_gettop(L) << endl;
    lua_pushstring(L, "test");
    cout << "len=" << lua_gettop(L) << endl;
    lua_rawset(L, -3);
    cout << "len=" << lua_gettop(L) << endl;

    return 1;
}

void luaCallCppFunctionReutnTable()
{
    lua_State *L = luaL_newstate();
    luaopen_base(L);
    lua_register(L, "print", print);
    lua_register(L, "returnTable", returnTable);
    loadLuaFile(L, "lua2cpp_table.lua");

    lua_close(L);
}
void luaCoroutine()
{
    lua_State* L = luaL_newstate();
    luaopen_base(L);
    luaL_openlibs(L);
    loadLuaFile(L, "luaCoroutine.lua");
    lua_close(L);
}
void luaCallCpp()
{
    lua_State *L = luaL_newstate();

    // lua_pushcfunction(L, add);// 将函数放入栈中
    // lua_setglobal(L, "add"); // 设置lua全局函数
    lua_register(L, "add", add);
    lua_register(L, "print", print);
    lua_register(L, "returnTable", returnTable);

    luaL_dofile(L, "lua2cpp.lua");
    lua_close(L);
}
void test4()
{
    lua_State *L = luaL_newstate();
    loadLuaFile(L, "table.lua");
    lua_close(L);
}

int count1 = 0;
void onHookMaskLine(lua_State *L, lua_Debug *ar)
{
    printf("c++ count: %d\n", ++count1);
}

void test5()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    Profiler::getInstance()->init(L);
    lua_register(L, "print", print);
    luaL_dofile(L, "test.lua");
    lua_close(L);
}
void testLoadCLib()
{
    LUA_VERSION;
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    loadLuaFile(L, "loadCLib.lua");
    lua_close(L);
}
void testHook()
{
    lua_State *L = luaL_newstate();
    lua_register(L, "print", print);
    luaL_dofile(L, "hook.lua");
    lua_close(L);
}
