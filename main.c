#include <stdio.h>
#include <gtk/gtk.h>
#include "matrix.h"
#include "spline.h"
#include "gtk_drawings.h"


int main(int argc, char **argv) {
    gtk_init(&argc, &argv);

    gtk_window();

    gtk_main();

    return 0;
}