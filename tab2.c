#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

//Definición de una estructura para representar un punto en el espacio tridimensional.
struct punto {
    float x; //miembro 'x' de tipo float para representar la coordenada x.
    float y; //miembro 'y' de tipo float para representar la coordenada y.
    float z; //miembro 'z' de tipo float para representar la coordenada z.
};

//Ayuda a organizar y almacenar las coordenadas cartesianas de un punto en el espacio tridimensional. 
struct punto esferico(float alpha, float beta, float r){
    struct punto p; //declara una variable llamada 'p' de tipo 'struct punto'.
    p.x = r * cos(alpha) * cos(beta); //calcula la coordenada x del punto en coordenadas esféricas y la asigna a 'p.x'.
    p.y = r * sin(alpha) * cos(beta); //calcula la coordenada y del punto en coordenadas esféricas y la asigna a 'p.y'.
    p.z = r * sin(beta); //calcula la coordenada z del punto en coordenadas esféricas y la asigna a 'p.z'.
    return p; //retorna la estructura 'p', que ahora contiene las coordenadas en formato esférico convertidas a coordenadas cartesianas.
}

int piezaSeleccionada = 0; //variable para almacenar la pieza seleccionada
int piezab = 0;
int piezan = 0;
int tab = 0;

//Variables globales para que cualquier figura se pueda mover en el eje x, y, z.
float eje_x = 0.0;
float eje_y = 0.0;
float eje_z = 0.0;

//Variables globales para que cualquier figura pueda rotar en x, y, z.
float eje_w = 0.0;
float eje_a = 0.0;
float eje_d = 0.0;

//Variables globales para que se pueda hacer el movimiento de la cámara.
float cameraX = 0.0;
float cameraY = 0.0;
float cameraZ = 5.0;

//Variables globales para la traslación y otras configuraciones.
double Sx = 0.0;
double Sy = 0.0;
double Sz = 0.0;
int dd = 1;

//Variables globales para el ángulo de rotación de esferas y anillo.
double esfera_superior01 = 0.0;
double esfera_superior02 = 0.0;
double anillo_superior = 0.0;
int indice = 0;
int indice02;
int pieza = 0;


//Declaramos las variables globales.
void dibujar_elipsoide(float a1, float a2, float b1, float b2);
void dibujar_fondo();
void dibujar_cubo(float x, float y, float z);
void texto_Rey();
void texto_Reina();
void texto_Alfil();
void texto_Caballo();
void texto_Torre();
void texto_Peon();
void dibujar_Rey_blanco();
void dibujar_Rey_negro();
void dibujar_Reina_blanca();
void dibujar_Reina_negra();
void dibujar_Alfil_blanco();
void dibujar_Alfil_negro();
void dibujar_Caballo_blanco();
void dibujar_Caballo_negro();
void dibujar_Torre_blanca();
void dibujar_Torre_negra();
void dibujar_Peon_blanco();
void dibujar_Peon_negro();
void tablero_sinpiezas();
void dibujar_tablero();
void movimientitos();
void piezas_blancas();
void piezas_negras();
void display();
void specialKeys(int key, int x, int y);
void movimientoMenu(unsigned char key, int x, int y);
void rotarfigura(unsigned char key, int w, int a, int d);
void movercamara(int key, int x, int y);
static void reshape01(int w, int h);
void reshape02(int w, int h);
static void init01(void);
void tableros();
void menu(int value);
void movimientos(unsigned char key, int x, int y);
void piezas();

//Sirve para dibujar un elipsoide dividido en polígonos.
void dibujar_elipsoide(float a1, float a2, float b1, float b2) {
    
    //Definir la cantidad de divisiones en los ejes alfa y beta.
    int na = 32; //número de divisiones en el eje alfa.
    int nb = 16; //número de divisiones en el eje beta.

    // Variables para almacenar los ángulos alfa y beta y sus incrementos.
    float alpha;
    float dalpha = (a2 - a1) / na; //incremento en alfa.
    float beta;
    float dbeta = (b2 - b1) / nb; //incremento en beta.
    beta = b2; //inicializar beta con el valor b2 y realizar bucles para las divisiones en beta.
    for (int j = 0; j < nb; j++, beta -= dbeta) {
        alpha = a1; //inicializar alpha con el valor a1 y realizar bucles para las divisiones en alf.
        for (int i = 0; i < na; i++, alpha += dalpha) {
            struct punto p; //estructura para almacenar las coordenadas cartesianas convertidas de esféricas.
            glBegin(GL_POLYGON); //iniciar un nuevo polígono con GL_POLYGON.
            p = esferico(alpha, beta, 1); //obtener las coordenadas cartesianas de un punto en elipsoide mediante coordenadas esféricas.
            glNormal3f(p.x, p.y, p.z); //especificar la normal para la iluminación.
            glVertex3f(p.x, p.y, p.z); //especificar un vértice del polígono con glVertex3f.

            //Repetir el proceso para los demás vértices del polígono.
            p = esferico(alpha + dalpha, beta, 1);
            glNormal3f(p.x, p.y, p.z);
            glVertex3f(p.x, p.y, p.z);
            p = esferico(alpha + dalpha, beta - dbeta, 1);
            glNormal3f(p.x, p.y, p.z);
            glVertex3f(p.x, p.y, p.z);
            p = esferico(alpha, beta - dbeta, 1);
            glNormal3f(p.x, p.y, p.z);
            glVertex3f(p.x, p.y, p.z);
            glEnd(); //finalizar el polígono con glEnd
        }
    }
}

//Dibuja el fondo que consiste en dos elipsoides.
void dibujar_fondo() {

    //Dibuja el primer elipsoide en el fondo.
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f);
    glRotated(-90, 1.0f, 0.0f, 0.0f);

    //Escala el primer elipsoide para hacerlo más ancho y alto
    glScalef(1.5, 1.5, 0.8);
    dibujar_elipsoide(0, 2 * M_PI, 0, M_PI / 2);
    glPopMatrix();
    
    //Dibuja el segundo elipsoide en el fondo.
    glPushMatrix();
    glTranslatef(0.0f, 0.9f, 0.0f);
    glRotated(-90, 1.0f, 0.0f, 0.0f);

    //Escala el segundo elipsoide para ajustar sus dimensiones
    glScalef(1.4, 1.4, 1.0);
    dibujar_elipsoide(0, 2 * M_PI, 0, M_PI / 2); /*el M_PI se utiliza para definor los angulos en términos de pi en las funciones trigonométricas
    como cos y sin, que se utilizan en la funcion dibujar_elipsoide para especificar los rangos de ángulos de los cuales se dibujan los elipsoides.*/
    glPopMatrix();
}

void dibujar_cubo(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glBegin(GL_QUADS);
    // Define the six faces of the cube
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);

    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);

    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);

    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);

    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    glPopMatrix();
}

