//
// Created by kirohy on 19/07/07.
//

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include "gtk_drawings.h"
#include "global_parameters.h"
#include "map_calculator.h"

int ActiveOffset = (WINDOW_SIZE - ACTIVE_SIZE) / 2;
int BasicOffset = (WINDOW_SIZE - MAP_SIZE) / 2;

static void cb_quit_clicked(GtkWidget *button, gpointer data) {
    gtk_main_quit();
}

static void cb_cube_clicked(GtkWidget *button, gpointer data) {
    CurrentMode = PUT_CUBE;
}

static void cb_cylinder_clicked(GtkWidget *button, gpointer data) {
    CurrentMode = PUT_CYLINDER;
}

static void cb_point_clicked(GtkWidget *button, gpointer data) {
    CurrentMode = PUT_POINT;
}

static void cb_run_clicked(GtkWidget *button, gpointer data) {
    CurrentMode = RUN;
}

static gboolean cb_get_spline_points(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    if (SplinePoints.num < MAX_POINTS && event->button == 1 && event->x > ActiveOffset &&
        event->x < WINDOW_SIZE - ActiveOffset && event->y > ActiveOffset &&
        event->y < WINDOW_SIZE - ActiveOffset && CurrentMode == POINT) {
        SplinePoints.num += 1;
        SplinePoints.xy[SplinePoints.num - 1][0] = (int) event->x - ActiveOffset;
        SplinePoints.xy[SplinePoints.num - 1][1] = WINDOW_SIZE - ActiveOffset - (int) event->y;
    }

    return TRUE;
}

static void cb_drawing_spline(cairo_t *cr) {
    if (SplinePoints.num >= 3) {
        calc_draw_points();
        cairo_set_line_width(cr, 3);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);

        for (int i = 0; i < ACTIVE_SIZE / SPLINE_STEP; i++) {
            cairo_move_to(cr, (double) SplineDrawPoints[i][0] + (double) ActiveOffset,
                          WINDOW_SIZE - ActiveOffset - (double) SplineDrawPoints[i][1]);
            cairo_line_to(cr, (double) SplineDrawPoints[i + 1][0] + ActiveOffset,
                          WINDOW_SIZE - ActiveOffset - (double) SplineDrawPoints[i + 1][1]);
            cairo_stroke(cr);
        }
    }
}

static gboolean cb_drawing_field(GtkWidget *widget, cairo_t *cr, gpointer data) {
    // const cairo_rectangle_int_t rec = {30, 30, 640, 640};
    // cairo_region_t *reg = cairo_region_create_rectangle(&rec);

    GdkWindow *window;
    cairo_region_t *reg;
    GdkDrawingContext *context;

    window = gtk_widget_get_window(widget);
    reg = cairo_region_create();
    context = gdk_window_begin_draw_frame(window, reg);

    cr = gdk_drawing_context_get_cairo_context(context);

    int offset = 30;
    int max = MAP_SIZE;

    {
        double wall = 20.0; // この半分が外枠の太さ
        cairo_set_line_width(cr, wall);
        cairo_set_source_rgb(cr, 0.7, 0.64, 0.38);

        cairo_rectangle(cr, offset, offset, max, max);
        cairo_stroke_preserve(cr); // 外枠

        cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
        cairo_fill(cr);
    }

    // SplinePoints描画
    {
        double point_size = 5.0;
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
        cairo_set_line_width(cr, 1.0);
        for (int i = 0; i < SplinePoints.num; i++) {
            cairo_rectangle(cr, SplinePoints.xy[i][0] + ActiveOffset - point_size / 2.0,
                            WINDOW_SIZE - ActiveOffset - point_size / 2.0 - SplinePoints.xy[i][1], point_size,
                            point_size);
            cairo_stroke_preserve(cr);
            cairo_fill(cr);
        }
    }

    cb_drawing_spline(cr);

    // cairo_destroy(cr);
    gdk_window_end_draw_frame(window, context);
    return FALSE;
}

