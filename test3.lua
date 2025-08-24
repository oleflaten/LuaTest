-- we call the C function "test_Lua" - which we have called "c_function" in Lua
-- (it could be called anything, for instance the same name as in C - but to show it is actually independent...)

Res1 = c_function(12.0)

print ( "The C-function returned " ..Res1);
