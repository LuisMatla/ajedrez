#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

float rotationAngleX = 0.0;
float rotationAngleY = 0.0;
float rotationAngleZ = 0.0;

struct punto {
    float x;
    float y;
    float z;
};

struct punto esferico(float alpha, float beta, float r) {
    struct punto p;
    p.x = r * cos(alpha) * cos(beta);
    p.y = r * sin(alpha) * cos(beta);
    p.z = r * sin(beta);
    return p;
}

double Sx = 0.0;
double Sy = 0.0;
double Sz = 0.0;
int dd = 1;

double esfera_superior01 = 0.0;
double esfera_superior02 = 0.0;
double anillo_superior = 0.0;
int indice = 0;
int indice02;
int pieza = 0;

void dibujar_elipsoide(float a1, float a2, float b1, float b2) {
    int na = 32;
    int nb = 16;

    float alpha;
    float dalpha = (a2 - a1) / na;
    float beta;
    float dbeta = (b2 - b1) / nb;

    beta = b2;
    for (int j = 0; j < nb; j++, beta -= dbeta) {
        alpha = a1;
        for (int i = 0; i < na; i++, alpha += dalpha) {
            struct punto p;
            glBegin(GL_POLYGON);

            p = esferico(alpha, beta, 1);
            glNormal3f(p.x, p.y, p.z);
            glVertex3f(p.x, p.y, p.z);

            p = esferico(alpha + dalpha, beta, 1);
            glNormal3f(p.x, p.y, p.z);
            glVertex3f(p.x, p.y, p.z);

            p = esferico(alpha + dalpha, beta - dbeta, 1);
            glNormal3f(p.x, p.y, p.z);
            glVertex3f(p.x, p.y, p.z);

            p = esferico(alpha, beta - dbeta, 1);
            glNormal3f(p.x, p.y, p.z);
            glVertex3f(p.x, p.y, p.z);

            glEnd();
        }
    }
}

void dibujar_fondo() {
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);
    glRotated(-90, 1.0f, 0.0f, 0.0f);
    glScalef(1.5, 1.5, 0.8);
    dibujar_elipsoide(0, 2 * M_PI, 0, M_PI / 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.9f, 0.0f);
    glRotated(-90, 1.0f, 0.0f, 0.0f);
    glScalef(1.4, 1.4, 1.0);
    dibujar_elipsoide(0, 2 * M_PI, 0, M_PI / 2);
    glPopMatrix();
}

