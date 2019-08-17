include_directories(../src)

include_directories(gtest)
include_directories(gtest/gtest)

add_executable(xipoint_test_start 
    # point tests
    point_test.cpp
    point_array_test.cpp
    # point sources    
    ../src/xipoint.cpp
    ../src/xipoint.h
    # gtest sources
    gtest/gtest/gtest-all.cc
    gtest/gtest/gtest_main.cc
        MyOwnTests.cpp)