void texto_Rey(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); //negro.
    glRasterPos2f(-1.7, -1.7); //posición del texto.
    char text[] = "REY"; //declaramos una cadena de caracteres para el texto.
    for (int i = 0; text[i] != '\0'; i++) { //iteramos a través de cada carácter de la cadena hasta llegar al carácter nulo '\0'.
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);//utilizamos la función glutBitmapCharacter para renderizar cada carácter en la posición actual.
}
    glFlush();
}

void texto_Reina(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); //negro.
    glRasterPos2f(-1.7, -1.7); //posición del texto.
    char text[] = "REINA"; //declaramos una cadena de caracteres para el texto.
    for (int i = 0; text[i] != '\0'; i++) { //iteramos a través de cada carácter de la cadena hasta llegar al carácter nulo '\0'.
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);//utilizamos la función glutBitmapCharacter para renderizar cada carácter en la posición actual.
}
    glFlush();
}

void texto_Alfil(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); //negro.
    glRasterPos2f(-1.7, -1.7); //posición del texto.
    char text[] = "ALFIL"; //declaramos una cadena de caracteres para el texto.
    for (int i = 0; text[i] != '\0'; i++) { //iteramos a través de cada carácter de la cadena hasta llegar al carácter nulo '\0'.
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);//utilizamos la función glutBitmapCharacter para renderizar cada carácter en la posición actual.
}
    glFlush();
}

void texto_Caballo(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); //negro.
    glRasterPos2f(-1.7, -1.7); //posición del texto.
    char text[] = "CABALLO"; //declaramos una cadena de caracteres para el texto.
    for (int i = 0; text[i] != '\0'; i++) { //iteramos a través de cada carácter de la cadena hasta llegar al carácter nulo '\0'.
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);//utilizamos la función glutBitmapCharacter para renderizar cada carácter en la posición actual.
}
    glFlush();
}

void texto_Torre(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); //negro.
    glRasterPos2f(-1.7, -1.7); //posición del texto.
    char text[] = "TORRE"; //declaramos una cadena de caracteres para el texto.
    for (int i = 0; text[i] != '\0'; i++) { //iteramos a través de cada carácter de la cadena hasta llegar al carácter nulo '\0'.
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);//utilizamos la función glutBitmapCharacter para renderizar cada carácter en la posición actual.
}
    glFlush();
}

void texto_Peon(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); //negro.
    glRasterPos2f(-1.7, -1.7); //posición del texto.
    char text[] = "PEON"; //declaramos una cadena de caracteres para el texto.
    for (int i = 0; text[i] != '\0'; i++) { //iteramos a través de cada carácter de la cadena hasta llegar al carácter nulo '\0'.
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);//utilizamos la función glutBitmapCharacter para renderizar cada carácter en la posición actual.
}
    glFlush();
}


void dibujar_Rey_blanco(){

    //Inicialización de variables.
    indice = 0;
    pieza = 10;
    glColor3f(1.0, 1.0, 1.0); //blanco.

    //Configuración de la matriz de modelo-vista.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz); //trasladar la figura en las coordenadas (Sx, Sy, Sz).
    
    glScalef(0.33 / dd, 0.33 / dd, 0.33 / dd); //escalar la figura.

    //Esfera superior.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 6.0f, 0.0f); //traslada la esfera a la posición (0.0, 6.0, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la esfera -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.4); //escala la esfera en los ejes x, y, y z.
    glutSolidTorus(0.5f, 0.2f, 40, 40); //dibuja un toro sólido con radios 0.5 y 0.2, usando 40 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.

    //Otra parte de la esfera superior.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 5.9f, 0.0f); //traslada la figura a la posición (0.0, 5.9, 0.0).
    glutSolidSphere(0.34f, 50, 50); //dibuja una esfera sólida con radio 0.34 y 50 segmentos en cada dirección.
    glTranslatef(0.0f, 0.55f, 0.0f); //traslada la figura a la posición (0.0, 0.55, 0.0).
    glPushMatrix(); //guarda la matriz actual en la pila.
    glScalef(1.0f, 0.2f, 0.2f); //escala la figura en los ejes x, y, y z.
    glutSolidCube(1.0f); //dibuja un cubo sólido con lado 1.0.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
    glScalef(0.3f, 1.0f, 0.2f); //escala la figura en los ejes x, y, y z.
    glutSolidCube(1.0f); //dibuja un cubo sólido con lado 1.0.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.

    //Anillo elíptico superior
    glPushMatrix(); //guarda la matriz actual en la pila

    //Primer toro sólido.
    glTranslatef(0.0f, 4.10f, 0.0f); //traslada el toro a la posición (0.0, 4.10, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.3); //escala el toro en los ejes x, y, y z.
    glutSolidTorus(0.6f, 0.2f, 40, 40); //dibuja un toro sólido con radios 0.6 y 0.2, usando 40 segmentos en cada dirección.

    //Segundo toro sólido.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 4.30f, 0.0f); //traslada el toro a la posición (0.0, 4.30, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el toro en los ejes x, y, y z.
    glutSolidTorus(0.4f, 0.2f, 40, 40); //dibuja un toro sólido con radios 0.4 y 0.2, usando 40 segmentos en cada dirección.

    //Tercer toro sólido.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 4.4f, 0.0f); //traslada el toro a la posición (0.0, 4.4, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el toro en los ejes x, y, y z.
    glutSolidTorus(0.4f, 0.2f, 40, 40); //dibuja un toro sólido con radios 0.4 y 0.2, usando 40 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Cono.
    glPushMatrix(); //guarda la matriz actual en la pila
    glTranslatef(0.0f, 1.0f, 0.0f); //traslada el cono a la posición (0.0, 1.0, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el cono -90 grados alrededor del eje x.
    glutSolidCone(1.05f, 5.1f, 50, 50); //dibuja un cono sólido con radio base 1.05, altura 5.1, y 50 segmentos en la base.
    glRotated(-180, 0.0f, 1.0f, 0.0f); //rota el cono -180 grados alrededor del eje y.
    glTranslatef(0.0f, 0.0f, -5.0f); //traslada el cono a lo largo del eje z.
    glutSolidCone(0.7f, 5.6f, 50, 50); //dibuja otro cono sólido con radio base 0.7, altura 5.6, y 50 segmentos en la base.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.

    //Círculo inferior.
    glPushMatrix(); //guarda la matriz actual en la pila.

    //Primer toro sólido.
    glTranslatef(0.0f, 1.3f, 0.0f); //traslada el toro a la posición (0.0, 1.3, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el toro en los ejes x, y, y z.
    glutSolidTorus(1.0f, 0.3f, 50, 50); //dibuja un toro sólido con radios 1.0 y 0.3, usando 50 segmentos en cada dirección.

    //Segundo toro sólido.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 1.5f, 0.0f); //traslada el toro a la posición (0.0, 1.5, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el toro en los ejes x, y, y z.
    glutSolidTorus(0.8f, 0.3f, 50, 50); //dibuja otro toro sólido con radios 0.8 y 0.3, usando 50 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    dibujar_fondo();
    glPopMatrix();
}