void dibujar_Torre(float x, float y, float z) {
    // Establece el índice actual.
    indice = indice02;
    glTranslatef(x + 1, y, z + 0.65 );
    // Define la pieza actual como 4 y establece el color a blanco.
    indice = indice02;
    pieza = 4;
    glColor3f(1.0, 1.0, 1.0); // blanco.

    // Configuración de la matriz de modelo-vista.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz); // trasladar la figura en las coordenadas (Sx, Sy, Sz).

    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);  // Rotación de 90 grados alrededor del eje x.

    glScalef(0.29 / dd, 0.30 / dd, 0.29 / dd);
    GLUquadricObj *cuadratico;

    // Cilindro superior.
    glPushMatrix(); // guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0, 4.0, 0.0); // translada el cilindro superior a la posición (0.0, 4.0, 0.0) en el espacio tridimensional.
    cuadratico = gluNewQuadric(); // inicializa un objeto cuadrático.
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // rota el cilindro -90 grados alrededor del eje x.
    gluCylinder(cuadratico, 1.0f, 1.0f, 1.0f, 32, 32); // dibuja un cilindro con radio superior 1.0, radio inferior 1.0, y altura 1.0 utilizando la función proporcionada por GLUT.
    glScalef(1.0, 1.0, 0.1); // escala el cilindro en los ejes x, y, y z. En este caso, se reduce la escala en el eje z.
    glutSolidTorus(0.9f, 0.1f, 50, 50); // dibuja un toro sólido con radio mayor 0.9, radio menor 0.1 utilizando la función proporcionada por GLUT.
    glPopMatrix(); // restaura la matriz a la guardada previamente.

    // Cubierta superior.
    glPushMatrix(); // guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0, 5.0, 0.0); // translada la cubierta superior a la posición (0.0, 5.0, 0.0) en el espacio tridimensional.
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // rota la cubierta superior -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.1); // escala la cubierta superior en los ejes x, y, y z. En este caso, se reduce la escala en el eje z.
    glutSolidTorus(0.9f, 0.1f, 50, 50); // dibuja un toro sólido con radio mayor 0.9, radio menor 0.1 utilizando la función proporcionada por GLUT.
    glPopMatrix(); // restaura la matriz a la guardada previamente.

    // Cilindro medio.
    glPushMatrix(); // guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0, 1.0, 0.0); // translada el cilindro medio a la posición (0.0, 1.0, 0.0) en el espacio tridimensional.
    cuadratico = gluNewQuadric(); // inicializa un objeto cuadrático para usar en la creación del cilindro.
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // rota el cilindro medio -90 grados alrededor del eje x.
    gluCylinder(cuadratico, 1.1f, 0.6f, 3.4f, 32, 32); // dibuja un cilindro sólido con radio de la base 1.1, radio del tope 0.6, altura 3.4 utilizando la función gluCylinder.
    glPopMatrix(); // restaura la matriz a la guardada previamente.

    // Cilindro invertido.
    glPushMatrix(); // guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0, 4.5, 0.0); // translada el cilindro invertido a la posición (0.0, 4.5, 0.0) en el espacio tridimensional.
    cuadratico = gluNewQuadric(); // inicializa un objeto cuadrático para usar en la creación del cilindro.
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // rota el cilindro invertido 90 grados alrededor del eje x.
    gluCylinder(cuadratico, 0.85f, 0.55f, 3.4f, 32, 32); // dibuja un cilindro sólido invertido con radio de la base 0.85, radio del tope 0.55, altura 3.4 utilizando la función gluCylinder.
    glPopMatrix(); // restaura la matriz a la guardada previamente.

    // Cubierta central.
    glPushMatrix(); // guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0, 3.4, 0.0); // translada la cubierta central a la posición (0.0, 3.4, 0.0) en el espacio tridimensional.
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // rota la cubierta central -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 3.5); // escala la cubierta central en los ejes x, y, y z. En este caso, se amplía la escala en el eje z mientras que se mantiene la escala en los otros ejes.
    glutSolidTorus(0.455f, 0.3f, 50, 50); // dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de la sección transversal 0.455 y radio de la sección circular 0.3.
    glPopMatrix(); // restaura la matriz a la guardada previamente.
    dibujar_fondo();
    glPopMatrix();
}

//Esta función dibuja un cubo para que se pueda hacer el tablero.
void dibujar_cubo(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glBegin(GL_QUADS);

    glVertex3f(-0.5, -0.5, 0.5); // Vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5);  // Vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5);   // Vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5);  // Vértice 4 de la cara frontal superior izquierda.

    glVertex3f(-0.5, -0.5, -0.5); // Vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5);  // Vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5);   // Vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5);  // Vértice 4 de la cara posterior superior izquierda.

    glVertex3f(-0.5, -0.5, 0.5); // Vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5);  // Vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); // Vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); // Vértice 4 de la cara posterior inferior izquierda.

    glVertex3f(0.5, -0.5, 0.5);  // Vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5);   // Vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5);  // Vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); // Vértice 4 de la cara posterior derecha inferior.

    glVertex3f(0.5, 0.5, 0.5);   // Vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5);  // Vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); // Vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5);  // Vértice 4 de la cara posterior superior derecha.

    glVertex3f(-0.5, 0.5, 0.5);  // Vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); // Vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); // Vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5);  // Vértice 4 de la cara posterior izquierda superior.

    glEnd();
    glPopMatrix();
}

void dibujar_tablero() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            float x = i * 1.0;  // Cambié i por j
            float y = j * 1.0;  // Cambié j por i
            float z = 0.0;

            if ((i + j) % 2 == 0) {
                glColor3f(1.0, 0.75, 0.8);
            } else {
                glColor3f(0.5, 0.0, 0.5);
            }

            dibujar_cubo(x, y, z);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up the camera
    gluLookAt(5.0, 5.0, 20.0, 0.0, 1.0, 0.0, 2.0, 2.0, 0.0);

    glRotatef(rotationAngleX, 1.0, 0.0, 0.0);
    glRotatef(rotationAngleY, 0.0, 1.0, 0.0);
    glRotatef(rotationAngleZ, 0.0, 0.0, 1.0);

    // Specify coordinates for a single cube
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    dibujar_tablero(x, y, z); // Call dibujar_cubo with specific coordinates
    dibujar_Torre(x, y, z);
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'x':
        case 'X':
            rotationAngleX += 5.0;
            break;
        case 'y':
        case 'Y':
            rotationAngleY += 5.0;
            break;
        case 'z':
        case 'Z':
            rotationAngleZ += 5.0;
            break;
        case 27:  // ESC key
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("TABLERO AJEDREZ.");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}