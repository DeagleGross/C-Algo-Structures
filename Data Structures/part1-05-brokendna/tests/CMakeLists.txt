include_directories(../src)

include_directories(.)

add_executable(tests
    # test sources
    linked_list_tests.cpp
    dna_element_tests.cpp
    dna_repairer_tests.cpp
    # task sources
    ../src/linked_list.h
    ../src/linked_list.hpp
    ../src/dna_element.h
    ../src/dna_element.cpp
    ../src/dna_repairer.h
    ../src/dna_repairer.cpp
    # gtest sources
    gtest/gtest-all.cc
    gtest/gtest_main.cc
)

# add pthread for unix systems
if (UNIX)
    target_link_libraries(tests pthread)
endif ()
