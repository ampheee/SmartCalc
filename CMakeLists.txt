cmake_minimum_required(VERSION 3.2)
project(SimpleCalculator)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(SimpleCalculator calculator.c calculator.h arithmetics.c interface.c)
target_link_libraries(SimpleCalculator ${GTK3_LIBRARIES})