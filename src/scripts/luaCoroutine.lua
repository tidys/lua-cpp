local co = coroutine.create(function()
    print("coroutine started")
    local value = coroutine.yield("coroutine paused");
    print("coroutine resume", value)
end)

print("main started")
-- 启动协程并传递数据
local status, result = coroutine.resume(co)
print("coroutine status:", status)
print("coroutine result:", result)

-- 继续执行协程并传递数据
status, result = coroutine.resume(co, 42)
print("coroutine status:", status)
print("coroutine result:", result)
