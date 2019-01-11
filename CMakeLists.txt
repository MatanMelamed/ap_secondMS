# cmake_minimum_required(VERSION <specify CMake version here>)
project(ap_secondMS)

set(CMAKE_CXX_STANDARD 14)

#add_executable(ap_secondMS main.cpp )
add_executable(ap_secondMS Searchable.h SearchableMatrix.cpp SearchableMatrix.h
        State.h main.cpp Searcher.h BestFS.h PStateUnorderedSet.h
        BFS.h)