cmake_minimum_required(VERSION 3.16)

project(LuaTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    functions.h
)

set(SOURCES
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

add_executable(LuaTest ${SOURCES} ${HEADERS})

# Adding External library:
# Linking static!!!
# ----------------
#Using the version that is included with the project:
# Add include directory
target_include_directories(LuaTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Lua/include)
# Add lib directory
target_link_libraries(LuaTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Lua/lib/lua5.4.3-static.lib)
# ----------------
