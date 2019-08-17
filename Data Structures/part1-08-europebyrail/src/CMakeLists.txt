add_executable(europe_by_rail_main
        main.cpp
        city.h
        rail_system.cpp
        rail_system.h
        service.h
        )


set(CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -stdlib=libstdc++”)