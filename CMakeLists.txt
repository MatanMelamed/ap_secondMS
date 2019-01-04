# cmake_minimum_required(VERSION <specify CMake version here>)
project(ap_secondMS)

set(CMAKE_CXX_STANDARD 14)

add_executable(ap_secondMS main.cpp Solver.cpp Solver.h StringReverser.cpp StringReverser.h CacheManager.cpp CacheManager.h FileCacheManager.cpp FileCacheManager.h)