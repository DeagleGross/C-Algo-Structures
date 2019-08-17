include_directories(../src)

include_directories(.)

add_executable(tests
    # point tests
    nice_stack_test.cpp
    nice_queue_test.cpp
    # point sources    
    ../src/NiceQueue.h
    ../src/NiceQueue.hpp
    ../src/NiceStack.h
    ../src/NiceStack.hpp
        # gtest sources
    gtest/gtest-all.cc
    gtest/gtest_main.cc
)

# add pthread for unix systems
if (UNIX)
    target_link_libraries(tests pthread)
endif ()