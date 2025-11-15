#include <GL/glut.h>
#include <stdlib.h>

static int slices = 16;
static int stacks = 16;

/* GLUT callback Handlers */

static void resize(int width, int height) {
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void) {
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t * 90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0); // color

    /* Solid sphere */
    glPushMatrix();
    glTranslated(-1.4, 0.5, -5);
    glRotated(60, 1, 0, 0);
    glRotated(a, 0, 0, 1);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();

    /* Wireframe sphere */
    glPushMatrix();
    glTranslated(1.4, 0.5, -5);
    glRotated(60, 1, 0, 0);
    glRotated(a, 0, 0, 1);
    glutWireSphere(1, slices, stacks);
    glPopMatrix();

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
    case 'q':
        exit(0);
        break;

    case '+':
        slices++;
        stacks++;
        break;

    case '-':
        if (slices > 3 && stacks > 3) {
            slices--;
            stacks--;
        }
        break;
    }

    glutPostRedisplay();
}

static void idle(void) {
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("ESFERAS ");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1, 1, 1, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glutMainLoop();

    return EXIT_SUCCESS;
}
