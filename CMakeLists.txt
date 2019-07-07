cmake_minimum_required(VERSION 3.14)
project(final C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(mathlib)
add_subdirectory(drawings)

add_executable(final main.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(final Mathlib Drawings ${GTK3_LIBRARIES})