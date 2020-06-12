cmake_minimum_required(VERSION 3.13)
project(Project4)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

set(CMAKE_CXX_STANDARD 14)

add_executable(Project4 main.cpp)


if(Boost_FOUND)

    target_link_libraries(Project3 ${Boost_LIBRARIES})

endif()

