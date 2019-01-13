cmake_minimum_required(VERSION 3.13)

project(ap_secondMS)

set(CMAKE_CXX_STANDARD 14)

file(GLOB algorithms "Algorithms/*.h" "Algorithms/*.cpp")
file(GLOB serverClient "Server Client/*.h" "Server Client/*.cpp")
file(GLOB solverCacher "Solver And Cacher/*.h" "Solver And Cacher/*.cpp")
file(GLOB etc "Etc/*.h" "Etc/*.cpp")
file(GLOB rootLayer "main.cpp")

add_executable(ap_secondMS ${algorithms} ${rootLayer} ${etc} ${serverClient} "Server Client/TCP_client.cpp" "Server Client/MyParallelServer.cpp" "Server Client/MyParallelServer.h")