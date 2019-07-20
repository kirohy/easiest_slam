#include <stdio.h>
#include <gtk/gtk.h>
#include <pthread.h>

#include "glut_drawings.h"
#include "gtk_drawings.h"


int main(int argc, char **argv) {
    pthread_t thread_gtk, thread_glut;
    pthread_create(&thread_gtk, NULL, (void *) gtk_window, NULL);
    pthread_create(&thread_glut, NULL, (void *) glut_window, NULL);

    pthread_join(thread_glut, NULL);
    pthread_join(thread_gtk, NULL);

    return 0;
}