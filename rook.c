#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

struct point
{
    float x;
    float y;
    float z;
};

struct point spherical(float alpha, float beta, float r)
{
    struct point p;
    p.x = r * cos(alpha) * cos(beta);
    p.y = r * sin(alpha) * cos(beta);
    p.z = r * sin(beta);
    return p;
}

double Sx = 0.0;
double Sy = 0.0;
double Sz = 0.0;
int dead = 1;
int pc_color = 1;

double Pawn_upper_sphere = 0.0;
double Pawn_upper_spherex = 0.0;
double Pawn_upper_ring = 0.0;
int new_index = 0;
int piece = 0;
int color = 0;

void drawSmoothUnityEllipsoidPatch(float a1, float a2, float b1, float b2)
{
    int na = 32;
    int nb = 16;

    float alpha;
    float dalpha = (a2 - a1) / na;
    float beta;
    float dbeta = (b2 - b1) / nb;

    beta = b2;
    for (int j = 0; j < nb; j++, beta -= dbeta)
    {
        alpha = a1;
        for (int i = 0; i < na; i++, alpha += dalpha)
        {
            struct point p;
            glBegin(GL_POLYGON);

            p = spherical(alpha, beta, 1);
            glNormal3f(p.x, p.y, p.z);
            glVertex3f(p.x, p.y, p.z);

            p = spherical(alpha + dalpha, beta, 1);
            glNormal3f(p.x, p.y, p.z);
            glVertex3f(p.x, p.y, p.z);

            p = spherical(alpha + dalpha, beta - dbeta, 1);
            glNormal3f(p.x, p.y, p.z);
            glVertex3f(p.x, p.y, p.z);

            p = spherical(alpha, beta - dbeta, 1);
            glNormal3f(p.x, p.y, p.z);
            glVertex3f(p.x, p.y, p.z);

            glEnd();
        }
    }
}

void draw_bottom() {
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);
    glRotated(-90, 1.0f, 0.0f, 0.0f);
    glScalef(1.5, 1.5, 0.8);
    drawSmoothUnityEllipsoidPatch(0, 2 * M_PI, 0, M_PI / 2);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.9f, 0.0f);
    glRotated(-90, 1.0f, 0.0f, 0.0f);
    glScalef(1.4, 1.4, 1.0);
    drawSmoothUnityEllipsoidPatch(0, 2 * M_PI, 0, M_PI / 2);
    glPopMatrix();
}


void draw_rook(int new_index2) {
    new_index = new_index2;
    piece = 4;
    color = pc_color;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz);

    glScalef(0.29 / dead, 0.30 / dead, 0.29 / dead);
    GLUquadricObj* quadratic;

    // topmost cylinder
    glPushMatrix();
    glTranslatef(0.0, 4.0, 0.0);
    quadratic = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 1.0f, 1.0f, 1.0f, 32, 32);
    glScalef(1.0, 1.0, 0.1);
    glutSolidTorus(0.9f, 0.1f, 50, 50);
    glPopMatrix();

    // top covering
    glPushMatrix();
    glTranslatef(0.0, 5.0, 0.0);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.0, 1.0, 0.1);
    glutSolidTorus(0.9f, 0.1f, 50, 50);
    glPopMatrix();

    // middle cylinder
    glPushMatrix();
    glTranslatef(0.0, 1.0, 0.0);
    quadratic = gluNewQuadric();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 1.1f, 0.6f, 3.4f, 32, 32);
    glPopMatrix();

    // inverted cylinder
    glPushMatrix();
    glTranslatef(0.0, 4.5, 0.0);
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.85f, 0.55f, 3.4f, 32, 32);
    glPopMatrix();

    // middle covering
    glPushMatrix();
    glTranslatef(0.0, 3.4, 0.0);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.0, 1.0, 3.5);
    glutSolidTorus(0.455f, 0.3f, 50, 50);
    glPopMatrix();

    // bottom Ellipsoid
    draw_bottom();
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Llama a la función para dibujar la torre
    draw_rook(new_index);

    glutSwapBuffers();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

static void keyboard(unsigned char key, int x, int y) {
    if ((key == 0x1b) || (key == 'q') || (key == 'Q'))
        exit(0);

    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(300, 50);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Chess Rook");

    glEnable(GL_DEPTH_TEST);
    init();

    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -5, 5);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported: %s\n", version);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
