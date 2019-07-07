#include <stdio.h>
#include <gtk/gtk.h>
#include "matrix.h"
#include "spline.h"
#include "gtk_drawings.h"


int main(int argc, char **argv) {
    /*
    SplinePoints Points;
    matrix base;
    mat_alloc(&base, MAX_POINTS, 2);
    base.main[0][0] = 0.0;
    base.main[0][1] = 0.0;
    base.main[1][0] = 8.0;
    base.main[1][1] = 8.0;
    base.main[2][0] = 18.0;
    base.main[2][1] = 4.0;

    if (spline_points_new(&Points, 3, base)) {
        printf("hoge!\n");
        return 1;
    }

    matrix answer;
    mat_alloc(&answer, 8, 1);
    spline(Points, &answer);
    mat_print(&answer);
    */

    gtk_init(&argc, &argv);

    gtk_window();

    gtk_main();

    return 0;
}