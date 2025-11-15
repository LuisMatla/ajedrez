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

//Declaramos como variables globales para que se puedan hacer las ventanas
int piezablanca, piezanegra, tablero, tableroconpiezas, ajedrez, cuborubik;

//Declaración de variables globales para la rotacion de la camara en X, Y, Z.
float rotationAngleX = 0.0;
float rotationAngleY = 0.0;
float rotationAngleZ = 0.0;

//Declaración de una variable para calcular el angulo
float angulo = 0.0f;

float torreA1PosX = 0.0;
float caballoB1PosX = 0.0;
float alfilC1PosX = 0.0;
float reinaD1PosX = 0.0;
float reyE1PosX = 0.0;
float alfilF1PosX = 0.0;
float caballoG1PosX = 0.0;
float torreH1PosX = 0.0;
float alfilC1PosY2 = 0.0;
float reinaD1PosY2 = 0.0;
float reyE1PosY = 0.0;
float alfilF1PosY2 = 0.0;
float alfilC8PosY2 = 0.0;
float reinaD8PosY2 = 0.0;
float reyE8PosY = 0.0;
float peonA1PosX = 0.0;
float peonB1PosX = 0.0;
float peonC1PosX = 0.0;
float peonD1PosX = 0.0;
float peonE1PosX = 0.0;
float peonF1PosX = 0.0;
float peonG1PosX = 0.0;
float peonH1PosX = 0.0;
float peonA8PosX = 0.0;
float peonB8PosX = 0.0;
float peonC8PosX = 0.0;
float peonD8PosX = 0.0;
float peonE8PosX = 0.0;
float peonF8PosX = 0.0;
float peonG8PosX = 0.0;
float peonH8PosX = 0.0;
float alfilF8PosY2 = 0.0;





float peonA2PosX = 0.0;
int primerA2Movimiento = 1;
float peonB2PosX = 0.0;
int primerB2Movimiento = 1;
float peonC2PosX = 0.0;
int primerC2Movimiento = 1;
float peonD2PosX = 0.0;
int primerD2Movimiento = 1;
float peonE2PosX = 0.0;
int primerE2Movimiento = 1;
float peonF2PosX = 0.0;
int primerF2Movimiento = 1;
float peonG2PosX = 0.0;
int primerG2Movimiento = 1;
float peonH2PosX = 0.0;
int primerH2Movimiento = 1;

float peonA7PosX = 0.0;
int primerA7Movimiento = 1;
float peonB7PosX = 0.0;
int primerB7Movimiento = 1;
float peonC7PosX = 0.0;
int primerC7Movimiento = 1;
float peonD7PosX = 0.0;
int primerD7Movimiento = 1;
float peonE7PosX = 0.0;
int primerE7Movimiento = 1;
float peonF7PosX = 0.0;
int primerF7Movimiento = 1;
float peonG7PosX = 0.0;
int primerG7Movimiento = 1;
float peonH7PosX = 0.0;
int primerH7Movimiento = 1;

float torreA8PosX = 0.0;
float caballoB8PosX = 0.0;
float alfilC8PosX = 0.0;
float reinaD8PosX = 0.0;
float reyE8PosX = 0.0;
float alfilF8PosX = 0.0;
float caballoG8PosX = 0.0;
float torreH8PosX = 0.0;


//Declaración de variable glogal para las piezas blancas y negras.
int piezab = 0;
int piezan = 0;

//Declaración de variable para el tamaño de la ventana.
int windowWidth = 800;
int windowHeight = 600;

//Variables globales para que cualquier figura se pueda mover en el eje x, y, z.
float eje_x = 0.0;
float eje_y = 0.0;
float eje_z = 0.0;

float eje_m = 0.0;
float eje_l = 0.0;
float eje_n = 0.0;

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

//Esta función nos es un texto el cual cuando aparece el Rey esta hace que diga "REY" en la esquina inferior izquierda.
void texto_Rey(){
    glClear(GL_COLOR_BUFFER_BIT); //borra el buffer de color para preparar la escena.
    glColor3f(0.0, 0.0, 0.0); //establece el color de dibujo a negro.
    glRasterPos2f(-1.7, -1.7); //establece la posición inicial para el texto.
    char text[] = "REY"; //declara una cadena de caracteres para el texto.
    for (int i = 0; text[i] != '\0'; i++) { //itera a través de cada carácter de la cadena hasta llegar al carácter nulo '\0'.
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]); //utiliza la función glutBitmapCharacter para renderizar cada carácter en la posición actual.
    }
    glFlush(); //vacía los comandos pendientes para asegurar que el texto se muestra.
}

//Esta función nos es un texto el cual cuando aparece la Reina esta hace que diga "REINA" en la esquina inferior izquierda.
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

//Esta función nos es un texto el cual cuando aparece el Alfil esta hace que diga "ALFIL" en la esquina inferior izquierda.
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

//Esta función nos es un texto el cual cuando aparece el Caballo esta hace que diga "CABALLO" en la esquina inferior izquierda.
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

//Esta función nos es un texto el cual cuando aparece la Torre esta hace que diga "TORRE" en la esquina inferior izquierda.
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

//Esta función nos es un texto el cual cuando aparece el Peón esta hace que diga "PEÓN" en la esquina inferior izquierda.
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

// Esta función muestra un texto que dice "TABLERO" en la esquina inferior izquierda cuando aparece el Rey.
void texto_Tablero() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); //negro.
    glRasterPos2f(-1.7, -1.7); //posición del texto.
    char text[] = "TABLERO"; //declaramos una cadena de caracteres para el texto.
    for (int i = 0; text[i] != '\0'; i++) { //iteramos a través de cada carácter de la cadena hasta llegar al carácter nulo '\0'.
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);//utilizamos la función glutBitmapCharacter para renderizar cada carácter en la posición actual.
}
    glFlush();
}

