cmake_minimum_required(VERSION 3.19)

project(LuaTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    functions.h
    main.cpp
)

# Define the script files
set(SCRIPT_FILES
    test0.lua
    test1.lua
    test2.lua
    test3.lua
)

# Add the script files to the project
add_custom_target(Scripts
    SOURCES ${SCRIPT_FILES}
)

# in its own Scripts-"folder" in the IDE
add_executable(LuaTest ${SOURCES})

# Adding External library:
# Linking static!!!
# ----------------
#Using the version that is included with the project:
# Add include directory
target_include_directories(LuaTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Lua/include)
# Add lib directory
if(MSVC)
target_link_libraries(LuaTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Lua/lib/lua5.4.3-static.lib)
elseif(APPLE)
target_link_libraries(LuaTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Lua/lib/liblua.a)
endif()
