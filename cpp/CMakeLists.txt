cmake_minimum_required(VERSION 3.20)

project("PersonnalLibrary")

add_library("NB_LIB" ScopedTimer/ScopedTimer.hpp Arena/Arena.h UnorderedVector/UnorderedVector.h)
set_target_properties("NB_LIB" PROPERTIES LINKER_LANGUAGE CXX)

# Testing
set(CMAKE_CXX_STANDARD 20)
add_executable(scoped_test ScopedTimer/test.cpp)
add_executable(arena_test Arena/test.cpp)
add_executable(unorderedvector_test UnorderedVector/test.cpp)