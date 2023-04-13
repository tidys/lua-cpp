local test = {}

function test:sub(arg)
    return arg - 1;
end

function test:add(arg)
    arg = 10 + arg;
    return arg + 1;
end
return test
