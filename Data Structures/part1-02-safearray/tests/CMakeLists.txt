include_directories(../src)

include_directories(.)

add_executable(tests 
    # array tests
    safearray_test.cpp
    subject_test.cpp
    # array sources
    ../src/safearray.h
    ../src/safearray.hpp
    ../src/subject.h
    ../src/subject.cpp
    # gtest sources
    gtest/gtest-all.cc
    gtest/gtest_main.cc
)

# add pthread for unix systems
if (UNIX)
    target_link_libraries(tests pthread)
endif ()