void dibujar_Rey_negro(){

    //Inicialización de variables.
    indice = 0;
    pieza = 10;
    glColor3f(0.0, 0.0, 0.0); //negro.

    //Configuración de la matriz de modelo-vista.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz); //trasladar la figura en las coordenadas (Sx, Sy, Sz).
    
    glScalef(0.33 / dd, 0.33 / dd, 0.33 / dd); //escalar la figura.

    //Esfera superior.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 6.0f, 0.0f); //traslada la esfera a la posición (0.0, 6.0, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la esfera -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.4); //escala la esfera en los ejes x, y, y z.
    glutSolidTorus(0.5f, 0.2f, 40, 40); //dibuja un toro sólido con radios 0.5 y 0.2, usando 40 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.

    //Otra parte de la esfera superior.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 5.9f, 0.0f); //traslada la figura a la posición (0.0, 5.9, 0.0).
    glutSolidSphere(0.34f, 50, 50); //dibuja una esfera sólida con radio 0.34 y 50 segmentos en cada dirección.
    glTranslatef(0.0f, 0.55f, 0.0f); //traslada la figura a la posición (0.0, 0.55, 0.0).
    glPushMatrix(); //guarda la matriz actual en la pila.
    glScalef(1.0f, 0.2f, 0.2f); //escala la figura en los ejes x, y, y z.
    glutSolidCube(1.0f); //dibuja un cubo sólido con lado 1.0.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
    glScalef(0.3f, 1.0f, 0.2f); //escala la figura en los ejes x, y, y z.
    glutSolidCube(1.0f); //dibuja un cubo sólido con lado 1.0.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.

    //Anillo elíptico superior
    glPushMatrix(); //guarda la matriz actual en la pila

    //Primer toro sólido.
    glTranslatef(0.0f, 4.10f, 0.0f); //traslada el toro a la posición (0.0, 4.10, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.3); //escala el toro en los ejes x, y, y z.
    glutSolidTorus(0.6f, 0.2f, 40, 40); //dibuja un toro sólido con radios 0.6 y 0.2, usando 40 segmentos en cada dirección.

    //Segundo toro sólido.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 4.30f, 0.0f); //traslada el toro a la posición (0.0, 4.30, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el toro en los ejes x, y, y z.
    glutSolidTorus(0.4f, 0.2f, 40, 40); //dibuja un toro sólido con radios 0.4 y 0.2, usando 40 segmentos en cada dirección.

    //Tercer toro sólido.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 4.4f, 0.0f); //traslada el toro a la posición (0.0, 4.4, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el toro en los ejes x, y, y z.
    glutSolidTorus(0.4f, 0.2f, 40, 40); //dibuja un toro sólido con radios 0.4 y 0.2, usando 40 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Cono.
    glPushMatrix(); //guarda la matriz actual en la pila
    glTranslatef(0.0f, 1.0f, 0.0f); //traslada el cono a la posición (0.0, 1.0, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el cono -90 grados alrededor del eje x.
    glutSolidCone(1.05f, 5.1f, 50, 50); //dibuja un cono sólido con radio base 1.05, altura 5.1, y 50 segmentos en la base.
    glRotated(-180, 0.0f, 1.0f, 0.0f); //rota el cono -180 grados alrededor del eje y.
    glTranslatef(0.0f, 0.0f, -5.0f); //traslada el cono a lo largo del eje z.
    glutSolidCone(0.7f, 5.6f, 50, 50); //dibuja otro cono sólido con radio base 0.7, altura 5.6, y 50 segmentos en la base.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.

    //Círculo inferior.
    glPushMatrix(); //guarda la matriz actual en la pila.

    //Primer toro sólido.
    glTranslatef(0.0f, 1.3f, 0.0f); //traslada el toro a la posición (0.0, 1.3, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el toro en los ejes x, y, y z.
    glutSolidTorus(1.0f, 0.3f, 50, 50); //dibuja un toro sólido con radios 1.0 y 0.3, usando 50 segmentos en cada dirección.

    //Segundo toro sólido.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 1.5f, 0.0f); //traslada el toro a la posición (0.0, 1.5, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el toro -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el toro en los ejes x, y, y z.
    glutSolidTorus(0.8f, 0.3f, 50, 50); //dibuja otro toro sólido con radios 0.8 y 0.3, usando 50 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz a la guardada previamente.
    dibujar_fondo();
    glPopMatrix();
}

void dibujar_Reina_blanca(){

    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 3 y establece el color a blanco.
    pieza = 9;
    glColor3f(1.0, 1.0, 1.0); //blanco.
    
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


void dibujar_Reina_negra(){

    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 3 y establece el color a negro.
    pieza = 9;
    glColor3f(0.0, 0.0, 0.0); //negro
    
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

void dibujar_Alfil_blanco(){

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

    //Primer anillo elíptico superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 3.10f, 0.0f); //translada el anillo elíptico superior a la posición (0.0, 3.10, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el anillo -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.25); //escala el anillo en los ejes x, y, y z.
    glutSolidTorus(0.6f, 0.2f, 40, 40); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de tubo 0.2 y radio de anillo 0.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Seguno anillo elíptico superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 3.1f, 0.0f); //translada el otro anillo elíptico superior a la posición (0.0, 3.1, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el anillo -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.24); //escala el anillo en los ejes x, y, y z.
    glutSolidTorus(0.6f, 0.2f, 40, 40); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de tubo 0.2 y radio de anillo 0.6.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Otro anillo elíptico superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 3.3f, 0.0f); //translada el otro anillo elíptico superior a la posición (0.0, 3.3, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el anillo -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el anillo en los ejes x, y, y z.
    glutSolidTorus(0.4f, 0.2f, 40, 40); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de tubo 0.2 y radio de anillo 0.4.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Cono.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 1.0f, 0.0f); //translada el cono a la posición (0.0, 1.0, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el cono -90 grados alrededor del eje x
    glutSolidCone(0.85f, 4.5f, 50, 50); //dibuja un cono sólido utilizando la función proporcionada por GLUT con radio de base 0.85 y altura 4.5.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Esfera superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 4.4f, 0.0f); //translada la esfera superior a la posición (0.0, 4.4, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la esfera -90 grados alrededor del eje x.
    glScalef(0.48, 0.48, 1.0); //escala la esfera en los ejes x, y, y z.
    glutSolidSphere(1, 40, 40); //dibuja una esfera sólida utilizando la función proporcionada por GLUT con radio 1.
    glPopMatrix(); //restaura la matriz a la guardada previamente.


    //Anillo medio.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 3.71f, 0.0f); //translada el anillo medio a la posición (0.0, 3.71, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el anillo medio -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.25); //escala el anillo medio en los ejes x, y, y z.
    glutSolidTorus(0.45f, 0.2f, 40, 40); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de la sección circular 0.45 y radio del tubo 0.2.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

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
    glPopMatrix();
}

