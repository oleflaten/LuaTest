-- 6. - using a C++ class from Lua
-- Test() creates a C++ object; ":" passes the userdata (this) to each method.

local t = Test()
t:setFloat(2.0)
print(t.number2)       -- 3  (field: use the dot)
print(t:multiply())    -- 3 * 2.0 = 6.0  (method: use the colon)
