#include <iostream> //cout, endl

//Lua is written in C, not C++:
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
//could also have used #include "lua.hpp", which contains the code above

#include "functions.h"

int main() {

    const std::string SCRIPT_PATH = "../../";   // "../../../" if compiled with Visual Studio

    std::cout << "Fun with Lua!\n\n";

	//Starts a new Lua state, which is like a new Lua interpreter
    lua_State* lua_vm = luaL_newstate();

	//test if the Lua state was created successfully
    if (lua_vm == NULL)
    {
        std::cout << "Lua state not generated - stopping now!\n";
        return -1;
    }

	// this is necessary to use Lua's standard libraries
	luaL_openlibs(lua_vm);


    /***** Lua is now ready *******/

	// 0. testing sending and receiving parameters:***************
			
	//send a number to Lua:
    lua_pushnumber(lua_vm, 3);
	//the name "index" is now associated with the number 3 in Lua
    lua_setglobal(lua_vm, "index");

	//runs a Lua script file
	//checks the return status of the script, e.g. if there are errors in the script or it is not found
	//Stops the program if there is an error
    int status = luaL_dofile(lua_vm, (SCRIPT_PATH + "test0.lua").c_str());
    if (status != LUA_OK) {
        const char* error_msg = lua_tostring(lua_vm, -1);
        std::cout << "Error running test0.lua: " << (error_msg ? error_msg : "Unknown error") << std::endl;
        lua_pop(lua_vm, 1); // remove error message from stack
        holdWindowOpen();
		return -1; // exit with error code
    }

	//fetches a variable from Lua
	lua_getglobal(lua_vm, "fin");	    //"fin" is pushed onto the stack inside Lua, and the value of "fin" is now on top of the stack
	int i = lua_gettop(lua_vm);			//fetches the index of the top element on the stack
	const char* p = lua_tostring(lua_vm, i);	//gets the string value of the top element on the stack

	//shows the result:

    std::cout << "0. - " << p << std::endl << std::endl;

	// 1. - getting a variable from Lua is done like this:
	
	//fetches a variable from Lua (must have run the script file first)
	lua_getglobal(lua_vm, "pille");	//"pille" is the name of the variable in Lua, which is now on top of the stack
    //bruker -1 som parameter 2. Det gir også toppen av stacken:
	//uses -1 as parameter 2. This also gives the top of the stack:
	p = lua_tostring(lua_vm, -1);	//fetches the string value of the top element on the stack
	
	std::cout << "1. - " << p << "\n\n";

	//2. simple script given in a string:
    std::cout << "2. - ";
    std::string strScript = "a = 2 + 5;\n print(a);\n";
    luaL_dostring(lua_vm, strScript.c_str());
    std::cout << std::endl;

	//3. - running a script file:
    std::cout << "3. - ";
    std::cout << "a script-file: ";
    luaL_dofile(lua_vm, (SCRIPT_PATH + "test1.lua").c_str());
    std::cout << std::endl;

    //kjører den samme scriptfila, men denne er kompilert med luac.exe
	//runs the same script file, but this one is compiled with luac.exe
    std::cout << "Compiled version:\n";
    luaL_dofile(lua_vm, (SCRIPT_PATH + "test1.out").c_str());
    std::cout << "Finished with compiled script file\n";
    std::cout << std::endl;

    //4. - runs another script file that contains a function we want to call:
    // (see the file functions.h for declarations to get this to work)
    std::cout << "4. - ";
    luaL_dofile(lua_vm, (SCRIPT_PATH + "test2.lua").c_str());

	//calls the C++ function that in turn calls the Lua function
    double res = luaFunction(lua_vm, 6.0, 2.0);

    std::cout << res << std::endl << std::endl;

	//5. - runs a C function from Lua:
	//   (c-function is in functions.h)
    std::cout << "5. - ";
	//we must register the function in Lua:
	//pushes the function itself onto the Lua stack
    lua_pushcfunction(lua_vm, test_Lua);
	//gives it a name in Lua
    lua_setglobal(lua_vm, "c_function");

    luaL_dofile(lua_vm, (SCRIPT_PATH + "test3.lua").c_str());
	
    lua_getglobal(lua_vm, "Res1");
    int j = lua_gettop(lua_vm);
    double s = lua_tonumber(lua_vm, j); // again, we could have used -1 here

    std::cout << std::endl;
    std::cout << "The C-program says that the function called from Lua gave the result: " << s << std::endl;

	//Lua must be closed:
	lua_close(lua_vm);

	// Visual Studio closes window before we can see the output, so we add this:
	holdWindowOpen(); //in functions.h

	return 0;
}
