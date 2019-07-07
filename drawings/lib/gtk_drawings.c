//
// Created by kirohy on 19/07/07.
//

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include "gtk_drawings.h"

static void cb_button_clicked(GtkWidget *button, gpointer user_data) {
    gtk_main_quit();
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
    int max = 640;

    {
        double wall = 20.0; // この半分が外枠の太さ
        cairo_set_line_width(cr, wall);
        cairo_set_source_rgb(cr, 0.7, 0.64, 0.38);

        cairo_rectangle(cr, offset, offset, max, max);
        cairo_stroke_preserve(cr); // 外枠

        cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
        cairo_fill(cr);
    }

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

                g_signal_connect(quit, "clicked", G_CALLBACK(cb_button_clicked), NULL);
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
