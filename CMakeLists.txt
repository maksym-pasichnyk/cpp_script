cmake_minimum_required(VERSION 3.26)
project(cpp_script)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API 2182bf5c-ef0d-489a-91da-49dbc3090d2a)
string(CONCAT CMAKE_EXPERIMENTAL_CXX_SCANDEP_SOURCE
        "${CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS}"
        " -format=p1689"
        " --"
        " <CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS>"
        " -x c++ <SOURCE> -c -o <OBJECT>"
        " -MT <DYNDEP_FILE>"
        " -MD -MF <DEP_FILE>"
        " > <DYNDEP_FILE>")

add_executable(cpp_script src/main.cpp)
target_sources(cpp_script
    PUBLIC
    FILE_SET cpp_script_modules
    TYPE CXX_MODULES
    FILES
        src/ir.cc
        src/gc.cc
        src/lib.cc
        src/enum.cc
        src/token.cc
        src/ast.cc
)