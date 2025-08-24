#include "lua.hpp"  //lua include that has the extern "C" thingy internally
#include <iostream>

//to call a function defined in Lua as "div_numbers"
double luaFunction (lua_State *LS, double x, double y) {

    double result;	//return variable

	/* push functions and arguments */
    lua_getglobal(LS, "div_numbers");  /* get function to be called */
    lua_pushnumber(LS, x);   /* push 1st argument */
    lua_pushnumber(LS, y);   /* push 2nd argument */

	/* do the call (2 arguments, 1 result)
    with some error handeling
    When 4th parameter is 0, the stack will get the error message
    (lua_call() does the same thing, but without error handeling)
    lua_call(LS, 2, 1)
    */

    if (lua_pcall(LS, 2, 1, 0) != 0)
    {
        std::cout << "error running function f \n";
        //Print error message that Lua gives
        std::cout << lua_tostring(LS, -1) << std::endl;
    }
	/* retrieve result 
    test if we get a number */
    if (!lua_isnumber(LS, -1)){
        std::cout << "function 'div_numbers' must return a number \n";
		return 0;
	}

    result = lua_tonumber(LS, -1);   //-1 returns top of stack
    lua_pop(LS, 1);  /* pop returned value */

    return result;
}

//A function that can be called from Lua:
static int test_Lua (lua_State *LS)
{
    //gets the index on top of the stack
    int arg = lua_gettop(LS);
	
    //gets the number
    double d = lua_tonumber(LS, arg);

    //the fantastic function that C++ will run!
	d *= 2;

    //sends the restult to Lua:
    lua_pushnumber(LS, d);

    //tells Lua that 1 result is returned:
    return 1;
}

//Utility function for Visual Studio, that closes the terminal before we see any results
void holdWindowOpen()
{
    std::cout << "Press Enter to continue...\n";
	std::cin.get();
}
