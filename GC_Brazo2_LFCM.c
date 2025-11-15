/*Programa para dibujar dos segmentos giratorios, unidos.*/

//LIBRERÍAS NECESARIAS
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

double VectorGlobal[4] = {50, 100, 0, 1};
double VecRot[4] = {200, 100, 0};  // Ajusta la posición inicial del segundo segmento
double center[2] = {250, 250};

typedef struct {
    double posicion[4];
    double matriz[4][4];
} body;

void Matriz_X_Vector(double matrix[4][4], double vector[4], double *c) {
    for (int i = 0; i < 4; i++)
        c[i] = matrix[i][0] * vector[0] +
               matrix[i][1] * vector[1] +
               matrix[i][2] * vector[2] +
               matrix[i][3] * vector[3];
}

void rotar(double *vector, double angle) {
    double seno = sin(angle);
    double coseno = cos(angle);

    double vectortemp[4];

    double matrizRot[4][4] = {
        {coseno, -seno, 0, 0},
        {seno, coseno, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    Matriz_X_Vector(matrizRot, vector, vectortemp);

    for (int i = 0; i < 4; i++)
        vector[i] = vectortemp[i];
}

void trasladar(double *vector, double *vectorout) {
    double matrizTras[4][4] = {
        {1, 0, 0, center[0]},
        {0, 1, 0, center[1]},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    Matriz_X_Vector(matrizTras, vector, vectorout);
}

static void init01(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

static void display01(void) {
    double vectortemp[4];
    trasladar(VectorGlobal, vectortemp);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();
    glBegin(GL_LINES);
    glVertex3f(center[0], center[1], 0);
    glVertex3f(vectortemp[0], vectortemp[1], vectortemp[2]);
    glEnd();

    // Ajusta la longitud del segundo segmento
    double secondSegmentLength = 100.0;
    double secondSegmentEnd[4];
    trasladar(VecRot, secondSegmentEnd);
    for (int i = 0; i < 3; i++) {
        secondSegmentEnd[i] = vectortemp[i] + (secondSegmentEnd[i] - vectortemp[i]) * secondSegmentLength / sqrt(pow(secondSegmentEnd[0] - vectortemp[0], 2) + pow(secondSegmentEnd[1] - vectortemp[1], 2));
    }

    glBegin(GL_LINES);
    glVertex3f(vectortemp[0], vectortemp[1], vectortemp[2]);
    glVertex3f(secondSegmentEnd[0], secondSegmentEnd[1], secondSegmentEnd[2]);
    glEnd();

    glPopMatrix();
    glFlush();
}

static void reshape01(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        gluOrtho2D(0.0, 500.0, 0.0, 500.0 * (GLdouble)h / (GLdouble)w);
    } else {
        gluOrtho2D(0.0, 500.0 * (GLdouble)w / (GLdouble)h, 0.0, 500.0);
    }
}

static void keyboard01(unsigned char key, int x, int y) {
    if ((key == 0x1b) || (key == 'q') || (key == 'Q'))
        exit(0);
    else if ((key == 'R') || (key == 'r')) {
        printf("Vector Inicial %f, %f, %f\n", VectorGlobal[0], VectorGlobal[1], VectorGlobal[2]);
        rotar(VectorGlobal, -.1);
        rotar(VecRot, -.1);
        printf("Vector final %f, %f, %f\n", VectorGlobal[0], VectorGlobal[1], VectorGlobal[2]);
    }
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("BRACITO ^.^");

    init01();

    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);

    printf("Renderer: %s\n", renderer);
    printf("Versión de OpenGL que soporta: %s\n", version);
    glutDisplayFunc(display01);
    glutReshapeFunc(reshape01);
    glutKeyboardFunc(keyboard01);
    glutMainLoop();
    return 0;
}
