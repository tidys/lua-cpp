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
    testRunEncodeLuaFile();
     //test1();
     //cppCallLuaVar();
     //cppCallLuaTable();

    // cppCallLuaFunction();
     //luaCallCpp();
     //luaCallCppFunctionReutnTable();
    //luaCoroutine();
    // test4();
    // test5();
     //testLoadCLib();
    //testHook();
    system("pause");
    return 0;
}
