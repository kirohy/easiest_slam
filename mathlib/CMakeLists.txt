add_library(Mathlib
        STATIC
        ${CMAKE_CURRENT_LIST_DIR}/lib/matrix.c
        ${CMAKE_CURRENT_LIST_DIR}/lib/spline.c
        )

target_include_directories(Mathlib
        PUBLIC
        include
        )