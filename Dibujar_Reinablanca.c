#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

struct punto{
    float x;
    float y;
    float z;
};

struct punto esferico(float alpha, float beta, float r){
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


void dibujar_elipsoide(float a1, float a2, float b1, float b2){
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


void dibujar_Reinablanca() {

    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 3 y establece el color a blanco.
    pieza = 3;
    glColor3f(1.0, 1.0, 1.0); //blanco
    
    //Configuración de la matriz de modelo-vista y aplicando transformaciones de traslación, rotación y escala.
    glMatrixMode(GL_MODELVIEW); //establece la matriz de modelo-vista como la matriz activa.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(Sx, Sy, Sz); //traslada la figura a la posición (Sx, Sy, Sz).
    glScalef(0.33 / dd, 0.34 / dd, 0.33 / dd); //escala la figura en los ejes x, y, y z.

    //Esfera superior
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 5.9f, 0.0f); //traslada la esfera a la posición (0.0, 5.9, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la esfera -90 grados alrededor del eje x.
    glScalef(0.4, 0.4, 0.4); //escala la esfera en los ejes x, y, y z.
    glutSolidSphere(1, 50, 50); //dibuja una esfera sólida con radio 1, usando 50 segmentos en la dirección de los polos y 50 en la dirección del ecuador.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Primer dodecaedro superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 6.0f, 0.0f); //translada la figura del dodecaedro a la posición (0.0, 6.0, 0.0) en el espacio tridimensional.
    glRotated(-90, 0.0f, 1.0f, 0.0f); //rota la figura del dodecaedro -90 grados alrededor del eje y.
    glScalef(0.45, 0.1, 0.45); //escala la figura del dodecaedro en los ejes x, y, y z. En este caso, se reduce la escala en el eje y (altura) mientras que se mantiene la escala en los otros ejes.
    glutSolidDodecahedron(); //dibuja un dodecaedro sólido utilizando la función proporcionada por GLUT.

    //Segundo dodecaedro superior.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 6.0f, 0.0f); //translada la figura del dodecaedro a la posición (0.0, 6.0, 0.0) en el espacio tridimensional.
    glScalef(0.45, 0.1, 0.45); //escala la figura del dodecaedro en los ejes x, y, y z. En este caso, se reduce la escala en el eje y (altura) mientras que se mantiene la escala en los otros ejes.
    glutSolidDodecahedron(); //dibuja un dodecaedro sólido utilizando la función proporcionada por GLUT.
    glPopMatrix();

    //Anillo de elipse superior.
    glPushMatrix(); //guarda la matriz actual en la pila.

    //Primer toro sólido.
    glTranslatef(0.0f, 4.10f, 0.0f); //traslada el toro a la posición (0.0, 4.10, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.34); //escala el toro en los ejes x, y, y z.
    glutSolidTorus(0.6f, 0.2f, 40, 40); // dibuja un toro sólido con radios 0.6 y 0.2, usando 40 segmentos en cada dirección.

    //Segundo toro sólido.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 4.30f, 0.0f); //traslada el toro a la posición (0.0, 4.30, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el toro en los ejes x, y, y z.
    glutSolidTorus(0.4f, 0.2f, 40, 40); //dibuja otro toro sólido con radios 0.4 y 0.2, usando 40 segmentos en cada dirección.

    //Tercer toro sólido.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 4.4f, 0.0f); //traslada el toro a la posición (0.0, 4.4, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el toro en los ejes x, y, y z.
    glutSolidTorus(0.4f, 0.2f, 40, 40); //dibuja otro toro sólido con radios 0.4 y 0.2, usando 40 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Cono.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 1.0f, 0.0f); //translada el cono a la posición (0.0, 1.0, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el cono -90 grados alrededor del eje x.
    glutSolidCone(1.05f, 5.1f, 50, 50); //dibuja un cono sólido con radio base 1.05 y altura 5.1 utilizando la función proporcionada por GLUT.
    glRotated(-180, 0.0f, 1.0f, 0.0f); //rota el cono -180 grados alrededor del eje y.
    glTranslatef(0.0f, 0.0f, -5.0f); //translada el cono en el eje z en -5.0 unidades.
    glutSolidCone(0.7f, 5.6f, 50, 50); //dibuja otro cono sólido con radio base 0.7 y altura 5.6 utilizando la función proporcionada por GLUT.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    // Círculo bajo
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 1.3f, 0.0f); //translada el círculo bajo a la posición (0.0, 1.3, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el círculo -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el círculo en los ejes x, y, y z. En este caso, se reduce la escala en el eje y mientras que se mantiene la escala en los otros ejes.
    glutSolidTorus(1.0f, 0.3f, 50, 50); //dibuja un toro sólido con radio mayor 1.0, radio menor 0.3 utilizando la función proporcionada por GLUT.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 1.5f, 0.0f); //translada el segundo círculo bajo a la posición (0.0, 1.5, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el segundo círculo -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el segundo círculo en los ejes x, y, y z. En este caso, se reduce la escala en el eje y mientras que se mantiene la escala en los otros ejes.
    glutSolidTorus(0.8f, 0.3f, 50, 50); //dibuja un segundo toro sólido con radio mayor 0.8, radio menor 0.3 utilizando la función proporcionada por GLUT.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    dibujar_fondo();
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Llama a la función para dibujar la reina
    dibujar_Reinablanca();

    glutSwapBuffers();
}

void init(void) {
    glClearColor(1.0, 0.8, 0.8, 1.0); 
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
    glutCreateWindow("Dibujar reina blanca");

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