//Función que dibuja al Rey.
void dibujar_Rey(){

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

//Función que cambia de color blanco la pieza del Rey.
void dibujar_Rey_blanco(){
    glColor3f(1.0, 1.0, 1.0); //blanco.
    dibujar_Rey();
}

//Función que cambia de color negro la pieza del Rey.
void dibujar_Rey_negro(){
    glColor3f(0.0, 0.0, 0.0); //negro.
    dibujar_Rey();
}

//Función que dibuja a la Reina.
void dibujar_Reina(){
    
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

//Función que cambia de color blanco la pieza de la Reina.
void dibujar_Reina_blanca(){
    glColor3f(1.0, 1.0, 1.0); //blanco.
    dibujar_Reina();
}

//Función que cambia de color negro la pieza de la Reina.
void dibujar_Reina_negra(){
    glColor3f(0.0, 0.0, 0.0); //negro
    dibujar_Reina();
}

//Función que dibuja al Alfil.
void dibujar_Alfil(){

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

//Función que cambia de color blanco la pieza del Alfil.
void dibujar_Alfil_blanco(){
    glColor3f(1.0, 1.0, 1.0); //blanco.
    dibujar_Alfil();
}

//Función que cambia de color negro la pieza del Alfil.
void dibujar_Alfil_negro(){
    glColor3f(0.0, 0.0, 0.0); //negro.
    dibujar_Alfil();
}

//Función que dibuja al Caballo.
void dibujar_Caballo(){

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

//Función que cambia de color blanco la pieza del Caballo.
void dibujar_Caballo_blanco(){
	glRotatef(90, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0, 1.0, 1.0); //blanco
    dibujar_Caballo();
}

//Función que cambia de color negro la pieza del Caballo.
void dibujar_Caballo_negro(){
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
    glColor3f(0.0, 0.0, 0.0); //negro.
    dibujar_Caballo();
}

//Función que dibuja a la Torre.
void dibujar_Torre(){

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

//Función que cambia de color blanco la pieza de la Torre.
void dibujar_Torre_blanca(){
    glColor3f(1.0, 1.0, 1.0); //blanco.
    dibujar_Torre();
}

//Función que cambia de color negro la pieza de la Torre.
void dibujar_Torre_negra(){
    glColor3f(0.0, 0.0, 0.0); //negro.
    dibujar_Torre();
}

//Función que dibuja al Peón.
void dibujar_Peon(){
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

//Función que cambia de color blanco la pieza del Peón.
void dibujar_Peon_blanco(){
    glColor3f(1.0, 1.0, 1.0); //blanco.
    dibujar_Peon();
}

//Función que cambia de color negro la pieza del Peón.
void dibujar_Peon_negro(){
    glColor3f(0.0, 0.0, 0.0); //negro.
    dibujar_Peon();
}


//Función para dibujar un tablero de ajedrez en 3D.
void dibujar_tablero() {
    for (int i = 0; i < 8; ++i) { //bucle externo para iterar a través de las filas del tablero.
        for (int j = 0; j < 8; ++j) { //bucle interno para iterar a través de las columnas del tablero.
            
            //Cálculo de las coordenadas (x, y, z) del cubo en la posición (i, j, 0).
            float x = i * 1.0; //multiplico la posición en fila por 1.0.
            float y = j * 1.0; //multiplico la posición en columna por 1.0.
            float z = 0.0;
            if ((i + j) % 2 == 0) { //verificación de si la suma de la posición en fila y columna es par o impar.

                //Si la suma es par, establecer el color del cubo en blanco.
                glColor3f(1.0, 0.75, 0.8); //rosa claro.
            } else {

                //Si la suma es impar, establecer el color del cubo en morado oscuro.
                glColor3f(0.5, 0.0, 0.5);  //morado oscuro.
            }
            dibujar_cubo(x, y, z); //llamada a una función externa para dibujar un cubo en las coordenadas calculadas.
        }
    }
}


//Función para aplicar transformaciones y configurar la matriz de vista para la cámara.
void movimientitos() {
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //configura la matriz de vista para la cámara utilizando la función gluLookAt.

    //Aplica traslaciones y rotaciones según las variables de posición y rotación.
    glTranslatef(eje_x, eje_y, eje_z);  //translación en los ejes x, y, z.
    
    glRotatef(eje_x, 1.0, 0.0, 0.0); //rotación alrededor del eje x.
    glRotatef(eje_y, 0.0, 1.0, 0.0); //rotación alrededor del eje y.
    glRotatef(eje_z, 0.0, 0.0, 1.0); //rotación alrededor del eje z.

    //Rotaciones adicionales utilizando otras variables.
    glRotatef(eje_w, 1.0, 0.0, 0.0); //rotación adicional alrededor del eje x.
    glRotatef(eje_a, 0.0, 1.0, 0.0); //rotación adicional alrededor del eje y.
    glRotatef(eje_d, 0.0, 0.0, 1.0); //rotación adicional alrededor del eje z.
}

//Función para dibujar y posicionar piezas blancas en el tablero.
void piezas_blancas() {

    //Utiliza un switch para determinar el tipo de pieza blanca (según la variable piezab).
    switch (piezab) {
        case 1:
            movimientitos(); //aplica transformaciones y configura la matriz de vista para la cámara.
            texto_Rey(); //muestra texto relacionado con el Rey blanco.
            dibujar_Rey_blanco(); //dibuja el modelo del Rey blanco.
            break;
        case 2:
            movimientitos(); //aplica transformaciones y configura la matriz de vista para la cámara.
            texto_Reina(); //muestra texto relacionado con la Reina blanca.
            dibujar_Reina_blanca(); //dibuja el modelo de la Reina blanca.
            break;
        case 3:
            movimientitos(); //aplica transformaciones y configura la matriz de vista para la cámara.
            texto_Alfil(); //muestra texto relacionado con el Alfil blanco.
            dibujar_Alfil_blanco(); //dibuja el modelo del Alfil blanco.
            break;
        case 4:
            movimientitos(); //aplica transformaciones y configura la matriz de vista para la cámara.
            texto_Caballo(); //muestra texto relacionado con el Caballo blanco.
            dibujar_Caballo_blanco(); //dibuja el modelo del Caballo blanco.
            break;
        case 5:
            movimientitos(); //aplica transformaciones y configura la matriz de vista para la cámara.
            texto_Torre(); //muestra texto relacionado con la Torre blanca.
            dibujar_Torre_blanca(); //dibuja el modelo de la Torre blanca.
            break;
        case 6:
            movimientitos(); //aplica transformaciones y configura la matriz de vista para la cámara.
            texto_Peon(); //muestra texto relacionado con el Peón blanco.
            dibujar_Peon_blanco(); //dibuja el modelo del Peón blanco.
            break;
    }
    glFlush(); //forzamos el renderizado para que las modificaciones sean visibles.
}


//Función para dibujar y posicionar piezas negras en el tablero.
void piezas_negras() {

    //utiliza un switch para determinar el tipo de pieza negra (según la variable piezan).
    switch (piezan) {
        case 7:
            movimientitos(); //aplica transformaciones y configura la matriz de vista para la cámara.
            texto_Rey(); //muestra texto relacionado con el Rey negro.
            dibujar_Rey_negro(); //dibuja el modelo del Rey negro.
            break;
        case 8:
            movimientitos(); //aplica transformaciones y configura la matriz de vista para la cámara.
            texto_Reina(); //muestra texto relacionado con la Reina negra.
            dibujar_Reina_negra(); //dibuja el modelo de la Reina negra.
            break;
        case 9:
            movimientitos(); //aplica transformaciones y configura la matriz de vista para la cámara.
            texto_Alfil(); //muestra texto relacionado con el Alfil negro.
            dibujar_Alfil_negro(); //dibuja el modelo del Alfil negro.
            break;
        case 10:
            movimientitos(); //aplica transformaciones y configura la matriz de vista para la cámara.
            texto_Caballo(); //muestra texto relacionado con el Caballo negro.
            dibujar_Caballo_negro(); //dibuja el modelo del Caballo negro.
            break;
        case 11:
            movimientitos(); //aplica transformaciones y configura la matriz de vista para la cámara.
            texto_Torre(); //muestra texto relacionado con la Torre negra.
            dibujar_Torre_negra(); //dibuja el modelo de la Torre negra.
            break;
        case 12:
            movimientitos(); //aplica transformaciones y configura la matriz de vista para la cámara.
            texto_Peon(); //muestra texto relacionado con el Peón negro.
            dibujar_Peon_negro();  //dibuja el modelo del Peón negro.
            break;
    }
    glFlush(); //forzamos el renderizado para que las modificaciones sean visibles.
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

//Función para manejar las teclas 'x', 'y' y 'z'.
void movimientoMenu2(unsigned char key, int m, int l) {
    switch (key) { //evaluamos la tecla presionada.

        //Si es 'x' o 'X', incrementamos la posición en el eje x.
        case 'x':
        case 'X':
            eje_m += 0.1;
            break;

        //Si es 'y' o 'Y', incrementamos la posición en el eje y.
        case 'y':
        case 'Y':
            eje_l += 0.1;
            break;

        //Si es 'z' o 'Z', incrementamos la posición en el eje z.
        case 'z':
        case 'Z':
            eje_n += 0.1;
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

//Función para manejar cambios en el tamaño de la ventana (reshape).
static void reshape01(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); //establecemos la ventana de visualización (viewport) con las dimensiones dadas.
    glMatrixMode(GL_PROJECTION); //seleccionamos y configuramos la matriz de proyección
    glLoadIdentity();

    //Configuramos una proyección ortográfica 2D centrada en (0, 0) con el tamaño de la ventana
    gluOrtho2D(-w / 2.0, w / 2.0, -h / 2.0, h / 2.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
   glClearColor(0.87f, 0.72f, 0.53f, 1.0f); //establece el color de fondo como blanco.
   glShadeModel(GL_SMOOTH); //establece el modelo de sombreado como suavizado (GL_SMOOTH).
}

//Función para manejar las selecciones del menú.
void menupiezasnegras(int value) {
    if (value >= 7 && value <= 11) { // Verificamos si el valor está en el rango de 1 a 6, correspondiente a las figuras.
        piezan = value; // Asignamos el valor de la figura seleccionada.
        glutPostRedisplay(); // Solicitamos un redibujado de la escena.
    }
}

// Función para manejar las selecciones del menú.
void menupiezasblancas(int value) {
    if (value >= 1 && value <= 6) { // Verificamos si el valor está en el rango de 1 a 6, correspondiente a las figuras.
        piezab = value; // Asignamos el valor de la figura seleccionada.
        glutPostRedisplay(); // Solicitamos un redibujado de la escena.
    }
}

//Función para manejar movimientos basados en teclas.
void movimientos(unsigned char key, int x, int y) {
    movimientoMenu(key, x, y);
    rotarfigura(key, 0, 0, 0);  
    movercamara(key, x, y);
}

//Función para manejar movimientos basados en teclas.
void movimientos2(unsigned char key, int m, int l) {
    movimientoMenu2(key, m, l);
    rotarfigura(key, 0, 0, 0);  
    movercamara(key, m, l);
}

//Función para dibujar una torre blanca en una posición específica.
void A1(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x, y, z - 0.35); //traslada la pieza a la posición especificada en el eje (x, y, z - 0.35).
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); //rota la pieza -90 grados alrededor del eje x.
    dibujar_Torre_blanca(); //llama a la función para dibujar la torre blanca.
    glPopMatrix(); //restaura la matriz original desde la pila de matrices.
}

//Función para dibujar el caballo blanco en una posición específica.
void B1(float x, float y, float z){
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 1, y, z - 0.35); //traslada la pieza a la posición especificada en el eje (x + 1, y, z - 0.35).
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); //rota la pieza -90 grados alrededor del eje x.
    dibujar_Caballo_blanco(); //llama a la función para dibujar el caballo blanco.
	glPopMatrix(); //restaura la matriz original desde la pila de matrices.
}

//Función para dibujar el alfil blanco en una posición específica.
void C1(float x, float y, float z){
	glPushMatrix(); //guarda la matriz actual en la pila de matrices.
	glTranslatef(x + 2, y , z - 0.35); //traslada la pieza a la posición especificada en el eje (x + 2, y, z - 0.35).
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //rota la pieza 270 grados alrededor del eje x.
	dibujar_Alfil_blanco(); //llama a la función para dibujar el alfil blanco.
	glPopMatrix(); //restaura la matriz original desde la pila de matrices.
}

//Función para dibujar la reina blanca en una posición específica.
void D1(float x, float y, float z){
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 3, y , z - 0.35); //traslada la pieza a la posición especificada en el eje (x + 3, y, z - 0.35).
    glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //rota la pieza 270 grados alrededor del eje x.
    dibujar_Reina_blanca(); //llama a la función para dibujar la reina blanca.
    glPopMatrix(); //restaura la matriz original desde la pila de matrices.
}

//Función para dibujar el rey blanco en una posición específica.
void E1(float x, float y, float z){
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 4, y , z - 0.35); //traslada la pieza a la posición especificada en el eje (x + 4, y, z - 0.35).
    glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //rota la pieza 270 grados alrededor del eje x.
    dibujar_Rey_blanco(); //llama a la función para dibujar el rey blanco.
    glPopMatrix(); //restaura la matriz original desde la pila de matrices.
}

//Función para dibujar el alfil blanco en una posición específica.
void F1(float x, float y, float z){
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 5, y , z - 0.35); //traslada la pieza a la posición especificada en el eje (x + 5, y, z - 0.35).
    glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //rota la pieza 270 grados alrededor del eje x.
    dibujar_Alfil_blanco(); //llama a la función para dibujar el alfil blanco.
    glPopMatrix(); //restaura la matriz original desde la pila de matrices.
}

//Función para dibujar el caballo blanco en una posición específica.
void G1(float x, float y, float z){
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 6, y , z - 0.35); //traslada la pieza a la posición especificada en el eje (x + 6, y, z - 0.35).
    glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //rota la pieza 270 grados alrededor del eje x.
    dibujar_Caballo_blanco(); //llama a la función para dibujar el caballo blanco.
    glPopMatrix(); //restaura la matriz original desde la pila de matrices.
}

//Función para dibujar una torre blanca en una posición específica.
void H1(float x, float y, float z){
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 7, y , z - 0.35); //traslada la pieza a la posición especificada en el eje (x + 7, y, z - 0.35).
    glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //rota la pieza 270 grados alrededor del eje x.
    dibujar_Torre_blanca(); //llama a la función para dibujar la torre blanca.
    glPopMatrix(); //restaura la matriz original desde la pila de matrices.
}

//Función para dibujar un peón blanco en una posición específica.
void A2(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x, y + 1.0, z - 1.0); //traslada la pieza a la posición especificada en el eje (x, y + 1.0, z - 1.0).
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); //rota la pieza 90 grados alrededor del eje x.
    dibujar_Peon_blanco(); //llama a la función para dibujar el peón blanco.
    glPopMatrix(); //restaura la matriz original desde la pila de matrices.
}

//Función para dibujar un peón blanco en una posición específica.
void B2(float x, float y, float z){
	glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 1.0, y + 1.0, z - 1.0); //traslada la pieza a la posición especificada en el eje (x + 1.0, y + 1.0, z - 1.0).
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); //rota la pieza 90 grados alrededor del eje x. 
    dibujar_Peon_blanco(); //llama a la función para dibujar el peón blanco.
    glPopMatrix(); //restaura la matriz original desde la pila de matrices.
}

