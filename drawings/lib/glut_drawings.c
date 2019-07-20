//
// Created by kirohy on 19/07/20.
//

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>

#include "global_parameters.h"
#include "glut_drawings.h"

int width, height;

static void init_usr(void) {}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 外枠
    GLdouble wall_vertex[][3] = {
            {0.0,   0.0,   0.0},
            {640.0, 0.0,   0.0},
            {640.0, 640.0, 0.0},
            {0.0,   640.0, 0.0},
            {0.0,   0.0,   100.0},
            {640.0, 0.0,   100.0},
            {640.0, 640.0, 100.0},
            {0.0,   640.0, 100.0}
    };

    int face[][4] = {
            {1, 5, 6, 2},
            {4, 0, 3, 7},
            {4, 5, 1, 0},
            {3, 2, 6, 7},
            {0, 1, 2, 3},
            {4, 5, 6, 7}
    };

    GLdouble normal[][3] = {
            {1.0,  0.0,  0.0},
            {-1.0, 0.0,  0.0},
            {0.0,  -1.0, 0.0},
            {0.0,  1.0,  0.0},
            {0.0,  0.0,  -1.0},
            {0.0,  0.0,  1.0}
    };

    glPushMatrix();
    glColor3d(0.7, 0.64, 0.38);
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        glNormal3d(normal[i][0], normal[i][1], normal[i][2]);
        for (int j = 0; j < 4; j++) {
            glVertex3dv(wall_vertex[face[i][j]]);
        }
    }
    glEnd();
    glPopMatrix();

    // 床
    glPushMatrix();
    glColor3d(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, 1.0);
    for (int j = 0; j < 4; j++) {
        glVertex3dv(wall_vertex[face[4][j]]);
    }
    glEnd();
    glPopMatrix();


    // Objects
    GLdouble cube_vertex[][3] = {
            {0.0,       0.0,       0.0},
            {CUBE_SIZE, 0.0,       0.0},
            {CUBE_SIZE, CUBE_SIZE, 0.0},
            {0.0,       CUBE_SIZE, 0.0},
            {0.0,       0.0,       CUBE_SIZE},
            {CUBE_SIZE, 0.0,       CUBE_SIZE},
            {CUBE_SIZE, CUBE_SIZE, CUBE_SIZE},
            {0.0,       CUBE_SIZE, CUBE_SIZE}
    };

    glColor3d(0.0, 0.0, 1.0);

    for (int i = 0; i < ObjectNum; i++) {
        glTranslatef(ObjectList[i].x - CUBE_SIZE / 2, ObjectList[i].y - CUBE_SIZE / 2, 0.0);

        glPushMatrix();
        glBegin(GL_QUADS);
        for (int j = 0; j < 6; j++) {
            glNormal3d(normal[j][0], normal[j][1], normal[j][2]);
            for (int k = 0; k < 4; k++) {
                glVertex3dv(cube_vertex[face[j][k]]);
            }
        }
        glEnd();
        glPopMatrix();

        glTranslatef(-ObjectList[i].x + CUBE_SIZE / 2, -ObjectList[i].y + CUBE_SIZE / 2, 0.0);
    }

    // 視点移動
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(SplineDrawPoints[CurrentPoint][0], SplineDrawPoints[CurrentPoint][1], 20.0,
              SplineDrawPoints[CurrentPoint][0] + 10.0,
              SplineDrawPoints[CurrentPoint][1] + 10.0 * SplineDiff[CurrentPoint], 20.0, 0.0, 0.0, 1.0);

    glutSwapBuffers();
}

static void timer() {
    if (CurrentMode == RUN) {
        time_animation += time_interval;
    }

    glutPostRedisplay();

    glutTimerFunc(time_interval, timer, 0);

    if (time_animation >= (ACTIVE_SIZE / SPLINE_STEP + 10) * time_interval) {
        glutLeaveMainLoop();
    }
}

static void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    width = w;
    height = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double) w / (double) h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

static void init(void) {
    GLfloat light_position[] = {320.0, 320.0, 800.0, 0.0};

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void glut_window() {
    int argc = 0;
    glutInit(&argc, NULL);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Animation");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(time_interval, timer, 0);
    init();
    init_usr();
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutMainLoop();
}