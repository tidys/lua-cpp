#include "profiler/data.h"
#define C_FUNCTION_FLAG "C"
void CallTreeItem::getInfo(lua_Debug* ar)
{
    if (nullptr != ar->name)
    {
        if (strcmp(ar->what, C_FUNCTION_FLAG) == 0)
        {
            // 函数是由C实现的，不是lua层的函数
            this->scriptFunction = false;
        }
        else{
            this->scriptFunction = true;
        }
        this->file = ar->short_src;
        this->line = ar->currentline;
        this->funcLineBegan = ar->linedefined;
        this->funcLineEnd = ar->lastlinedefined;
        this->func = ar->name;
        this->log();
    }
}

void CallTreeItem::getStack(lua_State* L)
{
    printf("===================================\n");
    lua_Debug  stack;
    int level = 0;
    while (lua_getstack(L, level++, &stack) != 0)
    {
        lua_getinfo(L, "fnSl", &stack);
        this->funcLineCall = stack.currentline;
        printf(" %s:%d %s\n", stack.short_src, stack.currentline, stack.name);

        for (int i=1;;i++)
        {
            const char* name = lua_getlocal(L, &stack, i);
            if (!name)
            {
                break;
            }
            if (name[0]!='(')// 临时变量 (temporary) (C temporary)
            {

              int type=  lua_type(L, -1);
              switch (type)
              {
              case LUA_TNUMBER:
                  printf("\t%d: %s = %lg\n", i, name,  lua_tonumber(L, -1));
                  break;
              case LUA_TSTRING:
                  printf("\t%d: %s = %s\n", i, name, lua_tostring(L, -1));
                  break;
              default:
                    printf("\t%d: %s = %s\n", i, name, ""/*luaL_tolstring(L, -1, NULL)*/);
                  break;
              }
            }
            lua_pop(L, 1);
        }

    }
}

void CallTreeItem::log()
{
    if (this->scriptFunction)
    {
        printf("%s:%d %s\n", this->file.c_str(), this->funcLineCall, this->func.c_str());
    }
}

