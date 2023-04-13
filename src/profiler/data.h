#ifndef __ProfilerData_H__
#define __ProfilerData_H__

#include <iostream>
using namespace std;
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class CallTreeItem
{
public:
    int line = 0; // 行号
    string func;  // 函数名
    string file;  // 文件名
    float time;   // 消耗时间
    int funcLineCall = -1;// 调用函数的行号
    int funcLineBegan = -1;// 函数定义的开始行号
    int funcLineEnd = -1; // 函数定义的结尾行号
    void getInfo(lua_Debug* ar);
    void getStack(lua_State* L);
    bool scriptFunction = true;
private:
    void log();
};
#endif
