cmake_minimum_required(VERSION 3.30)

project(rune)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("src")

enable_testing()

add_executable(test_rune_os tests/test_rune_os.cpp)
add_test(NAME test_rune_os COMMAND $<TARGET_FILE:test_rune_os>)
