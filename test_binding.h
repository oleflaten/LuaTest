#include "test.h"
#include "lua.hpp"   //lua include that has the extern "C" thingy internally
#include <cstring>

//Constructor: C++ object -> Lua userdata instance, returned to the script.
static int new_Test(lua_State* L)
{
    Test* t = new Test();
    Test** slot = (Test**)lua_newuserdata(L, sizeof(Test*));
    *slot = t;
    luaL_getmetatable(L, "Test");
    lua_setmetatable(L, -2);
    return 1;                       // returns the userdata
}

//Garbage collector: frees the C++ object when Lua collects the userdata.
static int test_gc(lua_State* L)
{
    Test* t = *(Test**)luaL_checkudata(L, 1, "Test");
    delete t;
    return 0;
}

//Method: multiplies number2 * number. Recovered "this" from the userdata (arg 1).
static int test_multiply(lua_State* L)
{
    Test* t = *(Test**)luaL_checkudata(L, 1, "Test");
    lua_pushnumber(L, t->multiply());
    return 1;
}

//Method: sets the private float member.
static int test_setFloat(lua_State* L)
{
    Test* t = *(Test**)luaL_checkudata(L, 1, "Test");
    t->setFloat((float)luaL_checknumber(L, 2));
    return 0;
}

//__index: resolves fields/methods by name.
static int test_index(lua_State* L)
{
    Test* t      = *(Test**)luaL_checkudata(L, 1, "Test");
    const char* key = luaL_checkstring(L, 2);
    if (std::strcmp(key, "number2") == 0) { lua_pushinteger(L, t->number2); return 1; }
    if (std::strcmp(key, "multiply") == 0) { lua_pushcfunction(L, test_multiply); return 1; }
    if (std::strcmp(key, "setFloat") == 0) { lua_pushcfunction(L, test_setFloat); return 1; }
    return 0;                        // nil -> nil result
}

//Registers the "Test" metatable and the "Test" constructor. Call once.
void register_Test(lua_State* L)
{
    if (luaL_newmetatable(L, "Test") == 0)
    {
        return;   // metatable already created
    }

    lua_pushcfunction(L, test_gc);     lua_setfield(L, -2, "__gc");
    lua_pushcfunction(L, test_index);  lua_setfield(L, -2, "__index");
    lua_pushcfunction(L, new_Test);    lua_setglobal(L, "Test");
}
