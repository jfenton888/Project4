cmake_minimum_required(VERSION 3.13)
project(Project4)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.72.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

add_executable(Project4 main.cpp boostGraph.h d_except.h heapV.cpp heapV.h matrix.cpp matrix.h maze.cpp maze.h findPath.cpp findPath.h global.cpp global.h)


if(Boost_FOUND)

    target_link_libraries(Project4 ${Boost_LIBRARIES})

endif()