void dibujar_Alfil_negro(){

    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 2 y establece el color a negro.
    pieza = 2;
    glColor3f(0.0, 0.0, 0.0); //negro.

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

    //Primer anillo elíptico superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 3.10f, 0.0f); //translada el anillo elíptico superior a la posición (0.0, 3.10, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el anillo -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.25); //escala el anillo en los ejes x, y, y z.
    glutSolidTorus(0.6f, 0.2f, 40, 40); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de tubo 0.2 y radio de anillo 0.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Seguno anillo elíptico superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 3.1f, 0.0f); //translada el otro anillo elíptico superior a la posición (0.0, 3.1, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el anillo -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.24); //escala el anillo en los ejes x, y, y z.
    glutSolidTorus(0.6f, 0.2f, 40, 40); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de tubo 0.2 y radio de anillo 0.6.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Otro anillo elíptico superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 3.3f, 0.0f); //translada el otro anillo elíptico superior a la posición (0.0, 3.3, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el anillo -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala el anillo en los ejes x, y, y z.
    glutSolidTorus(0.4f, 0.2f, 40, 40); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de tubo 0.2 y radio de anillo 0.4.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Cono.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 1.0f, 0.0f); //translada el cono a la posición (0.0, 1.0, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el cono -90 grados alrededor del eje x
    glutSolidCone(0.85f, 4.5f, 50, 50); //dibuja un cono sólido utilizando la función proporcionada por GLUT con radio de base 0.85 y altura 4.5.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

    //Esfera superior.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 4.4f, 0.0f); //translada la esfera superior a la posición (0.0, 4.4, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la esfera -90 grados alrededor del eje x.
    glScalef(0.48, 0.48, 1.0); //escala la esfera en los ejes x, y, y z.
    glutSolidSphere(1, 40, 40); //dibuja una esfera sólida utilizando la función proporcionada por GLUT con radio 1.
    glPopMatrix(); //restaura la matriz a la guardada previamente.


    //Anillo medio.
    glPushMatrix(); //guarda la matriz de transformación actual en la pila.
    glTranslatef(0.0f, 3.71f, 0.0f); //translada el anillo medio a la posición (0.0, 3.71, 0.0) en el espacio tridimensional.
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota el anillo medio -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.25); //escala el anillo medio en los ejes x, y, y z.
    glutSolidTorus(0.45f, 0.2f, 40, 40); //dibuja un toro sólido utilizando la función proporcionada por GLUT con radio de la sección circular 0.45 y radio del tubo 0.2.
    glPopMatrix(); //restaura la matriz a la guardada previamente.

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
    glPopMatrix();
}

