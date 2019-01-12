#cmake_minimum_required(VERSION 3.13)

project(ap_secondMS)

set(CMAKE_CXX_STANDARD 14)

file(GLOB algorithms "Algorithms/*.h" "Algorithms/*.cpp")
file(GLOB serverClient "Server Client/*.h" "Server Client/*.cpp")
file(GLOB solverCacher "Solver And Cacher/*.h" "Solver And Cacher/*.cpp")
file(GLOB rootLayer "*.h" "*.cpp")

add_executable(ap_secondMS ${algorithms} ${rootLayer} ${solverCacher}
        "Server Client/Try.h" "Server Client/TCP_socket.h"
        "Server Client/TCP_server.cpp"
        "Server Client/TCP_server.h" "Server Client/TCP_client.h" "Solver And Cacher/MatrixSolver.cpp" "Solver And Cacher/MatrixSolver.h")