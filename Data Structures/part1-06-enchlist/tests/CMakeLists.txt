include_directories(../src)

include_directories(.)

add_executable(tests
    # list tests
    bidi_linked_list_test.cpp
    # list sources    
    ../src/bidi_linked_list.h
    ../src/bidi_linked_list.hpp
        # gtest sources
    gtest/gtest-all.cc
    gtest/gtest_main.cc
)

# add pthread for unix systems
if (UNIX)
    target_link_libraries(tests pthread)
endif ()