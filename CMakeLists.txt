cmake_minimum_required(VERSION 3.22)
project(libevent_helloworld)

set(CMAKE_CXX_STANDARD 17)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

find_package(PkgConfig)
pkg_search_module(Libevent REQUIRED Libevent)
if (${Libevent_FOUND})
    message("LIBEVENT_INCLUDE_DIRS is ${Libevent_INCLUDE_DIRS},LIBEVENT_LIBRARIES is ${Libevent_LIBRARIES} in ${Libevent_LIBRARY_DIRS}")
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${Libevent_INCLUDE_DIRS})
    target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${Libevent_LIBRARY_DIRS})
    target_link_libraries(${CMAKE_PROJECT_NAME} ${Libevent_LIBRARIES})
endif ()
