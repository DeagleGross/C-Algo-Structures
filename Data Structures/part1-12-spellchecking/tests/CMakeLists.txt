include_directories(../src)

include_directories(.)

add_executable(tests

        # tests
        hashSetTests.cpp
        dictionaryTests.cpp
        
        # sources 
        ../src/dictionary.cpp
        ../src/dictionary.h
        ../src/hashset.cpp
        ../src/hashset.h
        
        # gtest sources
        gtest/gtest-all.cc
        gtest/gtest_main.cc
        )

# add pthread for unix systems
if (UNIX)
    target_link_libraries(tests pthread)
endif ()
