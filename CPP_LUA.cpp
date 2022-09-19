#include <iostream>
using namespace std;
extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

bool loadLuaFile(lua_State* L, const char* file){
    int ret = luaL_loadfile(L, file);
    if (ret)
    {
        cout << "load lua2cpp.lua failed" << endl;
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
void test1(){
    lua_State* L = luaL_newstate();
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
// CPP调用lua
void test2(){
    lua_State* L = luaL_newstate();
    if (!loadLuaFile(L, "main.lua"))
    {
        return;
    }

    // 读取全局变量
    lua_getglobal(L, "str");
    string str = lua_tostring(L, -1);
    cout << "str=" << str.c_str() << endl;

    lua_getglobal(L, "tbl");
    lua_getfield(L, -1, "name");
    str = lua_tostring(L, -1);
    cout << "tbl:name=" << str.c_str() << endl;

    // 读取函数
    lua_getglobal(L, "add");
    lua_pushnumber(L, 10);
    lua_pushnumber(L, 20);
    int ret = lua_pcall(L, 2, 1, 0);// 2表示参数格式，1表示返回值个数
    if (ret)
    {
        cout << "call add function error" << endl;
    }
    if (lua_isnumber(L, -1))
    {
        double val = lua_tonumber(L, -1);
        cout << "add result is: " << val << endl;
    }
    lua_close(L);

}




int add(lua_State* L){
    int n = lua_gettop(L);
    double a = lua_tonumber(L, -1);
    double b = lua_tonumber(L, -2);

    lua_pushnumber(L, a + b);
    lua_pushnumber(L, a * b);
    return 2;
}
int print(lua_State* L){
    if (lua_isstring(L, -1))
    {
        string str = lua_tostring(L, -1);
        cout << str.c_str() << endl;
    }
    else if (lua_isfunction(L, -1))
    {
        auto f = lua_gettop(L);
        cout << "func:" << endl;
    }
    else if (lua_isnumber(L, -1))
    {
        cout << lua_tonumber(L, -1) << endl;
    }
    else{
        cout << "unknow value";
    }
    return 0;
}
int testTable(lua_State* L){
    if (lua_istable(L, -1))
    {
        int n = lua_gettop(L);// n为table所在的位置
        lua_pushstring(L, "x");
        lua_gettable(L, n);
        double x = lua_tonumber(L, -1);

        lua_pushstring(L, "y");
        lua_gettable(L, n);
        double y = lua_tonumber(L, -1);

        cout << x << "," << y << endl;
    }
    return 0;
}
// lua 调用c++
void test3(){
    lua_State* L = luaL_newstate();

    //lua_pushcfunction(L, add);// 将函数放入栈中
    //lua_setglobal(L, "add"); // 设置lua全局函数
    lua_register(L, "add", add);
    lua_register(L, "print", print);
    lua_register(L, "testTable", testTable);

    loadLuaFile(L, "lua2cpp.lua");
    lua_close(L);
}
int main()
{
    //test1();
    //test2();
    test3();
    system("pause");
    return 0;
}