void C2(float x, float y, float z){
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 2.0, y + 1.0, z - 1.0); //traslada la pieza a la posición especificada en el eje (x + 1.0, y + 1.0, z - 1.0).
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); //rota la pieza 90 grados alrededor del eje x. 
    dibujar_Peon_blanco(); //llama a la función para dibujar el peón blanco.
    glPopMatrix(); //restaura la matriz original desde la pila de matrices.
}

void D2(float x, float y, float z){
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 3.0, y + 1.0, z - 1.0); //traslada la pieza a la posición especificada en el eje (x + 1.0, y + 1.0, z - 1.0).
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); //rota la pieza 90 grados alrededor del eje x. 
    dibujar_Peon_blanco(); //llama a la función para dibujar el peón blanco.
    glPopMatrix(); //restaura la matriz original desde la pila de matrices.
}

void E2(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 4.0, y + 1.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Peon_blanco();
	glPopMatrix();
}

void F2(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 5.0, y + 1.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Peon_blanco();
	glPopMatrix();
}

void G2(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 6.0, y + 1.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Peon_blanco();
	glPopMatrix();
}

void H2(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 7.0, y + 1.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Peon_blanco();
	glPopMatrix();
}

//Piezas negras.
void A8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x, y + 7.0, z  - 0.35 );
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Torre_negra();
	glPopMatrix();
}

void B8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 1.0, y + 7.0, z  - 0.35 );
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Caballo_negro();
	glPopMatrix();
}

void C8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 2.0, y + 7.0, z  - 0.35 );
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Alfil_negro();
	glPopMatrix();
}

void D8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 3.0, y + 7.0, z  - 0.35 );
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Reina_negra();
	glPopMatrix();
}

void E8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 4.0, y + 7, z  - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Rey_negro();
	glPopMatrix();
}

void F8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 5.0, y + 7, z  - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Alfil_negro();
	glPopMatrix();
}

void G8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 6.0, y + 7.0, z  - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Caballo_negro();
	glPopMatrix();
}

void H8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 7.0, y + 7.0, z  - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Torre_negra();
	glPopMatrix();
}

void A7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x , y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Peon_negro();
	glPopMatrix();
}

void B7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 1.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Peon_negro();
	glPopMatrix();
}

void C7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 2.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Peon_negro();
	glPopMatrix();
}

void D7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 3.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Peon_negro();
	glPopMatrix();
}

void E7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 4.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Peon_negro();
	glPopMatrix();
}

void F7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 5.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Peon_negro();
	glPopMatrix();
}

void G7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 6.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Peon_negro();
	glPopMatrix();
}

void H7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 7.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	dibujar_Peon_negro();
	glPopMatrix();
}



void display_piezasblancas() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.87f, 0.72f, 0.53f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    piezas_blancas();
    glutSwapBuffers();
}


void display_piezasnegras() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.87f, 0.72f, 0.53f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    piezas_negras();
    glutSwapBuffers();
}

void display_tablero() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.87f, 0.72f, 0.53f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();  // Reset the modelview matrix
    gluLookAt(5.0, 5.0, 20.0, 0.0, 1.0, 0.0, 2.0, 2.0, 0.0);
    glRotatef(rotationAngleX, 1.0, 0.0, 0.0);
    glRotatef(rotationAngleY, 0.0, 1.0, 0.0);
    glRotatef(rotationAngleZ, 0.0, 0.0, 1.0);

    // Specify coordinates for a single cube
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    texto_Tablero();
    dibujar_tablero(x, y, z); // Call dibujar_cubo with specific coordinates
    
    glutSwapBuffers();
}
void display_tableroconpiezas(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.87f, 0.72f, 0.53f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();  // Reset the modelview matrix
    gluLookAt(5.0, 5.0, 20.0, 0.0, 1.0, 0.0, 2.0, 2.0, 0.0);
    glRotatef(rotationAngleX, 1.0, 0.0, 0.0);
    glRotatef(rotationAngleY, 0.0, 1.0, 0.0);
    glRotatef(rotationAngleZ, 0.0, 0.0, 1.0);

    // Specify coordinates for a single cube
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    dibujar_tablero(x, y, z); // Call dibujar_cubo with specific coordinates
    A1(x, y, z);
    B1(x, y, z);
    C1(x, y, z);
    D1(x, y, z);
    E1(x, y, z);
    F1(x, y, z);
    G1(x, y, z);
    H1(x, y, z);

    A2(x, y, z);
    B2(x, y, z);
    C2(x, y, z);
    D2(x, y, z);
    E2(x, y, z);
    F2(x, y, z);
    G2(x, y, z);
    H2(x, y, z);

    A8(x, y, z);
    B8(x, y, z);
    C8(x, y, z);
    D8(x, y, z);
    E8(x, y, z);
    F8(x, y, z);
    G8(x, y, z);
    H8(x, y, z);

    A7(x, y, z);
    B7(x, y, z);
    C7(x, y, z);
    D7(x, y, z);
    E7(x, y, z);
    F7(x, y, z);
    G7(x, y, z);
    H7(x, y, z);
    glutSwapBuffers();
}

