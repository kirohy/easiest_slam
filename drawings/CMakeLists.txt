add_library(Drawings
        STATIC
        ${CMAKE_CURRENT_LIST_DIR}/lib/gtk_drawings.c
        )

target_include_directories(Drawings
        PUBLIC
        include
        )

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(Drawings ${GTK3_LIBRARY_DIRS})
