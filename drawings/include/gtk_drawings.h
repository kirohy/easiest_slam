//
// Created by kirohy on 19/07/07.
//

#ifndef FINAL_GTK_DRAWINGS_H
#define FINAL_GTK_DRAWINGS_H

static void cb_quit_clicked(GtkWidget *button, gpointer data);

static void cb_cube_clicked(GtkWidget *button, gpointer data);

static void cb_cylinder_clicked(GtkWidget *button, gpointer data);

static void cb_point_clicked(GtkWidget *button, gpointer data);

static void cb_run_clicked(GtkWidget *button, gpointer data);

static gboolean cb_get_spline_points(GtkWidget *widget, GdkEventButton *event, gpointer data);

static gboolean cb_get_object_points(GtkWidget *widget, GdkEventButton *event, gpointer data);

static void draw_spline_points(cairo_t *cr);

static void draw_spline_curve(cairo_t *cr);

static void draw_objects(cairo_t *cr);

static void draw_machine_vector(cairo_t *cr, int current_point);

static void draw_observed_points(cairo_t *cr, int current_point);

static gboolean cb_drawing_field(GtkWidget *widget, cairo_t *cr, gpointer data);

static gboolean cb_drawing_map(GtkWidget *widget, cairo_t *cr, gpointer data);

static gboolean timer_loop(GtkWidget *widget);

void gtk_window();

#endif //FINAL_GTK_DRAWINGS_H
