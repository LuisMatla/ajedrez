#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/freeglut.h>  // Cambia freeglut_std.h por freeglut.h para mayor compatibilidad
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
//Variables globales para que cualquier figura pueda rotar en x, y, z.
float eje_w = 0.0;
float eje_a = 0.0;
float eje_d = 0.0;
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

void dibujar_esferasuperior() {
    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 2 y establece el color a blanco.
    pieza = 2;
    glColor3f(1.0, 1.0, 1.0); //blanco.

    //Configuración de la matriz de modelo-vista.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz); //trasladar la figura en las coordenadas (Sx, Sy, Sz).

    glScalef(0.34 / dd, 0.31 / dd, 0.34 / dd); //escalar la figura.

    //Esfera superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila
    glTranslatef(0.0f, 5.5f, 0.0f); //translada la esfera superior a la posición (0.0, 5.5, 0.0) en el espacio tridimensional
    glutSolidSphere(0.2f, 40, 40); //dibuja una esfera sólida utilizando la función proporcionada por GLUT con un radio de 0.2
    glPopMatrix(); //restaura la matriz a la guardada previamente
}
void dibujaranillosuperior(){
    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 2 y establece el color a blanco.
    pieza = 2;
    glColor3f(0.0, 0.0, 0.0); //blanco.

    //Configuración de la matriz de modelo-vista.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz); //trasladar la figura en las coordenadas (Sx, Sy, Sz).

    glScalef(0.34 / dd, 0.31 / dd, 0.34 / dd); //escalar la figura.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 3.10f, 0.0f); //translada el anillo elíptico superior a la posición (0.0, 3.10, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el anillo -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.25); //escala el anillo en los ejes x, y, y z.
    glutSolidTorus(0.6f, 0.2f, 40, 40); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de tubo 0.2 y radio de anillo 0.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

}
void segundoanillo(){
    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 2 y establece el color a blanco.
    pieza = 2;
    glColor3f(1.0, 0.0, 0.0); //blanco.

    //Configuración de la matriz de modelo-vista.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz); //trasladar la figura en las coordenadas (Sx, Sy, Sz).

    glScalef(0.34 / dd, 0.31 / dd, 0.34 / dd); //escalar la figura.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 3.1f, 0.0f); //translada el otro anillo elíptico superior a la posición (0.0, 3.1, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el anillo -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.24); //escala el anillo en los ejes x, y, y z.
    glutSolidTorus(0.6f, 0.2f, 40, 40); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de tubo 0.2 y radio de anillo 0.6.
    glPopMatrix(); //restaura la matriz a la guardada previamente. 

}

void otroanillo(){
    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 2 y establece el color a blanco.
    pieza = 2;
    glColor3f(1.0, 1.0, 0.0); //blanco.

    //Configuración de la matriz de modelo-vista.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz); //trasladar la figura en las coordenadas (Sx, Sy, Sz).

    glScalef(0.34 / dd, 0.31 / dd, 0.34 / dd); //escalar la figura.
    //Otro anillo elíptico superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 3.3f, 0.0f); //translada el otro anillo elíptico superior a la posición (0.0, 3.3, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el anillo -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el anillo en los ejes x, y, y z.
    glutSolidTorus(0.4f, 0.2f, 40, 40); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de tubo 0.2 y radio de anillo 0.4.
    glPopMatrix(); //restaura la matriz a la guardada previamente.      
}

void conox(){
    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 2 y establece el color a blanco.
    pieza = 2;
    glColor3f(1.0, 0.0, 1.0); //blanco.

    //Configuración de la matriz de modelo-vista.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz); //trasladar la figura en las coordenadas (Sx, Sy, Sz).

    glScalef(0.34 / dd, 0.31 / dd, 0.34 / dd); //escalar la figura.   
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 1.0f, 0.0f); //translada el cono a la posición (0.0, 1.0, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el cono -90 grados alrededor del eje x
    glutSolidCone(0.85f, 4.5f, 50, 50); //dibuja un cono sólido utilizando la función proporcionada por GLUT con radio de base 0.85 y altura 4.5.
    glPopMatrix(); //restaura la matriz a la guardada previamente. 

}

