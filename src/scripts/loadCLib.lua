-- require("")
local libName = "libpdebug"
local libPath = "e:/proj/LuaHelper/luahelper-vscode/debugger/debugger_lib/plugins/win/x86/503/?.dll;"
package.cpath = package.cpath .. ';' .. libPath;

print(package.cpath)
local hookLib = require(libName)
if type(hookLib) == "table" then
    for k, v in pairs(hookLib) do
        print(k)
    end
else if type(hookLib) == "string" then
    print(hookLib)
end
-- if status then
--     print('ok')
-- else
--     print('error')
-- end
