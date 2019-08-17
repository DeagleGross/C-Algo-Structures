cmake_minimum_required(VERSION 3.12)
project(KDZ)

set(CMAKE_CXX_STANDARD 14)

add_executable(KDZ main.cpp ReadWriter.h Debugger.h ConstValues.h EdmondsKarp.h FordFulkerson.h EfimDinitz.h AlgoHelper.h)