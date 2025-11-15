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

void dibujar_Torre() {
    
    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 4 y establece el color a blanco.
    indice = indice02;
    pieza = 4;
    glColor3f(1.0, 1.0, 1.0); //blanco.

    //Configuración de la matriz de modelo-vista.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz); //trasladar la figura en las coordenadas (Sx, Sy, Sz).

    glScalef(0.29 / dd, 0.30 / dd, 0.29 / dd); 
    GLUquadricObj* cuadratico;

    //Cilindro superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0, 4.0, 0.0); //translada el cilindro superior a la posición (0.0, 4.0, 0.0) en el espacio tridimensional.
    cuadratico = gluNewQuadric(); //inicializa un objeto cuadrático.
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); //rota el cilindro -90 grados alrededor del eje x.
    gluCylinder(cuadratico, 1.0f, 1.0f, 1.0f, 32, 32); //dibuja un cilindro con radio superior 1.0, radio inferior 1.0, y altura 1.0 utilizando la función proporcionada por GLUT.
    glScalef(1.0, 1.0, 0.1); //escala el cilindro en los ejes x, y, y z. En este caso, se reduce la escala en el eje z.
    glutSolidTorus(0.9f, 0.1f, 50, 50); //dibuja un toro sólido con radio mayor 0.9, radio menor 0.1 utilizando la función proporcionada por GLUT.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Cubierta superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0, 5.0, 0.0); //translada la cubierta superior a la posición (0.0, 5.0, 0.0) en el espacio tridimensional.
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); //rota la cubierta superior -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.1); //escala la cubierta superior en los ejes x, y, y z. En este caso, se reduce la escala en el eje z.
    glutSolidTorus(0.9f, 0.1f, 50, 50); //dibuja un toro sólido con radio mayor 0.9, radio menor 0.1 utilizando la función proporcionada por GLUT.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Cilindro medio.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0, 1.0, 0.0); //translada el cilindro medio a la posición (0.0, 1.0, 0.0) en el espacio tridimensional.
    cuadratico = gluNewQuadric(); //inicializa un objeto cuadrático para usar en la creación del cilindro.
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); //rota el cilindro medio -90 grados alrededor del eje x.
    gluCylinder(cuadratico, 1.1f, 0.6f, 3.4f, 32, 32); //dibuja un cilindro sólido con radio de la base 1.1, radio del tope 0.6, altura 3.4 utilizando la función gluCylinder.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Cilindro invertido.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0, 4.5, 0.0); //translada el cilindro invertido a la posición (0.0, 4.5, 0.0) en el espacio tridimensional.
    cuadratico = gluNewQuadric(); //inicializa un objeto cuadrático para usar en la creación del cilindro.
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); //rota el cilindro invertido 90 grados alrededor del eje x.
    gluCylinder(cuadratico, 0.85f, 0.55f, 3.4f, 32, 32); //dibuja un cilindro sólido invertido con radio de la base 0.85, radio del tope 0.55, altura 3.4 utilizando la función gluCylinder.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Cubierta central.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0, 3.4, 0.0); //translada la cubierta central a la posición (0.0, 3.4, 0.0) en el espacio tridimensional.
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); //rota la cubierta central -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 3.5); //escala la cubierta central en los ejes x, y, y z. En este caso, se amplía la escala en el eje z mientras que se mantiene la escala en los otros ejes.
    glutSolidTorus(0.455f, 0.3f, 50, 50); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de la sección transversal 0.455 y radio de la sección circular 0.3.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    dibujar_fondo();
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Llama a la función para dibujar la torre
    dibujar_Torre();

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