void moverPeonA2() {
    if (primerA2Movimiento) {
        peonA2PosX += 2.0;
        primerA2Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonA2PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverPeonB2() {
    if (primerB2Movimiento) {
        peonB2PosX += 2.0;
        primerB2Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonB2PosX += 1.0;
    }

    glutPostRedisplay();
}
/*
void moverPeonC2() {
    if (primerC2Movimiento) {
        peonC2PosX += 2.0;
        primerC2Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonC2PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverPeonD2() {
    if (primerD2Movimiento) {
        peonD2PosX += 2.0;
        primerD2Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonD2PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverPeonE2() {
    if (primerE2Movimiento) {
        peonE2PosX += 2.0;
        primerE2Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonE2PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverPeonF2() {
    if (primerF2Movimiento) {
        peonF2PosX += 2.0;
        primerF2Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonF2PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverPeonG2() {
    if (primerG2Movimiento) {
        peonG2PosX += 2.0;
        primerG2Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonG2PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverPeonH2() {
    if (primerH2Movimiento) {
        peonH2PosX += 2.0;
        primerH2Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonH2PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverTorreA1() {
    torreA1PosX += 1.0;  // Mueve la torre horizontalmente en cada llamada

    glutPostRedisplay();
}

void moverCaballoB1() {
    caballoB1PosX += 2.0;  // Mueve el caballo dos espacios hacia adelante

    // Mueve el caballo uno a la izquierda o a la derecha
    // Dependiendo de la dirección deseada (izquierda o derecha)
    // Cambia el signo (+ o -) según sea necesario
    caballoB1PosX += 1.0;

    glutPostRedisplay();
}


void moverAlfilC1() {
    alfilC1PosX += 1.0;  // Mueve el alfil en la dirección diagonal (hacia arriba)

    // Mueve el alfil en la dirección diagonal (hacia la izquierda o derecha)
    // Dependiendo de la dirección deseada, puedes ajustar el signo (+ o -)
    alfilC1PosX += 1.0;

    alfilC1PosY2 += 1.0;  // Mueve el alfil en la dirección diagonal (hacia la derecha)

    glutPostRedisplay();
}

void moverReinaD1() {
    // Mueve la reina en horizontal o vertical
    reinaD1PosX += 1.0;  // Puedes ajustar el valor según la dirección y la velocidad

    // Mueve la reina en diagonal
    reinaD1PosX += 1.0;  // Puedes ajustar el valor según la dirección y la velocidad
    reinaD1PosY2 += 1.0;  // Puedes ajustar el valor según la dirección y la velocidad

    glutPostRedisplay();
}

void moverReyE1() {
    reyE1PosX += 1.0;  // Puedes ajustar el valor según la dirección y la velocidad
    reyE1PosY += 1.0;  // Puedes ajustar el valor según la dirección y la velocidad

    glutPostRedisplay();
}


void moverAlfilF1() {
    alfilF1PosX += 1.0;  // Mueve el alfil en la dirección diagonal (hacia arriba)

    // Mueve el alfil en la dirección diagonal (hacia la izquierda o derecha)
    // Dependiendo de la dirección deseada, puedes ajustar el signo (+ o -)
    alfilF1PosX += 1.0;

    alfilF1PosY2 += 1.0;  // Mueve el alfil en la dirección diagonal (hacia la derecha)

    glutPostRedisplay();
}


void moverCaballoG1() {
    caballoG1PosX += 2.0;  // Mueve el caballo dos espacios hacia adelante

    // Mueve el caballo uno a la izquierda o a la derecha
    // Dependiendo de la dirección deseada (izquierda o derecha)
    // Cambia el signo (+ o -) según sea necesario
    caballoG1PosX += 1.0;

    glutPostRedisplay();
}

void moverTorreH1() {
    torreH1PosX += 1.0;  // Mueve la torre horizontalmente en cada llamada

    glutPostRedisplay();
}


void moverTorreA8() {
    torreH1PosX += 1.0;  // Mueve la torre horizontalmente en cada llamada

    glutPostRedisplay();
}

void moverCaballoB8() {
    caballoB8PosX += 2.0;  // Mueve el caballo dos espacios hacia adelante

    // Mueve el caballo uno a la izquierda o a la derecha
    // Dependiendo de la dirección deseada (izquierda o derecha)
    // Cambia el signo (+ o -) según sea necesario
    caballoB8PosX += 1.0;

    glutPostRedisplay();
}


void moverAlfilC8() {
    alfilC8PosX += 1.0;  // Mueve el alfil en la dirección diagonal (hacia arriba)

    // Mueve el alfil en la dirección diagonal (hacia la izquierda o derecha)
    // Dependiendo de la dirección deseada, puedes ajustar el signo (+ o -)
    alfilC8PosX += 1.0;

    alfilC8PosY2 += 1.0;  // Mueve el alfil en la dirección diagonal (hacia la derecha)

    glutPostRedisplay();
}

void moverReinaD8() {
    // Mueve la reina en horizontal o vertical
    reinaD8PosX += 1.0;  // Puedes ajustar el valor según la dirección y la velocidad

    // Mueve la reina en diagonal
    reinaD8PosX += 1.0;  // Puedes ajustar el valor según la dirección y la velocidad
    reinaD8PosY2 += 1.0;  // Puedes ajustar el valor según la dirección y la velocidad

    glutPostRedisplay();
}

void moverReyE8() {
    reyE8PosX += 1.0;  // Puedes ajustar el valor según la dirección y la velocidad
    reyE8PosY += 1.0;  // Puedes ajustar el valor según la dirección y la velocidad

    glutPostRedisplay();
}


void moverAlfilF8() {
    alfilF8PosX += 1.0;  // Mueve el alfil en la dirección diagonal (hacia arriba)

    // Mueve el alfil en la dirección diagonal (hacia la izquierda o derecha)
    // Dependiendo de la dirección deseada, puedes ajustar el signo (+ o -)
    alfilF8PosX += 1.0;

    alfilF8PosY2 += 1.0;  // Mueve el alfil en la dirección diagonal (hacia la derecha)

    glutPostRedisplay();
}


void moverCaballoG8() {
    caballoG8PosX += 2.0;  // Mueve el caballo dos espacios hacia adelante

    // Mueve el caballo uno a la izquierda o a la derecha
    // Dependiendo de la dirección deseada (izquierda o derecha)
    // Cambia el signo (+ o -) según sea necesario
    caballoG8PosX += 1.0;

    glutPostRedisplay();
}

void moverTorreH8() {
    torreH8PosX += 1.0;  // Mueve la torre horizontalmente en cada llamada

    glutPostRedisplay();
}


void moverPeonA7() {
    if (primerA7Movimiento) {
        peonA7PosX += 2.0;
        primerA7Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonA7PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverPeonB7() {
    if (primerB7Movimiento) {
        peonB7PosX += 2.0;
        primerB7Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonB7PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverPeonC7() {
    if (primerC7Movimiento) {
        peonC7PosX += 2.0;
        primerC7Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonC7PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverPeonD7() {
    if (primerD7Movimiento) {
        peonD7PosX += 2.0;
        primerD7Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonD7PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverPeonE7() {
    if (primerE7Movimiento) {
        peonE7PosX += 2.0;
        primerE7Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonE7PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverPeonF7() {
    if (primerF7Movimiento) {
        peonF7PosX += 2.0;
        primerF7Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonF7PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverPeonG7() {
    if (primerG7Movimiento) {
        peonG7PosX += 2.0;
        primerG7Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonG7PosX += 1.0;
    }

    glutPostRedisplay();
}

void moverPeonH7() {
    if (primerH7Movimiento) {
        peonH7PosX += 2.0;
        primerH7Movimiento = 0; // Usamos 0 para representar false
    } else {
        peonH7PosX += 1.0;
    }

    glutPostRedisplay();
}*/

void keyboardA2(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            moverPeonA2();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardB2(unsigned char key, int x, int y) {
    switch (key) {
        case 'y':
            moverPeonB2();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

/*void keyboardC2(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            moverPeonC2();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardD2(unsigned char key, int x, int y) {
    switch (key) {
        case 'e':
            moverPeonD2();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardE2(unsigned char key, int x, int y) {
    switch (key) {
        case 'p':
            moverPeonE2();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardF2(unsigned char key, int x, int y) {
    switch (key) {
        case 'z':
            moverPeonF2();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardG2(unsigned char key, int x, int y) {
    switch (key) {
        case 'i':
            moverPeonG2();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardH2(unsigned char key, int x, int y) {
    switch (key) {
        case 'u':
            moverPeonH2();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardA1(unsigned char key, int x, int y) {
    switch (key) {
        case 'H':
            moverTorreA1();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardB1(unsigned char key, int x, int y) {
    switch (key) {
        case 'O':
            moverCaballoB1();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardC1(unsigned char key, int x, int y) {
    switch (key) {
        case 'B':
            moverAlfilC1();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardD1(unsigned char key, int x, int y) {
    switch (key) {
        case 'C':
            moverReinaD1();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardE1(unsigned char key, int x, int y) {
    switch (key) {
        case 'A':
            moverReyE1();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardF1(unsigned char key, int x, int y) {
    switch (key) {
        case 'Q':
            moverAlfilF1();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardG1(unsigned char key, int x, int y) {
    switch (key) {
        case 'g':
            moverAlfilG1();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardH1(unsigned char key, int x, int y) {
    switch (key) {
        case 'f':
            moverTorreH1();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardA8(unsigned char key, int x, int y) {
    switch (key) {
        case 'U':
            moverTorreA8();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardB8(unsigned char key, int x, int y) {
    switch (key) {
        case 'u':
            moverCaballoB8();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardC8(unsigned char key, int x, int y) {
    switch (key) {
        case 'MB':
            moverAlfilC8();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardD8(unsigned char key, int x, int y) {
    switch (key) {
        case 'J':
            moverReinaD8();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardE8(unsigned char key, int x, int y) {
    switch (key) {
        case 'R':
            moverReyE8();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardF8(unsigned char key, int x, int y) {
    switch (key) {
        case 'K':
            moverAlfilF8();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardG8(unsigned char key, int x, int y) {
    switch (key) {
        case 'V':
            moverAlfilG8();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}

void keyboardH8(unsigned char key, int x, int y) {
    switch (key) {
        case 'X':
            moverTorreH8();
            break;
        // Puedes agregar más casos para manejar otras teclas si es necesario
    }
}*/


void keyboardtodos(unsigned char key, int x, int y) {
    keyboardA2(key, x, y);
    keyboardB2(key, x, y);
    /*keyboardC2(key, x, y);
    keyboardD2(key, x, y);
    keyboardE2(key, x, y);
    keyboardF2(key, x, y);
    keyboardG2(key, x, y);
    keyboardH2(key, x, y);
    keyboardA1(key, x, y);
    keyboardB1(key, x, y);
    keyboardC1(key, x, y);
    keyboardD1(key, x, y);
    keyboardE1(key, x, y);
    keyboardF1(key, x, y);
    keyboardG1(key, x, y);
    keyboardH1(key, x, y);
    keyboardA8(key, x, y);
    keyboardB8(key, x, y);
    keyboardC8(key, x, y);
    keyboardD8(key, x, y);
    keyboardE8(key, x, y);
    keyboardF8(key, x, y);
    keyboardG8(key, x, y);
    keyboardH8(key, x, y);
    keyboardA7(key, x, y);
    keyboardB7(key, x, y);
    keyboardC7(key, x, y);
    keyboardD7(key, x, y);
    keyboardE7(key, x, y);
    keyboardF7(key, x, y);
    keyboardG7(key, x, y);
    keyboardH7(key, x, y);*/
}

/*void movimientotorreA1(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonA1PosX, 0.0);
    A1(x, y, z);
    glPopMatrix();
}

void movimientocaballoB1(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonB1PosX, 0.0);
    B1(x, y, z);
    glPopMatrix();
}

void movimientoalfilC1(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonC1PosX, 0.0);
    C1(x, y, z);
    glPopMatrix();
}

void movimientoreinaD1(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonD1PosX, 0.0);
    D1(x, y, z);
    glPopMatrix();
}

void movimientoreyE1(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonE1PosX, 0.0);
    E1(x, y, z);
    glPopMatrix();
}

void movimientoalfilF1(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonF1PosX, 0.0);
    F1(x, y, z);
    glPopMatrix();
}

void movimientocaballoG1(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonG1PosX, 0.0);
    G1(x, y, z);
    glPopMatrix();
}

void movimientotorreH1(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonH1PosX, 0.0);
    H1(x, y, z);
    glPopMatrix();
}*/


void movimientopeonA2(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonA2PosX, 0.0);
    A2(x, y, z);

    glPopMatrix();
}

void movimientopeonB2(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonB2PosX, 0.0);
    B2(x, y, z);
    glPopMatrix();
}

/*void movimientopeonC2(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonC2PosX, 0.0);
    C2(x, y, z);

    glPopMatrix();
}

void movimientopeonD2(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonD2PosX, 0.0);
    D2(x, y, z);

    glPopMatrix();
}

void movimientopeonE2(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonE2PosX, 0.0);
    E2(x, y, z);

    glPopMatrix();
}

void movimientopeonF2(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonF2PosX, 0.0);
    A2(x, y, z);

    glPopMatrix();
}

void movimientopeonG2(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonG2PosX, 0.0);
    A2(x, y, z);

    glPopMatrix();
}

void movimientopeonH2(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonH2PosX, 0.0);
    A2(x, y, z);

    glPopMatrix();
}

void movimientopeonA7(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonA7PosX, 0.0);
    A2(x, y, z);

    glPopMatrix();
}

void movimientopeonB7(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonB7PosX, 0.0);
    B2(x, y, z);
    glPopMatrix();
}

void movimientopeonC7(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonC7PosX, 0.0);
    C2(x, y, z);

    glPopMatrix();
}

void movimientopeonD7(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonD7PosX, 0.0);
    D2(x, y, z);

    glPopMatrix();
}

void movimientopeonE7(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonE7PosX, 0.0);
    E2(x, y, z);

    glPopMatrix();
}

void movimientopeonF7(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonF7PosX, 0.0);
    A2(x, y, z);

    glPopMatrix();
}

void movimientopeonG7(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonG7PosX, 0.0);
    A2(x, y, z);

    glPopMatrix();
}

void movimientopeonH7(){
	glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonH7PosX, 0.0);
    A2(x, y, z);

    glPopMatrix();
}

void movimientotorreA8(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonA8PosX, 0.0);
    A8(x, y, z);
    glPopMatrix();
}

void movimientocaballoB8(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonB8PosX, 0.0);
    B8(x, y, z);
    glPopMatrix();
}

void movimientoalfilC8(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonC8PosX, 0.0);
    C8(x, y, z);
    glPopMatrix();
}

void movimientoreinaD8(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonD8PosX, 0.0);
    D8(x, y, z);
    glPopMatrix();
}

void movimientoreyE8(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonE8PosX, 0.0);
    E8(x, y, z);
    glPopMatrix();
}

void movimientoalfilF8(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonF8PosX, 0.0);
    F8(x, y, z);
    glPopMatrix();
}

void movimientocaballoG8(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonG8PosX, 0.0);
    G8(x, y, z);
    glPopMatrix();
}

void movimientotorreH8(){
    glClear(GL_COLOR_BUFFER_BIT);
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    glTranslatef(0.0, peonH8PosX, 0.0);
    H8(x, y, z);
    glPopMatrix();
}*/

void display_ajedrez(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.87f, 0.72f, 0.53f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();  // Reset the modelview matrix
    gluLookAt(-5.0, -5.0, -20.0, 0.0, 1.0, 0.0, 2.0, 2.0, 0.0);
    /*movimientotorreA1();
    movimientocaballoB1();
    movimientoalfilC1();
    movimientoreinaD1();
	movimientoreyE1();
	movimientoalfilF1();
	movimientocaballoG1();
	movimientotorreH1();*/

    movimientopeonA2();
    movimientopeonB2();
    /*movimientopeonC2();
	movimientopeonD2();
	movimientopeonE2();
	movimientopeonF2();
	movimientopeonG2();
	movimientopeonH2();

	movimientopeonA7();
	movimientopeonB7();
	movimientopeonC7();
	movimientopeonD7();
	movimientopeonE7();
	movimientopeonF7();
	movimientopeonG7();
	movimientopeonH7();

	movimientotorreA8();
	movimientocaballoB8();
	movimientoalfilC8();
	movimientreinaD8();
	movimientoreyE8();
	movimientopeonalfilF8();
	movimientocaballoG8();
	movimientotorreH8();*/

	dibujar_tablero();
	
    glutSwapBuffers();
}

void reshape2(int width, int height) {
    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-10.0, -10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

static void keyboard2(unsigned char key, int x, int y) {
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

static float velocidad=0.0;

static int superior[3][3]={{0,0,0},{0,0,0},{0,0,0}}, 
derecha[3][3]={{1,1,1},{1,1,1},{1,1,1}}, 
frente[3][3]={{2,2,2},{2,2,2},{2,2,2}}, 
trasero[3][3]={{3,3,3},{3,3,3},{3,3,3}}, 
abajo[3][3]={{4,4,4},{4,4,4},{4,4,4}}, 
izquierda[3][3]={{5,5,5},{5,5,5},{5,5,5}}, 
temp[3][3]; 
 
int registro[300]; 
int contar=0;  
static int rotacion=0; 
int rotacion_completa=0; 
static GLfloat theta=0.0; 
static GLfloat p=0.0,q=0.0,r=0.0; 
static GLint inverso=0;  
int iniciox=0,inicioy=0; 
int movimiento=0; 

 
GLfloat vertices[][3]={{-1.0,-1.0,-1.0}, 
 
                       {1.0,-1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, //center 
                       {-1.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                        
                       {-1.0,-3.0,-1.0}, 
                       {1.0,-3.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0},  //bottom center 
                       {-1.0,-3.0,1.0}, 
                       {1.0,-3.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                        
                       {-3.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-3.0,1.0,-1.0},  //left center 
                       {-3.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-3.0,1.0,1.0}, 

                       {1.0,-1.0,-1.0}, 
                       {3.0,-1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, // right center 
                       {1.0,-1.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, 
 
                       {-1.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {1.0,3.0,-1.0}, 
                       {-1.0,3.0,-1.0}, // top center 
                       {-1.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {1.0,3.0,1.0}, 
                       {-1.0,3.0,1.0}, 
 
                       {-1.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, //front center 

                       {-1.0,-1.0,3.0}, 
                       {1.0,-1.0,3.0}, 
                       {1.0,1.0,3.0}, 
                       {-1.0,1.0,3.0}, 
 
                       {-1.0,-1.0,-3.0}, 
                       {1.0,-1.0,-3.0}, 
                       {1.0,1.0,-3.0}, 
                       {-1.0,1.0,-3.0}, //back center 
                       {-1.0,-1.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
 
                       {-3.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-1.0,3.0,-1.0}, 
                       {-3.0,3.0,-1.0}, // top left center 
                       {-3.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-1.0,3.0,1.0}, 
                       {-3.0,3.0,1.0},  
                             
                       {1.0,1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 

                       {3.0,3.0,-1.0}, 
                       {1.0,3.0,-1.0}, // top right  center 
                       {1.0,1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {3.0,3.0,1.0}, 
                       {1.0,3.0,1.0}, 
 
                       {-1.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {1.0,3.0,1.0}, 
                       {-1.0,3.0,1.0}, // top front center 
                       {-1.0,1.0,3.0}, 
                       {1.0,1.0,3.0}, 
                       {1.0,3.0,3.0}, 
                       {-1.0,3.0,3.0}, 
 
                       {-1.0,1.0,-3.0}, 
                       {1.0,1.0,-3.0}, 
                       {1.0,3.0,-3.0}, 
                       {-1.0,3.0,-3.0}, // top back center 
                       {-1.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {1.0,3.0,-1.0}, 
                       {-1.0,3.0,-1.0}, 

        {-3.0,-3.0,-1.0}, 
                       {-1.0,-3.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-3.0,-1.0,-1.0},  //bottom left center 
                       {-3.0,-3.0,1.0}, 
                       {-1.0,-3.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                       {-3.0,-1.0,1.0}, 
 
        {1.0,-3.0,-1.0}, 
                       {3.0,-3.0,-1.0}, 
                       {3.0,-1.0,-1.0}, 
                       {1.0,-1.0,-1.0},  //bottom  right center 
                       {1.0,-3.0,1.0}, 
                       {3.0,-3.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0}, 
            
        {-1.0,-3.0,1.0}, 
                       {1.0,-3.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0},  //bottom front center 

                       {-1.0,-3.0,3.0}, 
                       {1.0,-3.0,3.0}, 
                       {1.0,-1.0,3.0}, 
                       {-1.0,-1.0,3.0}, 
 
                       {-1.0,-3.0,-3.0}, 
                       {1.0,-3.0,-3.0}, 
                       {1.0,-1.0,-3.0}, 
                       {-1.0,-1.0,-3.0},  //bottom back center 
                       {-1.0,-3.0,-1.0}, 
                       {1.0,-3.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
 
        {-3.0,1.0,-3.0}, 
                       {-1.0,1.0,-3.0}, 
                       {-1.0,3.0,-3.0}, 
                       {-3.0,3.0,-3.0}, // top left back 
                       {-3.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-1.0,3.0,-1.0}, 
                       {-3.0,3.0,-1.0}, 
 
        {-3.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-1.0,3.0,1.0}, 
                       {-3.0,3.0,1.0}, // top left front 
                       {-3.0,1.0,3.0}, 
                       {-1.0,1.0,3.0}, 
                       {-1.0,3.0,3.0}, 
                       {-3.0,3.0,3.0}, 
 
        {1.0,1.0,-3.0}, 
                       {3.0,1.0,-3.0}, 
                       {3.0,3.0,-3.0}, 
                       {1.0,3.0,-3.0}, // top right  back 
                       {1.0,1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 
                       {3.0,3.0,-1.0}, 
                       {1.0,3.0,-1.0}, 
 
        {1.0,1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {3.0,3.0,1.0}, 
                       {1.0,3.0,1.0}, // top right  front 
                       {1.0,1.0,3.0}, 
                       {3.0,1.0,3.0}, 
                       {3.0,3.0,3.0}, 

                       {1.0,3.0,3.0}, 
 
        {-3.0,-1.0,-3.0}, 
                       {-1.0,-1.0,-3.0}, 
                       {-1.0,1.0,-3.0}, 
                       {-3.0,1.0,-3.0},  //ceneter left back 
                       {-3.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-3.0,1.0,-1.0}, 
 
        {-3.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-3.0,1.0,1.0},  //center left front 
                       {-3.0,-1.0,3.0}, 
                       {-1.0,-1.0,3.0}, 
                       {-1.0,1.0,3.0}, 
                       {-3.0,1.0,3.0}, 
 
        {1.0,-1.0,-3.0}, 
                       {3.0,-1.0,-3.0}, 
                       {3.0,1.0,-3.0}, 
                       {1.0,1.0,-3.0}, // center right back 
                       {1.0,-1.0,-1.0}, 

                       {3.0,-1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
 
        {1.0,-1.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, // center right front 
                       {1.0,-1.0,3.0}, 
                       {3.0,-1.0,3.0}, 
                       {3.0,1.0,3.0}, 
                       {1.0,1.0,3.0}, 
 
        {-3.0,-3.0,-3.0}, 
                       {-1.0,-3.0,-3.0}, 
                       {-1.0,-1.0,-3.0}, 
                       {-3.0,-1.0,-3.0},  //bottom left back 
                       {-3.0,-3.0,-1.0}, 
                       {-1.0,-3.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-3.0,-1.0,-1.0}, 
 
        {-3.0,-3.0,1.0}, 
                       {-1.0,-3.0,1.0}, 
                       {-1.0,-1.0,1.0}, 

                       {-3.0,-1.0,1.0},  //bottom left front 
                       {-3.0,-3.0,3.0}, 
                       {-1.0,-3.0,3.0}, 
                       {-1.0,-1.0,3.0}, 
                       {-3.0,-1.0,3.0}, 
 
        {1.0,-3.0,-3.0}, 
                       {3.0,-3.0,-3.0}, 
                       {3.0,-1.0,-3.0}, 
                       {1.0,-1.0,-3.0},  //bottom  right back 
                       {1.0,-3.0,-1.0}, 
                       {3.0,-3.0,-1.0}, 
                       {3.0,-1.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
            
        {1.0,-3.0,1.0}, 
                       {3.0,-3.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0},  //bottom  right front 
                       {1.0,-3.0,3.0}, 
                       {3.0,-3.0,3.0}, 
                       {3.0,-1.0,3.0}, 
                       {1.0,-1.0,3.0}, 
        {0.0,7.0,0.0}, 
        {0.0,7.5,0.0}, 
        {0.5,7.5,0.0}, //speed meter 
        {0.5,7.0,0.0}
}; 
                      
GLfloat color[][3]={{194.0 / 255.0, 178.0 / 255.0, 128.0 / 255.0}, //amarillo. 
                    {250.0 / 255.0, 128.0 / 255.0, 114.0 / 255.0},  //verde claro 
                    {0.956863, 0.643137, 0.376471},  //lila
                    {255.0 / 255.0, 204.0 / 255.0, 153.0 / 255.0},  //naranja claro
                    {127.0 / 255.0, 1.0, 212.0 / 255.0},  //agumarina
                    {219.0 / 255.0, 48.0 / 255.0, 122.0 / 255.0}, //rosa mexicano. 
		{0.0,0.0,0.0}, //grey used to represent faces of cube without colour 
};


void contornito(int a,int b,int c,int d,int e) {    
	glColor3f(1.0, 1.0, 1.0); 
	glLineWidth(5.0); 
	glBegin(GL_LINE_LOOP); 
	glVertex3fv(vertices[b]); 
	glVertex3fv(vertices[c]); 
	glVertex3fv(vertices[d]); 
	glVertex3fv(vertices[e]); 
	glEnd(); 

	glColor3fv(color[a]); 
	glBegin(GL_POLYGON); 
	glVertex3fv(vertices[b]); 
	glVertex3fv(vertices[c]); 
	glVertex3fv(vertices[d]); 
	glVertex3fv(vertices[e]); 
	glEnd(); 
} 

void contornocubo1() { 
	contornito(6,0,3,2,1);  
	contornito(6,2,3,7,6);  
	contornito(6,0,4,7,3);    
	contornito(6,1,2,6,5);            
	contornito(6,4,5,6,7); 
	contornito(6,0,1,5,4);  
}
 
void contornocubo2() { 
	contornito(6,8,11,10,9);  
	contornito(6,10,11,15,14);  
	contornito(6,8,12,15,11);   
	contornito(6,9,10,14,13);            
	contornito(6,12,13,14,15); 
	contornito(abajo[1][1],8,9,13,12);  
} 
 
void contornocubo3() { 
	contornito(6,16,19,18,17);  
	contornito(6,18,19,23,22);  
	contornito(izquierda[1][1],16,20,23,19);    
	contornito(6,17,18,22,21);            
	contornito(6,20,21,22,23); 
	contornito(6,16,17,21,20);  
} 
 
void contornocubo4() { 
	contornito(6,24,27,26,25);  
	contornito(6,26,27,31,30);  
	contornito(6,24,28,31,27);    
	contornito(derecha[1][1],25,26,30,29);            
	contornito(6,28,29,30,31); 
	contornito(6,24,25,29,28);  
} 
 
void contornocubo5() { 
	contornito(6,32,35,34,33);  
	contornito(superior[1][1],34,35,39,38);  
	contornito(6,32,36,39,35);    
	contornito(6,33,34,38,37);            
	contornito(6,36,37,38,39); 
	contornito(6,32,33,37,36);  
} 
 
void contornocubo6() { 
	contornito(6,40,43,42,41);  
	contornito(6,42,43,47,46);  
	contornito(6,40,44,47,43);   
	contornito(6,41,42,46,45);            
	contornito(frente[1][1],44,45,46,47); 
	contornito(6,40,41,45,44);  
} 
 
void contornocubo7() { 
	contornito(trasero[1][1],48,51,50,49);  
	contornito(6,50,51,55,54);  
	contornito(6,48,52,55,51);   
	contornito(6,49,50,54,53);            
	contornito(6,52,53,54,55); 
	contornito(6,48,49,53,52);  
} 

void contornocubo8() { 
	contornito(6,56,59,58,57);  
	contornito(superior[1][0],58,59,63,62);  
	contornito(izquierda[0][1],56,60,63,59);    
	contornito(6,57,58,62,61);            
	contornito(6,60,61,62,63); 
	contornito(6,56,57,61,60);  
} 

void contornocubo9() { 
	contornito(6,64,67,66,65);  
	contornito(superior[1][2],66,67,71,70);  
	contornito(6,64,68,71,67);   
	contornito(derecha[0][1],65,66,70,69);            
	contornito(6,68,69,70,71); 
	contornito(6,64,65,69,68);  
} 
 
void contornocubo10() { 
    contornito(6, 72, 75, 74, 73);  
    contornito(superior[2][1], 74, 75, 79, 78);  
    contornito(6, 72, 76, 79, 75);    
    contornito(6, 73, 74, 78, 77);            
    contornito(frente[0][1], 76, 77, 78, 79); 
    contornito(6, 72, 73, 77, 76);  
} 

void contornocubo11() { 
    contornito(trasero[0][1], 80, 83, 82, 81);  
    contornito(superior[0][1], 82, 83, 87, 86);  
    contornito(6, 80, 84, 87, 83);    
    contornito(6, 81, 82, 86, 85);            
    contornito(6, 84, 85, 86, 87); 
    contornito(6, 80, 81, 85, 84);  
} 

void contornocubo12() { 
    contornito(6, 80 + 8, 83 + 8, 82 + 8, 81 + 8);  
    contornito(6, 82 + 8, 83 + 8, 87 + 8, 86 + 8);  
    contornito(izquierda[2][1], 80 + 8, 84 + 8, 87 + 8, 83 + 8);    
    contornito(6, 81 + 8, 82 + 8, 86 + 8, 85 + 8);            
    contornito(6, 84 + 8, 85 + 8, 86 + 8, 87 + 8); 
    contornito(abajo[1][0], 80 + 8, 81 + 8, 85 + 8, 84 + 8);  
} 

void contornocubo13() { 
    contornito(6, 80 + 16, 83 + 16, 82 + 16, 81 + 16);  
    contornito(6, 82 + 16, 83 + 16, 87 + 16, 86 + 16);  
    contornito(6, 80 + 16, 84 + 16, 87 + 16, 83 + 16);    
    contornito(derecha[2][1], 81 + 16, 82 + 16, 86 + 16, 85 + 16);            
    contornito(6, 84 + 16, 85 + 16, 86 + 16, 87 + 16); 
    contornito(abajo[1][2], 80 + 16, 81 + 16, 85 + 16, 84 + 16);  
} 

void contornocubo14() { 
    contornito(6, 80 + 24, 83 + 24, 82 + 24, 81 + 24);  
    contornito(6, 82 + 24, 83 + 24, 87 + 24, 86 + 24);  
    contornito(6, 80 + 24, 84 + 24, 87 + 24, 83 + 24);   
    contornito(6, 81 + 24, 82 + 24, 86 + 24, 85 + 24);            
    contornito(frente[2][1], 84 + 24, 85 + 24, 86 + 24, 87 + 24); 
    contornito(abajo[0][1], 80 + 24, 81 + 24, 85 + 24, 84 + 24);  
} 

void contornocubo15() { 
    contornito(trasero[2][1], 112, 115, 114, 113);  
    contornito(6, 114, 115, 119, 118);  
    contornito(6, 112, 116, 119, 115);   
    contornito(6, 113, 114, 118, 117);            
    contornito(6, 116, 117, 118, 119); 
    contornito(abajo[2][1], 112, 113, 117, 116);  
} 

void contornocubo16() { 
    contornito(trasero[0][2], 120, 123, 122, 121);  
    contornito(superior[0][0], 122, 123, 127, 126);  
    contornito(izquierda[0][0], 120, 124, 127, 123);    
    contornito(6, 121, 122, 126, 125);            
    contornito(6, 124, 125, 126, 127); 
    contornito(6, 120, 121, 125, 124);  
} 

void contornocubo17() { 
    contornito(6, 128, 131, 130, 129);  
    contornito(superior[2][0], 130, 131, 135, 134);  
    contornito(izquierda[0][2], 128, 132, 135, 131);    
    contornito(6, 129, 130, 134, 133);            
    contornito(frente[0][0], 132, 133, 134, 135); 
    contornito(6, 128, 129, 133, 132);  
} 

void contornocubo18() { 
    contornito(trasero[0][0], 136, 139, 138, 137);  
    contornito(superior[0][2], 138, 139, 143, 142);  
    contornito(6, 136, 140, 143, 139);    
    contornito(derecha[0][2], 137, 138, 142, 141);            
    contornito(6, 140, 141, 142, 143); 
    contornito(6, 136, 137, 141, 140);  
} 

void contornocubo19() { 
    contornito(6, 144, 147, 146, 145);  
    contornito(superior[2][2], 146, 147, 151, 150);  
    contornito(6, 144, 148, 151, 147);    
    contornito(derecha[0][0], 145, 146, 150, 149);            
    contornito(frente[0][2], 148, 149, 150, 151); 
    contornito(6, 144, 145, 149, 148);  
} 

void contornocubo20() { 
    contornito(trasero[1][2], 152, 155, 154, 153);  
    contornito(6, 154, 155, 159, 158);  
    contornito(izquierda[1][0], 152, 156, 159, 155);  
    contornito(6, 153, 154, 158, 157);            
    contornito(6, 156, 157, 158, 159); 
    contornito(6, 152, 153, 157, 156);  
} 

void contornocubo21() { 
    contornito(6, 160, 163, 162, 161);  
    contornito(6, 162, 163, 167, 166);  
    contornito(izquierda[1][2], 160, 164, 167, 163);     
    contornito(6, 161, 162, 166, 165);            
    contornito(frente[1][0], 164, 165, 166, 167); 
    contornito(6, 160, 161, 165, 164);  
} 

void contornocubo22() { 
    contornito(trasero[1][0], 168, 171, 170, 169);  
    contornito(6, 170, 171, 175, 174);  
    contornito(6, 168, 172, 175, 171); 
    contornito(derecha[1][2], 169, 170, 174, 173);            
    contornito(6, 172, 173, 174, 175); 
    contornito(6, 168, 169, 173, 172);  
} 

void contornocubo23() { 
    contornito(6, 176, 179, 178, 177);  
    contornito(6, 178, 179, 183, 182);  
    contornito(6, 176, 180, 183, 179);    
    contornito(derecha[1][0], 177, 178, 182, 181);            
    contornito(frente[1][2], 180, 181, 182, 183); 
    contornito(6, 176, 177, 181, 180);  
} 

void contornocubo24() { 
    contornito(trasero[2][2], 184, 187, 186, 185);  
    contornito(6, 186, 187, 191, 190);  
    contornito(izquierda[2][0], 184, 188, 191, 187);    
    contornito(6, 185, 186, 190, 189);            
    contornito(6, 188, 189, 190, 191); 
    contornito(abajo[2][0], 184, 185, 189, 188);  
} 

void contornocubo25() { 
    contornito(6, 192, 195, 194, 193);  
    contornito(6, 194, 195, 199, 198);  
    contornito(izquierda[2][2], 192, 196, 199, 195);    
    contornito(6, 193, 194, 198, 197);            
    contornito(frente[2][0], 196, 197, 198, 199); 
    contornito(abajo[0][0], 192, 193, 197, 196);  
} 

void contornocubo26() { 
    contornito(trasero[2][0], 200, 203, 202, 201);  
    contornito(6, 202, 203, 207, 206);  
    contornito(6, 200, 204, 207, 203);   
    contornito(derecha[2][2], 201, 202, 206, 205);            
    contornito(6, 204, 205, 206, 207); 
    contornito(abajo[2][2], 200, 201, 205, 204);  
}

void contornocubo27() { 
    contornito(6, 208, 211, 210, 209);  
    contornito(6, 210, 211, 215, 214);  
    contornito(6, 208, 212, 215, 211);    
    contornito(derecha[2][0], 209, 210, 214, 213);            
    contornito(frente[2][2], 212, 213, 214, 215); 
    contornito(abajo[0][2], 208, 209, 213, 212);  
}


void display() { 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity(); 
	glColor3fv(color[0]); 
	glPushMatrix();
	glRotatef(25.0+p,1.0,0.0,0.0); 
	glRotatef(-30.0+q,0.0,1.0,0.0); 
	glRotatef(0.0+r,0.0,0.0,1.0);  

    if(rotacion == 0) {  
        contornocubo1(); 
        contornocubo2(); 
        contornocubo3(); 
        contornocubo4(); 
        contornocubo5(); 
        contornocubo6(); 
        contornocubo7(); 
        contornocubo8();  
        contornocubo9(); 
        contornocubo10(); 
        contornocubo11(); 
        contornocubo12(); 
        contornocubo13(); 
        contornocubo14(); 
        contornocubo15(); 
        contornocubo16(); 
        contornocubo17(); 
        contornocubo18(); 
        contornocubo19(); 
        contornocubo20(); 
        contornocubo21(); 
        contornocubo22(); 
        contornocubo23(); 
        contornocubo24(); 
        contornocubo25(); 
        contornocubo26(); 
        contornocubo27(); 
    }

    if (rotacion == 1) { 
        contornocubo1(); 
        contornocubo2(); 
        contornocubo3(); 
        contornocubo4(); 
        contornocubo6(); 
        contornocubo7(); 
        contornocubo12(); 
        contornocubo13(); 
        contornocubo14(); 
        contornocubo15(); 
        contornocubo20(); 
        contornocubo21(); 
        contornocubo22(); 
        contornocubo23(); 
        contornocubo24(); 
        contornocubo25(); 
        contornocubo26(); 
        contornocubo27(); 
    if (inverso == 0) {
        glRotatef(-theta, 0.0, 1.0, 0.0); 
    } 
    else { 
        glRotatef(theta, 0.0, 1.0, 0.0); 
    } 

        contornocubo5(); 
        contornocubo8();  
        contornocubo9(); 
        contornocubo10(); 
        contornocubo11(); 
        contornocubo16(); 
        contornocubo17(); 
        contornocubo18(); 
        contornocubo19(); 
    }

    if(rotacion==2) {  
        contornocubo1(); 
        contornocubo2(); 
        contornocubo3(); 
        contornocubo5(); 
        contornocubo6(); 
        contornocubo7(); 
        contornocubo8();  
        contornocubo10(); 
        contornocubo11(); 
        contornocubo12(); 
        contornocubo14(); 
        contornocubo15(); 
        contornocubo16(); 
        contornocubo17(); 
        contornocubo20(); 
        contornocubo21(); 
        contornocubo24(); 
        contornocubo25(); 
        if(inverso==0) { 
            glRotatef(-theta,1.0,0.0,0.0); 
        } 
        else {
            glRotatef(theta,1.0,0.0,0.0); 
        } 
        contornocubo4(); 
        contornocubo9(); 
        contornocubo13(); 
        contornocubo18(); 
        contornocubo19(); 
        contornocubo22(); 
        contornocubo23(); 
        contornocubo26(); 
        contornocubo27(); 
    } 
    if(rotacion==3) { 
        contornocubo1(); 
        contornocubo2(); 
        contornocubo3(); 
        contornocubo4(); 
        contornocubo5(); 
        contornocubo7(); 
        contornocubo8();  
        contornocubo9(); 
        contornocubo11(); 
        contornocubo12(); 
        contornocubo13(); 
        contornocubo15(); 
        contornocubo16(); 
        contornocubo18(); 
        contornocubo20(); 
        contornocubo22(); 
        contornocubo24(); 
        contornocubo26(); 
        if(inverso==0) { 
            glRotatef(-theta,0.0,0.0,1.0); 
        } 
        else { 
            glRotatef(theta,0.0,0.0,1.0); 
        } 
        contornocubo6(); 
        contornocubo10(); 
        contornocubo14(); 
        contornocubo17(); 
        contornocubo19(); 
        contornocubo21(); 
        contornocubo23(); 
        contornocubo25(); 
        contornocubo27(); 
    } 
    if(rotacion==4) {  
        contornocubo1(); 
        contornocubo2(); 
        contornocubo4(); 
        contornocubo5(); 
        contornocubo6(); 
        contornocubo7(); 
        contornocubo9(); 
        contornocubo10(); 
        contornocubo11(); 
        contornocubo13(); 
        contornocubo14(); 
        contornocubo15(); 
        contornocubo18(); 
        contornocubo19(); 
        contornocubo22(); 
        contornocubo23(); 
        contornocubo26(); 
        contornocubo27(); 
        if(inverso==0) {
            glRotatef(theta,1.0,0.0,0.0); 
        } 
        else {
            glRotatef(-theta,1.0,0.0,0.0); 
        } 
        contornocubo3(); 
        contornocubo8();  
        contornocubo12(); 
        contornocubo16(); 
        contornocubo17(); 
        contornocubo20(); 
        contornocubo21(); 
        contornocubo24(); 
        contornocubo25(); 
    }


    if(rotacion==5) {  
        contornocubo1(); 
        contornocubo2(); 
        contornocubo3(); 
        contornocubo4(); 
        contornocubo5(); 
        contornocubo6(); 
        contornocubo8();  
        contornocubo9(); 
        contornocubo10(); 
        contornocubo12(); 
        contornocubo13(); 
        contornocubo14(); 
        contornocubo17(); 
        contornocubo19(); 
        contornocubo21(); 
        contornocubo23(); 
        contornocubo25(); 
        contornocubo27(); 
        if(inverso==0) {
            glRotatef(theta,0.0,0.0,1.0); 
        } 
        else { 
            glRotatef(-theta,0.0,0.0,1.0); 
        } 
        contornocubo7(); 
        contornocubo11(); 
        contornocubo15(); 
        contornocubo16(); 
        contornocubo18(); 
        contornocubo20(); 
        contornocubo22(); 
        contornocubo24(); 
        contornocubo26(); 
    } 
    if(rotacion==6) {  
        contornocubo1(); 
        contornocubo3(); 
        contornocubo4(); 
        contornocubo5(); 
        contornocubo6(); 
        contornocubo7(); 
        contornocubo8();  
        contornocubo9(); 
        contornocubo10(); 
        contornocubo11(); 
        contornocubo16(); 
        contornocubo17(); 
        contornocubo18(); 
        contornocubo19(); 
        contornocubo20(); 
        contornocubo21(); 
        contornocubo22(); 
        contornocubo23(); 
        if(inverso==0) {

            glRotatef(theta,0.0,1.0,0.0); 
        } 
        else {
            glRotatef(-theta,0.0,1.0,0.0); 
        } 
        contornocubo2(); 
        contornocubo12(); 
        contornocubo13(); 
        contornocubo14(); 
        contornocubo15(); 
        contornocubo24(); 
        contornocubo25(); 
        contornocubo26(); 
        contornocubo27(); 
    }
     
    glPopMatrix(); 
    glPushMatrix(); 
    glTranslatef(-.5,-4,0); 
    glScalef(velocidad/4.5,1.0,1.0); 
    glTranslatef(0.5,4,0); 
    contornito(5,216,217,218,219); 
    glPopMatrix(); 
    glFlush(); 
    glutSwapBuffers(); 
}



void transponer(char a) {  
    if(a == 'r' || a == 'R') { 
        int temp; 
        temp = derecha[0][0]; 
        derecha[0][0] = derecha[2][0]; 
        derecha[2][0] = derecha[2][2]; 
        derecha[2][2] = derecha[0][2]; 
        derecha[0][2] = temp; 
        temp = derecha[1][0]; 
        derecha[1][0] = derecha[2][1]; 
        derecha[2][1] = derecha[1][2]; 
        derecha[1][2] = derecha[0][1]; 
        derecha[0][1] = temp;  
    } 

    if(a=='t' || a == 'T') { 
        int temp; 
        temp=superior[0][0]; 
        superior[0][0]=superior[2][0]; 
        superior[2][0]=superior[2][2]; 
        superior[2][2]=superior[0][2]; 
        superior[0][2]=temp; 
        temp=superior[1][0]; 
        superior[1][0]=superior[2][1]; 
        superior[2][1]=superior[1][2]; 
        superior[1][2]=superior[0][1]; 
        superior[0][1]=temp; 
    } 
    if(a=='f' || a == 'F') { 
        int temp; 
        temp=frente[0][0]; 
        frente[0][0]=frente[2][0]; 
        frente[2][0]=frente[2][2]; 
        frente[2][2]=frente[0][2]; 
        frente[0][2]=temp; 
        temp=frente[1][0]; 
        frente[1][0]=frente[2][1]; 
        frente[2][1]=frente[1][2]; 
        frente[1][2]=frente[0][1]; 
        frente[0][1]=temp; 
    } 
    if(a=='l' || a ==  'L') { 
        int temp; 
        temp=izquierda[0][0]; 
        izquierda[0][0]=izquierda[2][0]; 
        izquierda[2][0]=izquierda[2][2]; 
        izquierda[2][2]=izquierda[0][2]; 
        izquierda[0][2]=temp; 
        temp=izquierda[1][0]; 
        izquierda[1][0]=izquierda[2][1]; 
        izquierda[2][1]=izquierda[1][2]; 
        izquierda[1][2]=izquierda[0][1]; 
        izquierda[0][1]=temp; 
    } 
    if(a=='k' || a ==  'K') { 
        int temp; 
        temp=trasero[0][0]; 
        trasero[0][0]=trasero[2][0]; 
        trasero[2][0]=trasero[2][2]; 
        trasero[2][2]=trasero[0][2]; 
        trasero[0][2]=temp; 
        temp=trasero[1][0]; 
        trasero[1][0]=trasero[2][1]; 
        trasero[2][1]=trasero[1][2]; 
        trasero[1][2]=trasero[0][1]; 
        trasero[0][1]=temp; 
    } 
    if(a=='b' || a == 'B') { 
        int temp; 
        temp=abajo[0][0]; 
        abajo[0][0]=abajo[2][0]; 
        abajo[2][0]=abajo[2][2]; 
        abajo[2][2]=abajo[0][2]; 
        abajo[0][2]=temp; 
        temp=abajo[1][0]; 
        abajo[1][0]=abajo[2][1]; 
        abajo[2][1]=abajo[1][2]; 
        abajo[1][2]=abajo[0][1]; 
        abajo[0][1]=temp; 
    } 
}
 
 
  
void arribac() { 
	transponer('t' || 'T'); 
	int temp1=frente[0][0]; 
	int temp2=frente[0][1]; 
	int temp3=frente[0][2]; 

	frente[0][0]=derecha[0][0]; 
	frente[0][1]=derecha[0][1]; 
	frente[0][2]=derecha[0][2]; 
	 
	derecha[0][0]=trasero[0][0]; 
	derecha[0][1]=trasero[0][1]; 
	derecha[0][2]=trasero[0][2]; 
	 
	trasero[0][0]=izquierda[0][0]; 
	trasero[0][1]=izquierda[0][1]; 
	trasero[0][2]=izquierda[0][2]; 
	 
	izquierda[0][0]=temp1; 
	izquierda[0][1]=temp2; 
	izquierda[0][2]=temp3; 
} 
 
void frentec() { 
    transponer('f' || 'F'); 
    int temp1=izquierda[0][2]; 
    int temp2=izquierda[1][2]; 
    int temp3=izquierda[2][2]; 
     
    izquierda[0][2]=abajo[0][0]; 
    izquierda[1][2]=abajo[0][1]; 
    izquierda[2][2]=abajo[0][2]; 
     
    abajo[0][0]=derecha[2][0]; 
    abajo[0][1]=derecha[1][0]; 
    abajo[0][2]=derecha[0][0]; 
     
    derecha[2][0]=superior[2][2]; 
    derecha[1][0]=superior[2][1]; 
    derecha[0][0]=superior[2][0]; 
     
    superior[2][2]=temp1; 
    superior[2][1]=temp2; 
    superior[2][0]=temp3; 
}
 
 
void derechac() { 
	transponer('r' || 'R'); 
	int temp1=superior[0][2]; 
	int temp2=superior[1][2]; 
	int temp3=superior[2][2]; 
	 
	superior[0][2]=frente[0][2]; 
	superior[1][2]=frente[1][2]; 
	superior[2][2]=frente[2][2]; 
	 
	frente[0][2]=abajo[0][2]; 
	frente[1][2]=abajo[1][2]; 
	frente[2][2]=abajo[2][2]; 
	 
	abajo[0][2]=trasero[2][0]; 
	abajo[1][2]=trasero[1][0]; 
	abajo[2][2]=trasero[0][0]; 
	 
	trasero[2][0]=temp1; 
	trasero[1][0]=temp2; 
	trasero[0][0]=temp3; 
} 
 
void izquierdac() { 
	transponer('l' || 'L'); 
	int temp1=frente[0][0]; 
	int temp2=frente[1][0]; 
	int temp3=frente[2][0]; 
	 
	frente[0][0]=superior[0][0]; 
	frente[1][0]=superior[1][0]; 
	frente[2][0]=superior[2][0]; 

	superior[0][0]=trasero[2][2]; 
	superior[1][0]=trasero[1][2]; 
	superior[2][0]=trasero[0][2]; 
	 
	trasero[2][2]=abajo[0][0]; 
	trasero[1][2]=abajo[1][0]; 
	trasero[0][2]=abajo[2][0]; 

	abajo[0][0]=temp1; 
	abajo[1][0]=temp2; 
	abajo[2][0]=temp3;  
} 
 
void atrasc() { 
	transponer('k' || 'k'); 
	int temp1=superior[0][0]; 
	int temp2=superior[0][1]; 
	int temp3=superior[0][2]; 
	 
	superior[0][0]=derecha[0][2]; 
	superior[0][1]=derecha[1][2]; 
	superior[0][2]=derecha[2][2]; 
	 
	derecha[0][2]=abajo[2][2]; 
	derecha[1][2]=abajo[2][1]; 
	derecha[2][2]=abajo[2][0]; 

	abajo[2][2]=izquierda[2][0]; 
	abajo[2][1]=izquierda[1][0]; 
	abajo[2][0]=izquierda[0][0]; 

	izquierda[2][0]=temp1; 
	izquierda[1][0]=temp2; 
	izquierda[0][0]=temp3; 
} 
 
void abajoc() { 
	transponer('b' || 'B'); 
	int temp1=frente[2][0]; 
	int temp2=frente[2][1]; 
	int temp3=frente[2][2]; 

	frente[2][0]=izquierda[2][0]; 
	frente[2][1]=izquierda[2][1]; 
	frente[2][2]=izquierda[2][2]; 

	izquierda[2][0]=trasero[2][0]; 
	izquierda[2][1]=trasero[2][1]; 
	izquierda[2][2]=trasero[2][2]; 

	trasero[2][0]=derecha[2][0]; 
	trasero[2][1]=derecha[2][1]; 
	trasero[2][2]=derecha[2][2]; 

	derecha[2][0]=temp1; 
	derecha[2][1]=temp2; 
	derecha[2][2]=temp3; 
} 
 
 
void giro() {
	theta+=0.2+velocidad; 
	if(theta==360.0) 
		theta-=360.0; 
	if(theta>=90.0) { 
		rotacion_completa=1; 
		glutIdleFunc(NULL); 
		if(rotacion==1&&inverso==0) { 
			arribac(); 
		} 
		if(rotacion==1&&inverso==1) { 
			arribac(); 
			arribac(); 
			arribac(); 
		} 
		if(rotacion==2&&inverso==0) { 
			derechac(); 
		} 
		if(rotacion==2&&inverso==1) { 
			derechac(); 
			derechac(); 
			derechac(); 
		} 
		if(rotacion==3&&inverso==0) { 
			frentec(); 
		} 
		if(rotacion==3&&inverso==1) { 
			frentec(); 
			frentec(); 
			frentec(); 
		} 
		if(rotacion==4&&inverso==0) { 
			izquierdac(); 
		} 
		if(rotacion==4&&inverso==1) { 
			izquierdac(); 
			izquierdac(); 
			izquierdac(); 
		} 
		if(rotacion==5&&inverso==0) { 
			atrasc(); 
		} 
		if(rotacion==5&&inverso==1) { 
			atrasc(); 
			atrasc(); 
			atrasc(); 
		} 
		if(rotacion==6&&inverso==0) { 
			abajoc(); 
		} 
		if(rotacion==6&&inverso==1) { 
			abajoc(); 
			abajoc(); 
			abajoc(); 
		} 
		rotacion=0; 
		theta=0;  
	}  
	glutPostRedisplay(); 
} 
 
 
void mover(int x, int y) {
	if(movimiento) { 
		q=q + (x - iniciox); 
		iniciox = x; 
		p=p + (y - inicioy); 
		inicioy=y; 
		glutPostRedisplay(); 
	} 
} 
 
 
void mouse(int btn,int state,int x,int y) { 
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)  {      
	} 
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {  
		if(x>=0&&x<=2&&y>=7&&y<=9) 
		{    
		} 
		
		movimiento = 1; 
		iniciox = x; 
		inicioy=y; 
	}  
} 
 
 
static void keyboard(unsigned char key,int x,int y) { 
	if(((key=='a') || (key == 'A'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=1; 
		inverso=0; 
		registro[++contar]=1; 
		glutIdleFunc(giro); 
	} 
	if(((key=='q') || (key == 'Q'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=1; 
		inverso=1; 
		registro[++contar]=-1; 
		glutIdleFunc(giro); 
	} 
	if(((key=='s') || (key == 'S'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=2; 
		inverso=0; 
		registro[++contar]=2; 
		glutIdleFunc(giro); 
	} 
	if(((key=='w') || (key == 'W'))&&rotacion_completa==1) {
		rotacion_completa=0;
		rotacion=2; 
		inverso=1; 
		registro[++contar]=-2; 
		glutIdleFunc(giro); 
	} 
	if(((key=='d') || (key == 'D'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=3; 
		inverso=0; 
		registro[++contar]=3; 
		glutIdleFunc(giro); 
	} 
	if(((key=='e') || (key == 'E'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=3; 
		inverso=1; 
		registro[++contar]=-3; 
		glutIdleFunc(giro); 
	} 
	if(((key=='f') || (key == 'F'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=4; 
		inverso=0; 
		registro[++contar]=4; 
		glutIdleFunc(giro); 
	} 
	if(((key=='r') || (key == 'R'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=4; 
		inverso=1; 
		registro[++contar]=-4; 
		glutIdleFunc(giro); 
	} 
	if(((key=='g') || (key == 'G'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=5; 
		inverso=0; 
		registro[++contar]=5; 
		glutIdleFunc(giro); 
	} 
	if(((key=='t') || (key == 'T'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=5; 
		inverso=1; 
		registro[++contar]=-5; 
		glutIdleFunc(giro); 
	} 
	if(((key=='h') || (key == 'H'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=6; 
		inverso=0; 
		registro[++contar]=6; 
		glutIdleFunc(giro); 
	} 
	if(((key=='y') || (key == 'Y'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=6; 
		inverso=1; 
		registro[++contar]=-6; 
		glutIdleFunc(giro);  
	} 
} 
 

void myreshape(int w,int h) { 
	glViewport(0,0,w,h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	if (w <= h) 
		glOrtho(-10.0,10.0,-10.0*(GLfloat)h/(GLfloat)w, 10.0*(GLfloat)h/(GLfloat)w,-10.0,10.0); 
	else 
		glOrtho(-10.0*(GLfloat)w/(GLfloat)h, 10.0*(GLfloat)w/(GLfloat)h,-10.0,10.0,-10.0,10.0); 
	glMatrixMode(GL_MODELVIEW); 
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Ventana para piezas blancas.
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    piezablanca = glutCreateWindow("Piezas blancas");

    int piezasBlancasSubMenu = glutCreateMenu(menupiezasblancas);
    glutAddMenuEntry("Rey", 1);
    glutAddMenuEntry("Reina", 2);
    glutAddMenuEntry("Alfil", 3);
    glutAddMenuEntry("Caballo", 4);
    glutAddMenuEntry("Torre", 5);
    glutAddMenuEntry("Peon", 6);

    glutCreateMenu(menupiezasblancas);
    glutAddSubMenu("Piezas", piezasBlancasSubMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display_piezasblancas);
    glutReshapeFunc(reshape01);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(movimientos);

    //Ventana para piezas negras.
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(400, 400);
    piezanegra = glutCreateWindow("Piezas negras");

    int piezasNegrasSubMenu = glutCreateMenu(menupiezasnegras);
    glutAddMenuEntry("Rey", 7);
    glutAddMenuEntry("Reina", 8);
    glutAddMenuEntry("Alfil", 9);
    glutAddMenuEntry("Caballo", 10);
    glutAddMenuEntry("Torre", 11);
    glutAddMenuEntry("Peon", 12);

    glutCreateMenu(menupiezasnegras);
    glutAddSubMenu("Piezas", piezasNegrasSubMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display_piezasnegras);
    glutReshapeFunc(reshape01);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(movimientos);


    //Ventana para tablero
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    tablero = glutCreateWindow("Tablero.");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display_tablero);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard2);

    //Ventana para el tablero con piezas.
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    tableroconpiezas = glutCreateWindow("Tablero con piezas.");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display_tableroconpiezas);
    glutReshapeFunc(reshape2);
    glutKeyboardFunc(keyboard2);

    //Ventana para el ajedrez
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    ajedrez = glutCreateWindow("Ajedrez.");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display_ajedrez);
    glutReshapeFunc(reshape2);
    glutKeyboardFunc(keyboardtodos);

    //Ventana para el cubo RUBIK
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    cuborubik = glutCreateWindow("CUBO RUBIK.");
    glEnable(GL_DEPTH_TEST);
	glutReshapeFunc(myreshape); 
	glutIdleFunc(giro); 
	glutMouseFunc(mouse); 
	glutMotionFunc(mover); 
	glutAttachMenu(GLUT_RIGHT_BUTTON); 
	glutKeyboardFunc(keyboard); 
	glutDisplayFunc(display); 
	glEnable(GL_DEPTH_TEST); 


    glutMainLoop(); //iniciamos el bucle principal de GLUT.
    return 0;
}