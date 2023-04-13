local test = require("test-function")
test:add(1)

function foo(i)
    i = 10;
end

function bar()
    foo(100)
end

for i = 1, 2, 1 do
    foo(i)
end

bar()
