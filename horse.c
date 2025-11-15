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

//Variables globales para el ángulo de rotación de esferas y anillo.
double esfera_superior01 = 0.0;
double esfera_superior02 = 0.0;
double anillo_superior = 0.0;

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

void draw_bottom()
{
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

void d(int new_index2)
{
    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 2 y establece el color a blanco.
    pieza = 1;
    glColor3f(1.0, 1.0, 1.0); //blanco.

    //Configuración de la matriz de modelo-vista.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz); //trasladar la figura en las coordenadas (Sx, Sy, Sz).
    glScalef(0.29 / dd, 0.3 / dd, 0.29 / dd); //escalar la figura.

    //Dibuja la esfera superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0, esfera_superior01, -esfera_superior02); //translada la esfera a la posición especificada en el espacio tridimensional.
    glutSolidSphere(0.7f, 50, 50); //dibuja una esfera sólida con radio 0.7 utilizando GLUT.
    glPopMatrix(); //restaura la matriz a la guardada previamente.


    //Dibuja el anillo de elipse superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.

    //Translada y rota el anillo de elipse a una posición específica.
    glTranslatef(0, esfera_superior01, -esfera_superior02);
    glRotated(-90, 1.0f, 0.0f, 0.0f);
    glPushMatrix(); //guarda la matriz de transformación actual en una pila interna.
    glScalef(1.0, 1.0, 0.2); //escala el anillo de elipse en los ejes x, y, y z.
    glutSolidTorus(0.8f, 0.2f, 40, 40);//dibuja el toro sólido para formar el anillo de elipse.
    glPopMatrix(); //restaura la matriz a la guardada previamente en la pila interna.
    glPopMatrix(); //restaura la matriz a la guardada previamente en la pila.

    //Dibuja un cono.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 1.0f, 0.0f); //translada el cono a una posición específica en la escena.
    glRotated(-90, 1.0f, 0.0f, 0.0f);//rota el cono -90 grados alrededor del eje x.
    glutSolidCone(1.0f, 3.4f, 50, 50);// Dibuja el cono sólido con radio base 1.0, altura 3.4 y con 50 segmentos en la base y 50 en la altura.
    glPopMatrix(); // Restaura la matriz a la guardada previamente en la pila.

//Dibuja un toro sólido en la parte inferior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 1.3f, 0.0f); //translada el toro a una posición específica en la escena.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el toro en los ejes x, y, y z. En este caso, se reduce la escala en el eje y (altura) mientras se mantiene la escala en los otros ejes.
    glutSolidTorus(1.0f, 0.3f, 50, 50); // dibuja un toro sólido con radio exterior 1.0, radio interior 0.3, y con 50 segmentos en la base y 50 en la altura.
    glPopMatrix(); //restaura la matriz a la guardada previamente en la pila.
    dibujar_elipsoide(0, 2 * M_PI, 0, M_PI / 2); //llama a la función dibujar_elipsoide para dibujar el elipsoide superior.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Llama a la función para dibujar la pieza de ajedrez
    drawChessPiece(new_index);

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
    glutCreateWindow("Chess Piece");

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
