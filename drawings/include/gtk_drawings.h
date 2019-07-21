#ifndef FINAL_GTK_DRAWINGS_H
#define FINAL_GTK_DRAWINGS_H

// ボタンクリック時のコールバック
static void cb_quit_clicked(GtkWidget *button, gpointer data);

static void cb_cube_one_clicked(GtkWidget *button, gpointer data);

static void cb_cube_two_clicked(GtkWidget *button, gpointer data);

static void cb_point_clicked(GtkWidget *button, gpointer data);

static void cb_run_clicked(GtkWidget *button, gpointer data);

// Field上をクリックされたときの動作をモードごとに振り分け
static gboolean cb_identify(GtkWidget *widget, GdkEventButton *event, gpointer data);

// 補間元の点を記録
static gboolean cb_get_spline_points(GtkWidget *widget, GdkEventButton *event, gpointer data);

// オブジェクトの設置位置を記録
static gboolean cb_get_object_points(GtkWidget *widget, GdkEventButton *event, gpointer data);

// 補間元の点を表示
static void draw_spline_points(cairo_t *cr);

// 補間された曲線を表示
static void draw_spline_curve(cairo_t *cr);

// オブジェクトを表示
static void draw_objects(cairo_t *cr);

// マシンの現在位置を表示
static void draw_machine_vector(cairo_t *cr, int current_point);

// 観測点をMapに表示
static void draw_observed_points(cairo_t *cr, int current_point);

// Field描画
static gboolean cb_drawing_field(GtkWidget *widget, cairo_t *cr, gpointer data);

// Map描画
static gboolean cb_drawing_map(GtkWidget *widget, cairo_t *cr, gpointer data);

// 再描画を指示
static gboolean timer_loop(GtkWidget *widget);

// メイン
void gtk_window();

#endif //FINAL_GTK_DRAWINGS_H
