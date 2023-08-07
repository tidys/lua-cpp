#include "dbg.h"
static int test(lua_State *L)
{
    size_t len = 0;
    int num = luaL_checkinteger(L, 1);
    const char *str = luaL_checklstring(L, 2, &len);
    printf("come from test: num = %d	str = %s	len = %d\n", num, str, len);
    return 0;
}

int luaopen_dbg(lua_State *L)
{
    luaL_Reg l[] =
        {
            {"test", test},
            {NULL, NULL}};

    // luaL_newlib(L, l); // lua504才有这个函数
    luaL_register(L, "dbg", l);
    return 1;
}