void esferasup(){
    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 2 y establece el color a blanco.
    pieza = 2;
    glColor3f(0.0, 1.0, 1.0); //blanco.

    //Configuración de la matriz de modelo-vista.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz); //trasladar la figura en las coordenadas (Sx, Sy, Sz).

    glScalef(0.34 / dd, 0.31 / dd, 0.34 / dd); //escalar la figura. 
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 4.4f, 0.0f); //translada la esfera superior a la posición (0.0, 4.4, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la esfera -90 grados alrededor del eje x.
    glScalef(0.48, 0.48, 1.0); //escala la esfera en los ejes x, y, y z.
    glutSolidSphere(1, 40, 40); //dibuja una esfera sólida utilizando la función proporcionada por GLUT con radio 1.
    glPopMatrix(); //restaura la matriz a la guardada previamente. 
}

/*void anillomedio(){
    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 2 y establece el color a blanco.
    pieza = 2;
    glColor3f(0.0, 0.8, 0.8); //blanco.

    //Configuración de la matriz de modelo-vista.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz); //trasladar la figura en las coordenadas (Sx, Sy, Sz).

    glScalef(0.34 / dd, 0.31 / dd, 0.34 / dd); //escalar la figura.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 3.71f, 0.0f); //translada el anillo medio a la posición (0.0, 3.71, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el anillo medio -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.25); //escala el anillo medio en los ejes x, y, y z.
    glutSolidTorus(0.45f, 0.2f, 40, 40); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de la sección circular 0.45 y radio del tubo 0.2.
    glPopMatrix(); //restaura la matriz a la guardada previamente.    
}
    /*


    //Primer círculo inferior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 1.3f, 0.0f); //translada el círculo inferior a la posición (0.0, 1.3, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el círculo -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el círculo en los ejes x, y, y z.
    glutSolidTorus(0.85f, 0.3f, 50, 50); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de tubo 0.3 y radio de anillo 0.85.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Segundo círculo inferior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 1.5f, 0.0f); //translada el otro círculo inferior a la posición (0.0, 1.5, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el círculo -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el círculo en los ejes x, y, y z.
    glutSolidTorus(0.7f, 0.3f, 50, 50); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de tubo 0.3 y radio de anillo 0.7.
    glPopMatrix(); //restaura la matriz a la guardada previamente.


    //Dibuja el elipsoide inferior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 0.6f, 0.0f); //translada el elipsoide inferior a la posición (0.0, 0.6, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el elipsoide inferior -90 grados alrededor del eje x.
    glScalef(1.4, 1.4, 0.8); //escala el elipsoide inferior en los ejes x, y, y z.
    dibujar_elipsoide(0, 2 * M_PI, 0, M_PI / 2); //llama a la función dibujar_elipsoide para dibujar el elipsoide inferior.
    glPopMatrix(); //restaura la matriz a la guardada previamente

    //Dibuja el elipsoide superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 0.9f, 0.0f); //translada el elipsoide superior a la posición (0.0, 0.9, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el elipsoide superior -90 grados alrededor del eje x.
    glScalef(1.3, 1.3, 0.9); //escala el elipsoide superior en los ejes x, y, y z.
    dibujar_elipsoide(0, 2 * M_PI, 0, M_PI / 2); //llama a la función dibujar_elipsoide para dibujar el elipsoide superior.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    glPopMatrix();*/



void init(void) {
    glClearColor(1.0, 0.8, 0.8, 1.0); 
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void rotarfigura(unsigned char key, int w, int a, int d) {
    switch (key) { //evaluamos la tecla presionada.

        //Si es 'w' o 'W', incrementamos el ángulo de rotación en el eje w.
        case 'w':
        case 'W':
            eje_w += 5;
            break;

        //Si es 'a' o 'A', incrementamos el ángulo de rotación en el eje a.
        case 'a':
        case 'A':
            eje_a += 5;
            break;
        //Si es 'd' o 'D', incrementamos el ángulo de rotación en el eje d.
        case 'd':
        case 'D':
            eje_d += 5;
            break;
    }
    glutPostRedisplay(); //solicitamos una redibujado de la escena.
}

void display(void) {
    int key;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    rotarfigura(key, 0, 0, 0);
    /* Llama a la función para dibujar el obispo
    /dibujar_esferasuperior();
    dibujaranillosuperior();
    //segundoanillo();
    //otroanillo();
    conox();*/
    esferasup();
    //anillomedio();
    glutSwapBuffers();
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
    glutCreateWindow("Dibujar Alfil blanco");

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