void dibujar_Caballo_blanco(){

    //Establece el índice actual.
    indice = indice02;

    //Desactiva las luces GL_LIGHT1 y GL_LIGHT2.
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);

    //Define la pieza actual como 3 y establece el color a blanco.
    pieza = 3;
    glColor3f(1.0, 1.0, 1.0); //blanco

    //Configuración de la matriz de modelo-vista y aplicando transformaciones de traslación, rotación y escala.
    glMatrixMode(GL_MODELVIEW); //establece la matriz de modelo-vista como la matriz activa.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(Sx, Sy, Sz); //traslada la figura a la posición (Sx, Sy, Sz).
    glRotatef(180, 0.0f, 1.0f, 0.0f); //rota la figura 180 grados alrededor del eje y.
    glScalef(0.29 / dd, 0.29 / dd, 0.29 / dd); //escala la figura en los ejes x, y, y z.


    //Cuerpo principal del caballo.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 4.0f, 0.0f); //traslada la figura a la posición (0.0, 4.0, 0.0).
    GLfloat tm12 = 0.8f; //define una variable GLfloat llamada tm12 y le asigna el valor 0.8.
    glTranslatef(0, -0.05f, 0); //traslada la figura a la posición (0, -0.05, 0).
    glTranslatef(-0.2f, 0.0f, 0.0f); //traslada la figura a la posición (-0.2, 0.0, 0.0)

    // Configura una transformación de escala en la matriz de modelo-vista.
    glPushMatrix(); // Guarda la matriz actual en la pila
    glScalef(0.8, 0.9, 0.8); // Escala la figura en los ejes x, y, y z

    //Dibuja la primera cara del cuerpo del caballo.
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros.
    glNormal3f(0.0f, 0.0f, -1.0f); //establece la normal de la cara en el sentido negativo del eje z.
    glVertex3f(-0.8f, -2.5f, -tm12); //define el primer vértice del cuadrilátero.
    glVertex3f(0.8f, -2.5f, -tm12); //define el segundo vértice del cuadrilátero.
    glVertex3f(0.4f, -1.2f, -tm12); //define el tercer vértice del cuadrilátero.
    glVertex3f(-0.4f, -0.5f, -tm12); //define el cuarto vértice del cuadrilátero.
    glEnd(); //finaliza la definición del conjunto de cuadriláteros.

    //Dibuja la tercera cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(1.0f, 0.2f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(0.8f, -2.5f, -tm12); //define el primer vértice del quad.
    glVertex3f(0.8f, -2.5f, tm12); //define el segundo vértice del quad.
    glVertex3f(0.2f, -0.5f, tm12); //define el tercer vértice del quad.
    glVertex3f(0.2f, -0.5f, -tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.

    //Dibuja la tercera cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(1.0f, 0.2f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(0.8f, -2.5f, -tm12); //define el primer vértice del quad.
    glVertex3f(0.8f, -2.5f, tm12); //define el segundo vértice del quad.
    glVertex3f(0.2f, -0.5f, tm12); //define el tercer vértice del quad.
    glVertex3f(0.2f, -0.5f, -tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.
    tm12 = -0.8f; //actualiza el valor de tm12 para la siguiente cara.

    //Dibuja la cuarta cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(0.0f, 0.0f, 1.0f); //establece la normal para las caras del quad.
    glVertex3f(-0.8f, -2.5f, -tm12); //define el primer vértice del quad.
    glVertex3f(0.8f, -2.5f, -tm12); //define el segundo vértice del quad.
    glVertex3f(0.4f, -1.2f, -tm12); //define el tercer vértice del quad.
    glVertex3f(-0.4f, -0.5f, -tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.
    tm12 = 0.8f; //actualiza el valor de tm12 para la siguiente cara.

    //Dibuja la quinta cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(-1.0f, 0.5f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(-0.4f, -0.5f, -tm12); //define el primer vértice del quad.
    glVertex3f(1.0f, 1.4f, -tm12); //define el segundo vértice del quad.
    glVertex3f(1.0f, 1.4f, tm12); //define el tercer vértice del quad.
    glVertex3f(-0.4f, -0.5f, tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.

    //Dibuja la sexta cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(1.0f, -0.4f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(0.4f, -1.2f, -tm12); //define el primer vértice del quad.
    glVertex3f(1.0f, 1.4f, -tm12); //define el segundo vértice del quad.
    glVertex3f(1.0f, 1.4f, tm12); //define el tercer vértice del quad.
    glVertex3f(0.4f, -1.2f, tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.

    //Dibuja la séptima cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(0.0f, 0.0f, -1.0f); //establece la normal para las caras del quad.
    glVertex3f(1.0f, 1.4f, -tm12); //define el primer vértice del quad.
    glVertex3f(0.4f, -1.2f, -tm12); //define el segundo vértice del quad.
    glVertex3f(-0.4f, -0.5f, -tm12); //define el tercer vértice del quad.
    glVertex3f(1.0f, 1.4f, -tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.

    //Dibuja la octava cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(0.0f, 0.0f, 1.0f); //establece la normal para las caras del quad.
    glVertex3f(1.0f, 1.4f, tm12); //define el primer vértice del quad.
    glVertex3f(0.4f, -1.2f, tm12); //define el segundo vértice del quad.
    glVertex3f(-0.4f, -0.5f, tm12); //define el tercer vértice del quad.
    glVertex3f(1.0f, 1.4f, tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.

    //Parte superior del cuerpo del caballo con dos caras.
    glPushMatrix(); //guarda la matriz actual en la pila
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(0.3f, 1.0f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(1.0f, 1.4f, tm12); //define el primer vértice del quad.
    glVertex3f(1.0f, 1.4f, -tm12); //define el segundo vértice del quad.
    glVertex3f(2.6f, 0.8f, -tm12 + 0.5f); //define el tercer vértice del quad.
    glVertex3f(2.6f, 0.8f, tm12 - 0.5f); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads

    //Parte inferior del cuerpo del caballo con dos caras.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(-0.2f, -1.0f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(0.5f, -0.2f, tm12); //define el primer vértice del quad.
    glVertex3f(0.5f, -0.2f, -tm12); //define el segundo vértice del quad.
    glVertex3f(2.6f, 0.4f, -tm12 + 0.5f); //define el tercer vértice del quad.
    glVertex3f(2.6f, 0.4f, tm12 - 0.5f); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.

    //Cara lateral izquierda del cuerpo del caballo con cuatro caras.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(0.2f, 0.0f, -1.0f); //establece la normal para las caras del quad.
    glVertex3f(0.5f, -0.2f, -tm12); //define el primer vértice del quad.
    glVertex3f(1.0f, 1.4f, -tm12); //define el segundo vértice del quad.
    glVertex3f(2.6f, 0.8f, -tm12 + 0.5f); //define el tercer vértice del quad.
    glVertex3f(2.6f, 0.4f, -tm12 + 0.5f); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.


    //Cara lateral derecha del cuerpo del caballo con cuatro caras.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(0.2f, 0.0f, 1.0f); //establece la normal para las caras del quad.
    glVertex3f(0.5f, -0.2f, tm12); //define el primer vértice del quad.
    glVertex3f(1.0f, 1.4f, tm12); //define el segundo vértice del quad.
    glVertex3f(2.6f, 0.8f, tm12 - 0.5f); //define el tercer vértice del quad.
    glVertex3f(2.6f, 0.4f, tm12 - 0.5f); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.


    //Cara trasera del cuerpo del caballo con cuatro caras.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(1.0f, 0.0f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(2.6f, 0.4f, -tm12 + 0.5f); //define el primer vértice del quad.
    glVertex3f(2.6f, 0.8f, -tm12 + 0.5f); //define el segundo vértice del quad.
    glVertex3f(2.6f, 0.4f, tm12 - 0.5f); //define el tercer vértice del quad.
    glVertex3f(2.6f, 0.8f, tm12 - 0.5f); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.
    
    //El tm12 tiene como función representar el desplazamiento a lo largo del eje z en varias 

    //Restaura la matriz de modelo-vista.
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    // Dibuja las patas del caballo utilizando toros sólidos.
    // Primera pata.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 1.6f, 0.0f); //traslada la pata a la posición (0.0, 1.6, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la pata -90 grados alrededor del eje x.
    glScalef(0.86, 0.86, 0.25); //escala la pata en los ejes x, y, y z.
    glutSolidTorus(1.0f, 0.3f, 50, 50); //dibuja un toro sólido con radios 1.0 y 0.3, usando 50 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.


    //Segunda pata.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 1.5f, 0.0f); //traslada la pata a la posición (0.0, 1.5, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la pata -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala la pata en los ejes x, y, y z.
    glutSolidTorus(0.8f, 0.3f, 50, 50); //dibuja un toro sólido con radios 0.8 y 0.3, usando 50 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.

    //Tercera pata.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 1.3f, 0.0f); //traslada la pata a la posición (0.0, 1.3, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la pata -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala la pata en los ejes x, y, y z.
    glutSolidTorus(1.0f, 0.3f, 50, 50); //dibuja un toro sólido con radios 1.0 y 0.3, usando 50 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.


    // Cuarta pata.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 1.5f, 0.0f); //traslada la pata a la posición (0.0, 1.5, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la pata -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala la pata en los ejes x, y, y z.
    glutSolidTorus(0.8f, 0.3f, 50, 50); //dibuja un toro sólido con radios 0.8 y 0.3, usando 50 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.


    //Llamada a la función dibujar_fondo().
    dibujar_fondo();
    glPopMatrix();
}

void dibujar_Caballo_negro(){

    //Establece el índice actual.
    indice = indice02;

    //Desactiva las luces GL_LIGHT1 y GL_LIGHT2.
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);

    //Define la pieza actual como 3 y establece el color a negro.
    pieza = 3;
    glColor3f(0.0, 0.0, 0.0); //negro.

    //Configuración de la matriz de modelo-vista y aplicando transformaciones de traslación, rotación y escala.
    glMatrixMode(GL_MODELVIEW); //establece la matriz de modelo-vista como la matriz activa.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(Sx, Sy, Sz); //traslada la figura a la posición (Sx, Sy, Sz).
    glRotatef(180, 0.0f, 1.0f, 0.0f); //rota la figura 180 grados alrededor del eje y.
    glScalef(0.29 / dd, 0.29 / dd, 0.29 / dd); //escala la figura en los ejes x, y, y z.


    //Cuerpo principal del caballo.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 4.0f, 0.0f); //traslada la figura a la posición (0.0, 4.0, 0.0).
    GLfloat tm12 = 0.8f; //define una variable GLfloat llamada tm12 y le asigna el valor 0.8.
    glTranslatef(0, -0.05f, 0); //traslada la figura a la posición (0, -0.05, 0).
    glTranslatef(-0.2f, 0.0f, 0.0f); //traslada la figura a la posición (-0.2, 0.0, 0.0)

    // Configura una transformación de escala en la matriz de modelo-vista.
    glPushMatrix(); // Guarda la matriz actual en la pila
    glScalef(0.8, 0.9, 0.8); // Escala la figura en los ejes x, y, y z

    //Dibuja la primera cara del cuerpo del caballo.
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros.
    glNormal3f(0.0f, 0.0f, -1.0f); //establece la normal de la cara en el sentido negativo del eje z.
    glVertex3f(-0.8f, -2.5f, -tm12); //define el primer vértice del cuadrilátero.
    glVertex3f(0.8f, -2.5f, -tm12); //define el segundo vértice del cuadrilátero.
    glVertex3f(0.4f, -1.2f, -tm12); //define el tercer vértice del cuadrilátero.
    glVertex3f(-0.4f, -0.5f, -tm12); //define el cuarto vértice del cuadrilátero.
    glEnd(); //finaliza la definición del conjunto de cuadriláteros.

    //Dibuja la tercera cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(1.0f, 0.2f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(0.8f, -2.5f, -tm12); //define el primer vértice del quad.
    glVertex3f(0.8f, -2.5f, tm12); //define el segundo vértice del quad.
    glVertex3f(0.2f, -0.5f, tm12); //define el tercer vértice del quad.
    glVertex3f(0.2f, -0.5f, -tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.

    //Dibuja la tercera cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(1.0f, 0.2f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(0.8f, -2.5f, -tm12); //define el primer vértice del quad.
    glVertex3f(0.8f, -2.5f, tm12); //define el segundo vértice del quad.
    glVertex3f(0.2f, -0.5f, tm12); //define el tercer vértice del quad.
    glVertex3f(0.2f, -0.5f, -tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.
    tm12 = -0.8f; //actualiza el valor de tm12 para la siguiente cara.

    //Dibuja la cuarta cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(0.0f, 0.0f, 1.0f); //establece la normal para las caras del quad.
    glVertex3f(-0.8f, -2.5f, -tm12); //define el primer vértice del quad.
    glVertex3f(0.8f, -2.5f, -tm12); //define el segundo vértice del quad.
    glVertex3f(0.4f, -1.2f, -tm12); //define el tercer vértice del quad.
    glVertex3f(-0.4f, -0.5f, -tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.
    tm12 = 0.8f; //actualiza el valor de tm12 para la siguiente cara.

    //Dibuja la quinta cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(-1.0f, 0.5f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(-0.4f, -0.5f, -tm12); //define el primer vértice del quad.
    glVertex3f(1.0f, 1.4f, -tm12); //define el segundo vértice del quad.
    glVertex3f(1.0f, 1.4f, tm12); //define el tercer vértice del quad.
    glVertex3f(-0.4f, -0.5f, tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.

    //Dibuja la sexta cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(1.0f, -0.4f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(0.4f, -1.2f, -tm12); //define el primer vértice del quad.
    glVertex3f(1.0f, 1.4f, -tm12); //define el segundo vértice del quad.
    glVertex3f(1.0f, 1.4f, tm12); //define el tercer vértice del quad.
    glVertex3f(0.4f, -1.2f, tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.

    //Dibuja la séptima cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(0.0f, 0.0f, -1.0f); //establece la normal para las caras del quad.
    glVertex3f(1.0f, 1.4f, -tm12); //define el primer vértice del quad.
    glVertex3f(0.4f, -1.2f, -tm12); //define el segundo vértice del quad.
    glVertex3f(-0.4f, -0.5f, -tm12); //define el tercer vértice del quad.
    glVertex3f(1.0f, 1.4f, -tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.

    //Dibuja la octava cara del cuerpo del caballo.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(0.0f, 0.0f, 1.0f); //establece la normal para las caras del quad.
    glVertex3f(1.0f, 1.4f, tm12); //define el primer vértice del quad.
    glVertex3f(0.4f, -1.2f, tm12); //define el segundo vértice del quad.
    glVertex3f(-0.4f, -0.5f, tm12); //define el tercer vértice del quad.
    glVertex3f(1.0f, 1.4f, tm12); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.

    //Parte superior del cuerpo del caballo con dos caras.
    glPushMatrix(); //guarda la matriz actual en la pila
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(0.3f, 1.0f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(1.0f, 1.4f, tm12); //define el primer vértice del quad.
    glVertex3f(1.0f, 1.4f, -tm12); //define el segundo vértice del quad.
    glVertex3f(2.6f, 0.8f, -tm12 + 0.5f); //define el tercer vértice del quad.
    glVertex3f(2.6f, 0.8f, tm12 - 0.5f); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads

    //Parte inferior del cuerpo del caballo con dos caras.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(-0.2f, -1.0f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(0.5f, -0.2f, tm12); //define el primer vértice del quad.
    glVertex3f(0.5f, -0.2f, -tm12); //define el segundo vértice del quad.
    glVertex3f(2.6f, 0.4f, -tm12 + 0.5f); //define el tercer vértice del quad.
    glVertex3f(2.6f, 0.4f, tm12 - 0.5f); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.

    //Cara lateral izquierda del cuerpo del caballo con cuatro caras.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(0.2f, 0.0f, -1.0f); //establece la normal para las caras del quad.
    glVertex3f(0.5f, -0.2f, -tm12); //define el primer vértice del quad.
    glVertex3f(1.0f, 1.4f, -tm12); //define el segundo vértice del quad.
    glVertex3f(2.6f, 0.8f, -tm12 + 0.5f); //define el tercer vértice del quad.
    glVertex3f(2.6f, 0.4f, -tm12 + 0.5f); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.


    //Cara lateral derecha del cuerpo del caballo con cuatro caras.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(0.2f, 0.0f, 1.0f); //establece la normal para las caras del quad.
    glVertex3f(0.5f, -0.2f, tm12); //define el primer vértice del quad.
    glVertex3f(1.0f, 1.4f, tm12); //define el segundo vértice del quad.
    glVertex3f(2.6f, 0.8f, tm12 - 0.5f); //define el tercer vértice del quad.
    glVertex3f(2.6f, 0.4f, tm12 - 0.5f); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.


    //Cara trasera del cuerpo del caballo con cuatro caras.
    glBegin(GL_QUADS); //comienza a definir un conjunto de quads (cuadriláteros).
    glNormal3f(1.0f, 0.0f, 0.0f); //establece la normal para las caras del quad.
    glVertex3f(2.6f, 0.4f, -tm12 + 0.5f); //define el primer vértice del quad.
    glVertex3f(2.6f, 0.8f, -tm12 + 0.5f); //define el segundo vértice del quad.
    glVertex3f(2.6f, 0.4f, tm12 - 0.5f); //define el tercer vértice del quad.
    glVertex3f(2.6f, 0.8f, tm12 - 0.5f); //define el cuarto vértice del quad.
    glEnd(); //finaliza la definición del conjunto de quads.
    
    //El tm12 tiene como función representar el desplazamiento a lo largo del eje z en varias 

    //Restaura la matriz de modelo-vista.
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    // Dibuja las patas del caballo utilizando toros sólidos.
    // Primera pata.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 1.6f, 0.0f); //traslada la pata a la posición (0.0, 1.6, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la pata -90 grados alrededor del eje x.
    glScalef(0.86, 0.86, 0.25); //escala la pata en los ejes x, y, y z.
    glutSolidTorus(1.0f, 0.3f, 50, 50); //dibuja un toro sólido con radios 1.0 y 0.3, usando 50 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.


    //Segunda pata.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 1.5f, 0.0f); //traslada la pata a la posición (0.0, 1.5, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la pata -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala la pata en los ejes x, y, y z.
    glutSolidTorus(0.8f, 0.3f, 50, 50); //dibuja un toro sólido con radios 0.8 y 0.3, usando 50 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.

    //Tercera pata.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 1.3f, 0.0f); //traslada la pata a la posición (0.0, 1.3, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la pata -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala la pata en los ejes x, y, y z.
    glutSolidTorus(1.0f, 0.3f, 50, 50); //dibuja un toro sólido con radios 1.0 y 0.3, usando 50 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.


    // Cuarta pata.
    glPushMatrix(); //guarda la matriz actual en la pila.
    glTranslatef(0.0f, 1.5f, 0.0f); //traslada la pata a la posición (0.0, 1.5, 0.0).
    glRotated(-90, 1.0f, 0.0f, 0.0f); //rota la pata -90 grados alrededor del eje x.
    glScalef(1.0, 1.0, 0.2); //escala la pata en los ejes x, y, y z.
    glutSolidTorus(0.8f, 0.3f, 50, 50); //dibuja un toro sólido con radios 0.8 y 0.3, usando 50 segmentos en cada dirección.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.


    //Llamada a la función dibujar_fondo().
    dibujar_fondo();
    glPopMatrix();
}

void dibujar_Torre_blanca(){

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

    glScalef(0.29 / dd, 0.30 / dd, 0.29 / dd);  //escalar la figura.
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

void dibujar_Torre_negra(){

    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 4 y establece el color a negro.
    indice = indice02;
    pieza = 4;
    glColor3f(0.0, 0.0, 0.0); //negro.

    //Configuración de la matriz de modelo-vista.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(Sx, Sy, Sz); //trasladar la figura en las coordenadas (Sx, Sy, Sz).

    glScalef(0.29 / dd, 0.30 / dd, 0.29 / dd);  //escalar la figura.
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

void dibujar_Peon_blanco(){

    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 1 y establece el color a blanco.
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

void dibujar_Peon_negro(){

    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 1 y establece el color a negro.
    pieza = 1;
    glColor3f(0.0, 0.0, 0.0); //negro.

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

void tablero_sinpiezas(){
    dibujar_tablero();
}

void dibujar_tablero() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            float x = i * 1.0;
            float y = j * 1.0;
            float z = 0.0;

            // Alternate the color of the cubes to create a checkerboard pattern
            if ((i + j) % 2 == 0) {
                glColor3f(1.0, 0.75, 0.8); // White
            } else {
                glColor3f(0.5, 0.0, 0.5); // Black
            }

            dibujar_cubo(x, y, z);
            }
    
    }
}

void movimientitos(){
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //configura la matriz de vista para la cámara.

    //Aplicamos las traslaciones y rotaciones según las variables de posición y rotación.
    glTranslatef(eje_x, eje_y, eje_z);
    glRotatef(eje_x, 1.0, 0.0, 0.0);
    glRotatef(eje_y, 0.0, 1.0, 0.0);
    glRotatef(eje_z, 0.0, 0.0, 1.0);

    glRotatef(eje_w, 1.0, 0.0, 0.0);
    glRotatef(eje_a, 0.0, 1.0, 0.0);
    glRotatef(eje_d, 0.0, 0.0, 1.0);
}

void piezas_blancas(){
    switch (piezab) {
    case 1:
        movimientitos();
        texto_Rey();
        dibujar_Rey_blanco();
        break;
    case 2:
        movimientitos();
        texto_Reina();
        dibujar_Reina_blanca();
        break;
    case 3:
        movimientitos();
        texto_Alfil();
        dibujar_Alfil_blanco();
        break;
    case 4:
        movimientitos();
        texto_Caballo();
        dibujar_Caballo_blanco();
        break;
    case 5:
        movimientitos();
        texto_Torre();
        dibujar_Torre_blanca();
        break;
    case 6:
        movimientitos();
        texto_Peon();
        dibujar_Peon_blanco();
        break;
    }
    glFlush(); //forzamos el renderizado.
}

void piezas_negras(){
    switch (piezan) {
    case 7:
        movimientitos();
        texto_Rey();
        dibujar_Rey_negro();
        break;
    case 8:
        movimientitos();
        texto_Reina();
        dibujar_Reina_negra();
        break;
    case 9:
        movimientitos();
        texto_Alfil();
        dibujar_Alfil_negro();
        break;
    case 10:
        movimientitos();
        texto_Caballo();
        dibujar_Caballo_negro();
        break;
    case 11:
        movimientitos();
        texto_Torre();
        dibujar_Torre_negra();
        break;
    case 12:
        movimientitos();
        texto_Peon();
        dibujar_Peon_negro();
        break;
    }
    glFlush(); //forzamos el renderizado.
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    piezas();
    glutSwapBuffers();
}

//Función para manejar las teclas especiales.
void specialKeys(int key, int x, int y) {

    //Evaluamos la tecla especial presionada.
    switch (key) {

        //Si es la tecla de flecha derecha, incrementamos la posición en el eje x.
        case GLUT_KEY_RIGHT:
            eje_x += 0.1;
            break;

        //Si es la tecla de flecha izquierda, incrementamos la posición en el eje y.
        case GLUT_KEY_LEFT:
            eje_y += 0.1;
            break;

        //Si es la tecla de flecha abajo, salimos del programa.
        case GLUT_KEY_DOWN:
            exit(0);
            break;
    }  
    glutSwapBuffers();
    glutPostRedisplay(); //solicitamos una redibujado de la escena.
}

//Función para manejar las teclas 'x', 'y' y 'z'.
void movimientoMenu(unsigned char key, int x, int y) {
    switch (key) { //evaluamos la tecla presionada.

        //Si es 'x' o 'X', incrementamos la posición en el eje x.
        case 'x':
        case 'X':
            eje_x += 0.1;
            break;

        //Si es 'y' o 'Y', incrementamos la posición en el eje y.
        case 'y':
        case 'Y':
            eje_y += 0.1;
            break;

        //Si es 'z' o 'Z', incrementamos la posición en el eje z.
        case 'z':
        case 'Z':
            eje_z += 0.1;
            break;
    }
    glutPostRedisplay(); //solicitamos una redibujado de la escena.
}

//Función para manejar las teclas 'w', 'a' y 'd' para rotar la figura.
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

//Función para manejar las teclas 'o', 'p', 'i' y 'u' para mover la figura.
void movercamara(int key, int x, int y) {
    switch (key) { //evaluamos la tecla presionada

    //Si es 'O' u 'o', se mueve la cámara positivamente en el eje x.   
    case 'O':
    case 'o':
        cameraX -= 0.1;
        break;

    //Si es 'P' o 'p', se mueve la cámara negativamente en el eje x. 
    case 'P':
    case 'p':
        cameraX += 0.1;
        break;

    //Si es 'I' o 'i', se mueve la cámara positivamente en el eje y.
    case 'I':
    case 'i':
        cameraY += 0.1;
        break;

    //Si es 'U' o 'u', se mueve la cámara negativamente en el eje y.
    case 'U':
    case 'u':
        cameraY -= 0.1;
        break;
    }
    glutPostRedisplay();
}


static void reshape01(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); //establecemos la ventana de visualización (viewport) con las dimensiones dadas.
    glMatrixMode(GL_PROJECTION); //seleccionamos y configuramos la matriz de proyección
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h); //configuramos una proyección ortográfica 2D
    reshape02(w, h);
}

//Función que configura la proyección y el área de visualización en la ventana.
void reshape02(int w, int h) {
    glViewport(0, 0, w, h); //establece el área de visualización en función del tamaño de la ventana.
    glMatrixMode(GL_PROJECTION); //cambia a la matriz de proyección y carga una matriz de identidad.
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0); // establece la perspectiva de la cámara usando gluPerspective.
    glMatrixMode(GL_MODELVIEW); //cambia a la matriz de modelo-vista.
}


//Esta función inicializa algunos estados de OpenGL.
static void init01(void) {
   glClearColor(1.0, 1.0, 1.0, 0.0); //establece el color de fondo como blanco.
   glShadeModel(GL_SMOOTH); //establece el modelo de sombreado como suavizado (GL_SMOOTH).
}

//Función para manejar las selecciones del menú.
void menu(int value) {
    if (value >= 1 && value <= 6) { //verificamos si el valor está en el rango de 1 a 4, correspondiente a las figuras.
        piezab = value; //asignamos el valor de la figura seleccionada.
    } 
    else if (value >= 7 && value <= 12) { //si no, verificamos si el valor está en el rango de 11 a 15, correspondiente a los colores.
        piezan = value; //asignamos el valor del color seleccionado ajustando el rango.

    }
    glutPostRedisplay(); //solicitamos una redibujado de la escena.
}

void tableros(){
    tablero_sinpiezas();
}
//Función para manejar movimientos basados en teclas.
void movimientos(unsigned char key, int x, int y) {
    movimientoMenu(key, x, y);
    rotarfigura(key, 0, 0, 0);  
    movercamara(key, x, y);
}

void piezas(){
    piezas_blancas();
    piezas_negras();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("AJEDREZ :D");

    // Configura la proyección ortográfica y el color de fondo.
    glOrtho(-5, 5, -5, 5, -5, 5);
    // Establecer el color de fondo a naranja claro
    glClearColor(1.0, 0.8, 0.4, 1.0);

    int piezasBlancasSubMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Rey", 1);
    glutAddMenuEntry("Reina", 2);
    glutAddMenuEntry("Alfil", 3);
    glutAddMenuEntry("Caballo", 4);
    glutAddMenuEntry("Torre", 5);
    glutAddMenuEntry("Peon", 6);

    int piezasNegrasSubMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Rey", 7);
    glutAddMenuEntry("Reina", 8);
    glutAddMenuEntry("Alfil", 9);
    glutAddMenuEntry("Caballo", 10);
    glutAddMenuEntry("Torre", 11);
    glutAddMenuEntry("Peon", 12);

    int moverSubMenuID = glutCreateMenu(movimientoMenu); //creamos submenús para mover y rotar.

    //Agregamos opciones al submenú de mover.
    glutAddMenuEntry("Mover en X (tecla 'x')", 'x');
    glutAddMenuEntry("Mover en Y (tecla 'y')", 'y');
    glutAddMenuEntry("Mover en Z (tecla 'z')", 'z');;

    int rotarfig = glutCreateMenu(rotarfigura);

    //Agregamos opciones al submenú de rotar.
    glutAddMenuEntry("Rotar en X (tecla 'w')", 'w');
    glutAddMenuEntry("Rotar en Y (tecla 'a')", 'a');
    glutAddMenuEntry("Rotar en Z (tecla 'd')", 'd');

    int llavesSubMenuID = glutCreateMenu(specialKeys); //creamos submenús para las teclas especiales.

    //Agregamos opciones al submenú de teclas especiales.
    glutAddMenuEntry("Mover en X (tecla 'derecha')", GLUT_KEY_RIGHT);
    glutAddMenuEntry("Mover en Y (tecla 'izquierda')", GLUT_KEY_LEFT);
    glutAddMenuEntry("Salir del programa (tecla 'abajo')", 27); //27 representa la tecla Esc.

    int movcam = glutCreateMenu(movercamara); //creamos submenús para mover la cámara.

    //Agregamos opciones al submenú de mover la cámara.
    glutAddMenuEntry("Mover camara en X positivo (tecla 'p')", 'p');
    glutAddMenuEntry("Mover camara en X negativo (tecla 'o')", 'o');
    glutAddMenuEntry("Mover camara en Y positivo (tecla 'i')", 'i');
    glutAddMenuEntry("Mover camara en Y negativo (tecla 'u')", 'u');

    int piezasSubMenu = glutCreateMenu(piezas);
    glutAddSubMenu("Blancas", piezasBlancasSubMenu);
    glutAddSubMenu("Negras", piezasNegrasSubMenu);
    glutAddSubMenu("Ejes", moverSubMenuID);
    glutAddSubMenu("Llaves especiales", llavesSubMenuID);
    glutAddSubMenu("Rotar", rotarfig);
    glutAddSubMenu("Mover camara", movcam);

    int tablerosinpiezas = glutCreateMenu(tablero_sinpiezas);
    glutAddSubMenu("Mostrar tablero", dibujar_tablero);
    glutAddSubMenu("Ejes", moverSubMenuID);
    glutAddSubMenu("Llaves especiales", llavesSubMenuID);
    glutAddSubMenu("Rotar", rotarfig);
    glutAddSubMenu("Mover camara", movcam);

    int tableroSubMenu = glutCreateMenu(tableros);
    glutAddSubMenu("Sin piezas", tablerosinpiezas);


    glutCreateMenu(menu);
    glutAddSubMenu("Piezas", piezasSubMenu);
    glutAddSubMenu("Tablero", tableroSubMenu);

    glutAttachMenu(GLUT_RIGHT_BUTTON); //adjuntamos el menú principal al botón derecho del ratón.

    //Definimos las funciones de visualización y redimensionamiento.
    glutDisplayFunc(display);
    glutReshapeFunc(reshape01);

    //Definimos las funciones para las teclas especiales y teclas normales.
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(movimientos);

    glutMainLoop(); //iniciamos el bucle principal de GLUT.
    return 0;
}