static gboolean cb_drawing_map(GtkWidget *widget, cairo_t *cr, gpointer data) {
    // const cairo_rectangle_int_t rec = {30, 30, 640, 640};
    // cairo_region_t *reg = cairo_region_create_rectangle(&rec);

    GdkWindow *window;
    cairo_region_t *reg;
    GdkDrawingContext *context;

    window = gtk_widget_get_window(widget);
    reg = cairo_region_create();
    context = gdk_window_begin_draw_frame(window, reg);

    cr = gdk_drawing_context_get_cairo_context(context);

    int offset = 30;
    int max = 640;

    {
        double wall = 20.0; // この半分が外枠の太さ

        cairo_rectangle(cr, offset - wall / 2, offset - wall / 2, max + wall, max + wall);

        cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
        cairo_fill(cr);
    }

    // cairo_destroy(cr);
    gdk_window_end_draw_frame(window, context);
    return FALSE;
}

static gboolean timer_loop(GtkWidget *widget) {
    if (gtk_widget_get_window(widget) == NULL) {
        return FALSE;
    }

    gtk_widget_queue_draw(widget);

    return TRUE;
}

void gtk_window() {
    GtkWidget *window;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "EasiestSLAM");

    // gtk_widget_set_size_request(window, 300, 200);
    {
        GtkWidget *hbox;
        hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
        gtk_container_add(GTK_CONTAINER(window), hbox);
        {
            GtkWidget *vbox;
            vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            {
                GtkWidget *cube;
                GtkWidget *cylinder;
                GtkWidget *point;
                GtkWidget *run;
                GtkWidget *quit;

                cube = gtk_button_new_with_label("Put Cubes");
                cylinder = gtk_button_new_with_label("Put Cylinders");
                point = gtk_button_new_with_label("Set Points");
                run = gtk_button_new_with_label("Run");
                quit = gtk_button_new_with_label("Quit");

                gtk_box_pack_start(GTK_BOX(vbox), cube, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vbox), cylinder, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vbox), point, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vbox), run, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vbox), quit, TRUE, TRUE, 0);

                g_signal_connect(cube, "clicked", G_CALLBACK(cb_cube_clicked), NULL);
                g_signal_connect(cylinder, "clicked", G_CALLBACK(cb_cylinder_clicked), NULL);
                g_signal_connect(point, "clicked", G_CALLBACK(cb_point_clicked), NULL);
                g_signal_connect(run, "clicked", G_CALLBACK(cb_run_clicked), NULL);
                g_signal_connect(quit, "clicked", G_CALLBACK(cb_quit_clicked), NULL);
            }
            gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 0);
        }
        {
            GtkWidget *vbox;
            vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            {
                GtkWidget *label;
                GtkWidget *field;

                char *str = "Field";

                label = gtk_label_new(NULL);
                gtk_label_set_markup(GTK_LABEL(label), str);
                gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);

                field = gtk_drawing_area_new();
                gtk_widget_set_size_request(field, 700, 700);

                g_signal_connect(field, "draw", G_CALLBACK(cb_drawing_field), NULL);
                g_signal_connect(field, "button_press_event", G_CALLBACK(cb_get_spline_points), NULL);
                g_timeout_add(50, (GSourceFunc) timer_loop, field);
                gtk_widget_set_events(field,
                                      GDK_BUTTON_PRESS_MASK
                );

                gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vbox), field, TRUE, TRUE, 0);

            }
            gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 5);
        }
        {
            GtkWidget *vbox;
            vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            {
                GtkWidget *label;
                GtkWidget *map;

                char *str = "Map";

                label = gtk_label_new(NULL);
                map = gtk_drawing_area_new();
                gtk_widget_set_size_request(map, 700, 700);

                gtk_label_set_markup(GTK_LABEL(label), str);

                gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);

                gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vbox), map, TRUE, TRUE, 0);

                g_signal_connect(map, "draw", G_CALLBACK(cb_drawing_map), NULL);
            }
            gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 5);
        }
    }
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
}
