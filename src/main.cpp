#include <iostream>
using namespace std;
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include "case.h"
int main()
{
    // test1();
    // cppCallLuaVar();
    // cppCallLuaTable();

    // cppCallLuaFunction();
    // luaCallCpp();
    // luaCallCppFunctionReutnTable();
    // test4();
     test5();
    //testHook();
    system("pause");
    return 0;
}
