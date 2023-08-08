--require("LuaPanda").start("127.0.0.1", 8818);
package.cpath = package.cpath .. ';' .. '.\\socket\\?.dll' .. ';' .. '.\\mime\\?.dll';

print(package.cpath)
require("socket.core")

local libName = "libpdebug"
-- local libPath = "e:/proj/LuaHelper/luahelper-vscode/debugger/debugger_lib/plugins/win/x86/501/?.dll;"
-- package.cpath = package.cpath .. ';' .. libPath;
-- print(package.cpath)

-- 测试能否跳到其他lua文件里面
local v = require('./func')
print(v)
v:test()

-- package.path = package.path .. ';' .. "./?.dll"
-- print(package.path)
-- 默认就会去exe所在的目录查找dll
libName = "dbg"
local hookLib = require(libName)
if type(hookLib) == "table" then
    print("dbg is table")
    for k, v in pairs(hookLib) do
        print("table key: " .. k)
    end
    if hookLib.test then
        hookLib.test(100, "i am string")
    end
elseif type(hookLib) == "string" then
    print("dbg is string: " .. hookLib)
end
-- if status then
--     print('ok')
-- else
--     print('error')
-- end
