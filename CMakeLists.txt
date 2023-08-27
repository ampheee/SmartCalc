cmake_minimum_required(VERSION 3.2)
project(SmartCalc)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -lm")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(SmartCalc stack.c queue.c
        parse.c arithmetics.c debug.c
        interface.c calculator.c)
target_link_libraries(SmartCalc ${GTK3_LIBRARIES} m)