#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
int piezablanca, piezanegra, tablero, tableroconpiezas, ajedrez;

//Estados del juego
typedef enum {
    MENU_INICIAL,
    SOLICITANDO_NOMBRE_BLANCO,
    SOLICITANDO_NOMBRE_NEGRO,
    JUGANDO_UNO_VS_UNO,
    JUGANDO_UNO_VS_IA
} EstadoJuego;

EstadoJuego estadoActual = MENU_INICIAL;

//Variables para nombres de jugadores
char nombreJugadorBlanco[50] = "";
char nombreJugadorNegro[50] = "";
char inputBuffer[50] = "";
int inputActivo = 0;
int inputIndex = 0;

//Variables para el zoom del tablero en modo juego
float zoomJuego = 12.0;

//Variables para la rotación de la cámara en modo juego
float rotacionCamaraX = 0.0;
float rotacionCamaraY = 0.0;

//Sistema de jugabilidad
typedef enum {
    VACIO = 0,
    PEON_BLANCO = 1,
    TORRE_BLANCA = 2,
    CABALLO_BLANCO = 3,
    ALFIL_BLANCO = 4,
    REINA_BLANCA = 5,
    REY_BLANCO = 6,
    PEON_NEGRO = -1,
    TORRE_NEGRA = -2,
    CABALLO_NEGRO = -3,
    ALFIL_NEGRO = -4,
    REINA_NEGRA = -5,
    REY_NEGRO = -6
} TipoPieza;

//Tablero 8x8: fila 0-7, columna 0-7 (0,0 es A1, 7,7 es H8)
TipoPieza tableroJuego[8][8];

//Turno actual: 1 = blancas, -1 = negras
int turnoActual = 1;

//Pieza seleccionada: -1 si no hay selección, sino (fila*8 + columna)
int piezaSeleccionada = -1;
int filaSeleccionada = -1;
int columnaSeleccionada = -1;

//Casillas válidas para movimiento (para dibujar en rojo)
int casillasValidas[8][8]; // 1 = válida, 0 = no válida

//Variables para la imagen de la pieza negra
unsigned char* imagenPiezaNegra = NULL;
int anchoImagen = 0, altoImagen = 0, canalesImagen = 0;
GLuint texturaPiezaNegra = 0;
int texturaCargada = 0;

//Variables para la imagen de la pieza blanca
unsigned char* imagenPiezaBlanca = NULL;
int anchoImagenBlanca = 0, altoImagenBlanca = 0, canalesImagenBlanca = 0;
GLuint texturaPiezaBlanca = 0;
int texturaBlancaCargada = 0;

//Declaración de variables globales para la rotacion de la camara en X, Y, Z.
float rotationAngleX = 0.0;
float rotationAngleY = 0.0;
float rotationAngleZ = 0.0;

//Variables para el control del mouse en las ventanas de ajedrez
int mouseTablero = 0;
int mouseTableroConPiezas = 0;
int mousePiezasBlancas = 0;
int mousePiezasNegras = 0;
int lastMouseXTablero = 0;
int lastMouseYTablero = 0;
int lastMouseXTableroConPiezas = 0;
int lastMouseYTableroConPiezas = 0;
int lastMouseXPiezasBlancas = 0;
int lastMouseYPiezasBlancas = 0;
int lastMouseXPiezasNegras = 0;
int lastMouseYPiezasNegras = 0;

//Variables para la distancia de la cámara en cada ventana (zoom)
float cameraDistanceTablero = 20.0;
float cameraDistanceTableroConPiezas = 20.0;
float cameraDistancePiezasBlancas = 5.0;
float cameraDistancePiezasNegras = 5.0;

//Variables de cámara separadas para piezas blancas y negras
float cameraXPiezasBlancas = 0.0;
float cameraYPiezasBlancas = 0.0;
float cameraZPiezasBlancas = 5.0;
float cameraXPiezasNegras = 0.0;
float cameraYPiezasNegras = 0.0;
float cameraZPiezasNegras = 5.0;

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
void inicializarTablero(void);
void calcularMovimientosValidos(int fila, int columna);
void texto_Rey();
void texto_Reina();
void texto_Alfil();
void texto_Caballo();
void texto_Torre();
void texto_Peon();
void dibujar_Rey_blanco();
void dibujar_Rey_negro();
void dibujar_Rey_gris();
void dibujar_Reina_blanca();
void dibujar_Reina_negra();
void dibujar_Reina_gris();
void dibujar_Alfil_blanco();
void dibujar_Alfil_negro();
void dibujar_Alfil_gris();
void dibujar_Caballo_blanco();
void dibujar_Caballo_negro();
void dibujar_Caballo_gris();
void dibujar_Torre_blanca();
void dibujar_Torre_negra();
void dibujar_Torre_gris();
void dibujar_Peon_blanco();
void dibujar_Peon_negro();
void dibujar_Peon_gris();
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

    glVertex3f(0.5, -0.5, 0.5); // Vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5);  // Vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); // Vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); // Vértice 4 de la cara posterior derecha inferior.

    glVertex3f(0.5, 0.5, 0.5); // Vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); // Vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); // Vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); // Vértice 4 de la cara posterior superior derecha.

    glVertex3f(-0.5, 0.5, 0.5); // Vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); // Vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); // Vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); // Vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
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

//Función que cambia de color gris la pieza del Rey.
void dibujar_Rey_gris(){
    glColor3f(0.5, 0.5, 0.5); //gris.
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
    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 3 y establece el color a blanco.
    pieza = 9;
    glColor3f(1.0, 1.0, 1.0); //blanco.
    dibujar_Reina();
}

//Función que cambia de color negro la pieza de la Reina.
void dibujar_Reina_negra(){

    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 3 y establece el color a negro.
    pieza = 9;
    glColor3f(0.0, 0.0, 0.0); //negro
    dibujar_Reina();
}

//Función que cambia de color gris la pieza de la Reina.
void dibujar_Reina_gris(){
    //Establece el índice actual.
    indice = indice02;
    //Define la pieza actual como 9 y establece el color a gris.
    pieza = 9;
    glColor3f(0.5, 0.5, 0.5); //gris.
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

    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 2 y establece el color a blanco.
    pieza = 2;
    glColor3f(1.0, 1.0, 1.0); //blanco.
    dibujar_Alfil();
}

//Función que cambia de color negro la pieza del Alfil.
void dibujar_Alfil_negro(){

    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 2 y establece el color a negro.
    pieza = 2;
    glColor3f(0.0, 0.0, 0.0); //negro.
    dibujar_Alfil();
}

//Función que cambia de color gris la pieza del Alfil.
void dibujar_Alfil_gris(){
    //Establece el índice actual.
    indice = indice02;
    //Define la pieza actual como 2 y establece el color a gris.
    pieza = 2;
    glColor3f(0.5, 0.5, 0.5); //gris.
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
    //Guardar el color actual antes de dibujar_fondo
    GLfloat colorActual[4];
    glGetFloatv(GL_CURRENT_COLOR, colorActual);
    
    dibujar_fondo();
    
    //Restaurar el color después de dibujar_fondo
    glColor3f(colorActual[0], colorActual[1], colorActual[2]);
    
    glPopMatrix();
}

//Función que cambia de color blanco la pieza del Caballo.
void dibujar_Caballo_blanco(){
	glRotatef(90, 0.0f, 1.0f, 0.0f);

    //Define la pieza actual como 3 y establece el color a blanco.
    pieza = 3;
    glColor3f(1.0, 1.0, 1.0); //blanco
    dibujar_Caballo();
}

//Función que cambia de color negro la pieza del Caballo.
void dibujar_Caballo_negro(){
	glRotatef(-90, 0.0f, 1.0f, 0.0f);

    //Define la pieza actual como 3 y establece el color a negro.
    pieza = 3;
    glColor3f(0.0, 0.0, 0.0); //negro.
    dibujar_Caballo();
}

//Función que cambia de color gris la pieza del Caballo.
void dibujar_Caballo_gris(){
	glRotatef(90, 0.0f, 1.0f, 0.0f);
    //Define la pieza actual como 3 y establece el color a gris.
    pieza = 3;
    glColor3f(0.5, 0.5, 0.5); //gris.
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

    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 4 y establece el color a blanco.
    indice = indice02;
    pieza = 4;
    glColor3f(1.0, 1.0, 1.0); //blanco.
    dibujar_Torre();
}

//Función que cambia de color negro la pieza de la Torre.
void dibujar_Torre_negra(){

    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 4 y establece el color a negro.
    indice = indice02;
    pieza = 4;
    glColor3f(0.0, 0.0, 0.0); //negro.
    dibujar_Torre();
}

//Función que cambia de color gris la pieza de la Torre.
void dibujar_Torre_gris(){
    //Establece el índice actual.
    indice = indice02;
    //Define la pieza actual como 4 y establece el color a gris.
    pieza = 4;
    glColor3f(0.5, 0.5, 0.5); //gris.
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
    //Guardar el color actual antes de dibujar_elipsoide
    GLfloat colorActual[4];
    glGetFloatv(GL_CURRENT_COLOR, colorActual);
    
    dibujar_elipsoide(0, 2 * M_PI, 0, M_PI / 2); //llama a la función dibujar_elipsoide para dibujar el elipsoide superior.
    
    //Restaurar el color después de dibujar_elipsoide
    glColor3f(colorActual[0], colorActual[1], colorActual[2]);
    
    glPopMatrix(); //restaura la matriz a la guardada previamente.
}

//Función que cambia de color blanco la pieza del Peón.
void dibujar_Peon_blanco(){

    //Establece el índice actual.
    indice = indice02;

    //Define la pieza actual como 1 y establece el color a blanco.
    pieza = 1;
    glColor3f(1.0, 1.0, 1.0); //blanco.
    dibujar_Peon();
}

//Función que cambia de color negro la pieza del Peón.
void dibujar_Peon_negro(){
    glColor3f(0.0, 0.0, 0.0); //negro.
    dibujar_Peon();
}

//Función que cambia de color gris la pieza del Peón.
void dibujar_Peon_gris(){
    //Establece el índice actual.
    indice = indice02;
    //Define la pieza actual como 1 y establece el color a gris.
    pieza = 1;
    glColor3f(0.5, 0.5, 0.5); //gris.
    dibujar_Peon();
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

void movimientitos(){
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //configura la matriz de vista para la cámara.
}


void movimientitosPiezasNegras(){
    gluLookAt(cameraXPiezasNegras, cameraYPiezasNegras, cameraZPiezasNegras, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //Aplicamos las traslaciones y rotaciones según las variables de posición y rotación.
    glTranslatef(eje_x, eje_y, eje_z);
    glRotatef(eje_x, 1.0, 0.0, 0.0);
    glRotatef(eje_y, 0.0, 1.0, 0.0);
    glRotatef(eje_z, 0.0, 0.0, 1.0);

    glRotatef(eje_w, 1.0, 0.0, 0.0);
    glRotatef(eje_a, 0.0, 1.0, 0.0);
    glRotatef(eje_d, 0.0, 0.0, 1.0);
}

void movimientitosPiezasBlancas(){
    gluLookAt(cameraXPiezasBlancas, cameraYPiezasBlancas, cameraZPiezasBlancas, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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
        movimientitosPiezasBlancas();
        texto_Rey();
        dibujar_Rey_blanco();
        break;
    case 2:
        movimientitosPiezasBlancas();
        texto_Reina();
        dibujar_Reina_blanca();
        break;
    case 3:
        movimientitosPiezasBlancas();
        texto_Alfil();
        dibujar_Alfil_blanco();
        break;
    case 4:
        movimientitosPiezasBlancas();
        texto_Caballo();
        dibujar_Caballo_blanco();
        break;
    case 5:
        movimientitosPiezasBlancas();
        texto_Torre();
        dibujar_Torre_blanca();
        break;
    case 6:
        movimientitosPiezasBlancas();
        texto_Peon();
        dibujar_Peon_blanco();
        break;
    }
    glFlush(); //forzamos el renderizado.
}

void piezas_negras(){
    switch (piezan) {
    case 7:
        movimientitosPiezasNegras();
        texto_Rey();
        dibujar_Rey_negro();
        break;
    case 8:
        movimientitosPiezasNegras();
        texto_Reina();
        dibujar_Reina_negra();
        break;
    case 9:
        movimientitosPiezasNegras();
        texto_Alfil();
        dibujar_Alfil_negro();
        break;
    case 10:
        movimientitosPiezasNegras();
        texto_Caballo();
        dibujar_Caballo_negro();
        break;
    case 11:
        movimientitosPiezasNegras();
        texto_Torre();
        dibujar_Torre_negra();
        break;
    case 12:
        movimientitosPiezasNegras();
        texto_Peon();
        dibujar_Peon_negro();
        break;
    }
    glFlush(); //forzamos el renderizado.
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


static void reshape01(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // Establecemos la ventana de visualización (viewport) con las dimensiones dadas.
    glMatrixMode(GL_PROJECTION); // Seleccionamos y configuramos la matriz de proyección
    glLoadIdentity();

    // Configuramos una proyección ortográfica 2D centrada en (0, 0) con el tamaño de la ventana
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

//Función auxiliar para dibujar una pieza según su tipo y si está seleccionada
void dibujarPiezaSegunTipo(TipoPieza tipo, int fila, int columna, float rotX, float rotY, float rotZ) {
    //Guardar el estado de la matriz ANTES de hacer cualquier cambio
    //NO guardar el color en los atributos para evitar que se restaure
    glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT | GL_ENABLE_BIT | GL_LINE_BIT | GL_POLYGON_BIT);
    
    //Guardar las variables globales originales ANTES de modificarlas
    int indiceOriginal = indice;
    int piezaOriginal = pieza;
    double SxOriginal = Sx;
    double SyOriginal = Sy;
    double SzOriginal = Sz;
    
    //Asegurar que Sx, Sy, Sz estén en 0 para que las piezas se dibujen en la posición correcta
    Sx = 0.0;
    Sy = 0.0;
    Sz = 0.0;
    
    //Establecer el color según el tipo de pieza (SIEMPRE color normal, sin selección visual)
    //Desactivar temporalmente la iluminación para que el color se aplique directamente
    GLboolean lightingWasEnabled = glIsEnabled(GL_LIGHTING);
    if(lightingWasEnabled) {
        glDisable(GL_LIGHTING);
    }
    
    //Establecer el color normal según el tipo de pieza
    if(tipo > 0) {
        //Pieza blanca
        glColor3f(1.0, 1.0, 1.0);
    } else if(tipo < 0) {
        //Pieza negra
        glColor3f(0.0, 0.0, 0.0);
    }
    
    //Reactivar la iluminación si estaba activada
    if(lightingWasEnabled) {
        glEnable(GL_LIGHTING);
        //Usar glColorMaterial para que el color se aplique correctamente con iluminación
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    }
    
    //Dibujar la pieza según su tipo
    switch(tipo) {
        case TORRE_BLANCA:
        case TORRE_NEGRA:
            dibujar_Torre();
            break;
        case CABALLO_BLANCO:
            glRotatef(90, 0.0f, 1.0f, 0.0f);
            pieza = 3;
            //Re-establecer el color ANTES de dibujar para asegurar que no se cambie
            glColor3f(1.0, 1.0, 1.0); // Blanco
            dibujar_Caballo();
            break;
        case CABALLO_NEGRO:
            glRotatef(-90, 0.0f, 1.0f, 0.0f);
            pieza = 3;
            //Re-establecer el color ANTES de dibujar para asegurar que no se cambie
            glColor3f(0.0, 0.0, 0.0); // Negro
            dibujar_Caballo();
            break;
        case ALFIL_BLANCO:
        case ALFIL_NEGRO:
            dibujar_Alfil();
            break;
        case REINA_BLANCA:
        case REINA_NEGRA:
            dibujar_Reina();
            break;
        case REY_BLANCO:
        case REY_NEGRO:
            dibujar_Rey();
            break;
        case PEON_BLANCO:
            indice = indice02;
            pieza = 1;
            //Re-establecer el color ANTES de dibujar para asegurar que no se cambie
            glColor3f(1.0, 1.0, 1.0); // Blanco
            dibujar_Peon();
            break;
        case PEON_NEGRO:
            indice = indice02;
            pieza = 1;
            //Re-establecer el color ANTES de dibujar para asegurar que no se cambie
            glColor3f(0.0, 0.0, 0.0); // Negro
            dibujar_Peon();
            break;
        default:
            break;
    }
    
    //Restaurar las variables originales
    indice = indiceOriginal;
    pieza = piezaOriginal;
    Sx = SxOriginal;
    Sy = SyOriginal;
    Sz = SzOriginal;
    
    //Restaurar el estado (pero NO el color, ya que no lo guardamos en los atributos)
    glPopAttrib();
    glPopMatrix();
}

void A1(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x, y, z - 0.35);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	//Dibujar según el estado del tablero y si está seleccionada
	if(tableroJuego[0][0] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[0][0], 0, 0, -90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Torre_blanca(); // Por defecto si no hay pieza en el tablero
	}
	glPopMatrix();
}

void B1(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 1, y , z - 0.35);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[0][1] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[0][1], 0, 1, -90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Caballo_blanco();
	}
	glPopMatrix();
}

void C1(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 2, y , z - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[0][2] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[0][2], 0, 2, 270.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Alfil_blanco();
	}
	glPopMatrix();
}

void D1(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 3, y , z - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[0][3] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[0][3], 0, 3, 270.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Reina_blanca();
	}
	glPopMatrix();
}

void E1(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 4, y , z - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[0][4] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[0][4], 0, 4, 270.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Rey_blanco();
	}
	glPopMatrix();
}

void F1(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 5, y , z - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[0][5] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[0][5], 0, 5, 270.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Alfil_blanco();
	}
	glPopMatrix();
}

void G1(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 6, y , z - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[0][6] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[0][6], 0, 6, 270.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Caballo_blanco();
	}
	glPopMatrix();
}

void H1(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 7, y , z - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[0][7] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[0][7], 0, 7, 270.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Torre_blanca();
	}
	glPopMatrix();
}

void A2(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x , y + 1.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[1][0] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[1][0], 1, 0, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_blanco();
	}
	glPopMatrix();
}

void B2(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 1.0, y + 1.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[1][1] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[1][1], 1, 1, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_blanco();
	}
	glPopMatrix();
}

void C2(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 2.0 , y + 1.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[1][2] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[1][2], 1, 2, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_blanco();
	}
	glPopMatrix();
}

void D2(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 3.0, y + 1.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[1][3] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[1][3], 1, 3, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_blanco();
	}
	glPopMatrix();
}

void E2(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 4.0, y + 1.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[1][4] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[1][4], 1, 4, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_blanco();
	}
	glPopMatrix();
}

void F2(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 5.0, y + 1.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[1][5] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[1][5], 1, 5, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_blanco();
	}
	glPopMatrix();
}

void G2(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 6.0, y + 1.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[1][6] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[1][6], 1, 6, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_blanco();
	}
	glPopMatrix();
}

void H2(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 7.0, y + 1.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[1][7] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[1][7], 1, 7, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_blanco();
	}
	glPopMatrix();
}

//Piezas negras.
void A8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x, y + 7.0, z  - 0.35 );
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[7][0] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[7][0], 7, 0, -90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Torre_negra();
	}
	glPopMatrix();
}

void B8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 1.0, y + 7.0, z  - 0.35 );
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[7][1] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[7][1], 7, 1, -90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Caballo_negro();
	}
	glPopMatrix();
}

void C8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 2.0, y + 7.0, z  - 0.35 );
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[7][2] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[7][2], 7, 2, 270.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Alfil_negro();
	}
	glPopMatrix();
}

void D8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 3.0, y + 7.0, z  - 0.35 );
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[7][3] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[7][3], 7, 3, 270.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Reina_negra();
	}
	glPopMatrix();
}

void E8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 4.0, y + 7, z  - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[7][4] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[7][4], 7, 4, 270.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Rey_negro();
	}
	glPopMatrix();
}

void F8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 5.0, y + 7, z  - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[7][5] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[7][5], 7, 5, 270.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Alfil_negro();
	}
	glPopMatrix();
}

void G8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 6.0, y + 7.0, z  - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[7][6] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[7][6], 7, 6, 270.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Caballo_negro();
	}
	glPopMatrix();
}

void H8(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 7.0, y + 7.0, z  - 0.35);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[7][7] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[7][7], 7, 7, 270.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Torre_negra();
	}
	glPopMatrix();
}

void A7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x , y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[6][0] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[6][0], 6, 0, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_negro();
	}
	glPopMatrix();
}

void B7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 1.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[6][1] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[6][1], 6, 1, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_negro();
	}
	glPopMatrix();
}

void C7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 2.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[6][2] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[6][2], 6, 2, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_negro();
	}
	glPopMatrix();
}

void D7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 3.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[6][3] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[6][3], 6, 3, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_negro();
	}
	glPopMatrix();
}

void E7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 4.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[6][4] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[6][4], 6, 4, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_negro();
	}
	glPopMatrix();
}

void F7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 5.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[6][5] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[6][5], 6, 5, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_negro();
	}
	glPopMatrix();
}

void G7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 6.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[6][6] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[6][6], 6, 6, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_negro();
	}
	glPopMatrix();
}

void H7(float x, float y, float z){
	glPushMatrix();
	glTranslatef(x + 7.0, y + 6.0, z - 1.0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(tableroJuego[6][7] != VACIO) {
	    dibujarPiezaSegunTipo(tableroJuego[6][7], 6, 7, 90.0f, 0.0f, 0.0f);
	} else {
	    dibujar_Peon_negro();
	}
	glPopMatrix();
}



void display_piezasblancas() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.898f, 0.788f, 0.635f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    piezas_blancas();
    glutSwapBuffers();
}


void display_piezasnegras() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.898f, 0.788f, 0.635f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    piezas_negras();
    glutSwapBuffers();
}

void display_tablero() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.898f, 0.788f, 0.635f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();  // Reset the modelview matrix
    gluLookAt(5.0, 5.0, cameraDistanceTablero, 0.0, 1.0, 0.0, 2.0, 2.0, 0.0);
    glRotatef(rotationAngleX, 1.0, 0.0, 0.0);
    glRotatef(rotationAngleY, 0.0, 1.0, 0.0);
    glRotatef(rotationAngleZ, 0.0, 0.0, 1.0);

    // Specify coordinates for a single cube
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    texto_Tablero();
    dibujar_tablero();
    
    glutSwapBuffers();
}
void display_tableroconpiezas(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.898f, 0.788f, 0.635f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();  // Reset the modelview matrix
    gluLookAt(5.0, 5.0, cameraDistanceTableroConPiezas, 0.0, 1.0, 0.0, 2.0, 2.0, 0.0);
    glRotatef(rotationAngleX, 1.0, 0.0, 0.0);
    glRotatef(rotationAngleY, 0.0, 1.0, 0.0);
    glRotatef(rotationAngleZ, 0.0, 0.0, 1.0);

    // Specify coordinates for a single cube
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    dibujar_tablero();
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


//Declaración adelantada
int clickEnBoton(int x, int y, float bx, float by, float ancho, float alto);
void cargarTexturaPiezaNegra(void);
void cargarTexturaPiezaBlanca(void);

//Función de mouse para la ventana de ajedrez
int mouseAjedrez = 0;
int lastMouseXAjedrez = 0;
int lastMouseYAjedrez = 0;

void mouseAjedrezFunc(int btn, int state, int x, int y) {
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if(estadoActual == MENU_INICIAL) {
            //Verificar clicks en botones
            float botonX = windowWidth / 2 - 100;
            float botonY1 = windowHeight / 2 - 50;
            float botonY2 = windowHeight / 2 - 120;
            
            if(clickEnBoton(x, y, botonX, botonY1, 200, 50)) {
                //Click en "Uno vs Uno"
                estadoActual = SOLICITANDO_NOMBRE_BLANCO;
                inputActivo = 1;
                inputIndex = 0;
                inputBuffer[0] = '\0';
                glutPostRedisplay();
            } else if(clickEnBoton(x, y, botonX, botonY2, 200, 50)) {
                //Click en "Uno vs IA" (por ahora igual que uno vs uno)
                estadoActual = SOLICITANDO_NOMBRE_BLANCO;
                inputActivo = 1;
                inputIndex = 0;
                inputBuffer[0] = '\0';
                glutPostRedisplay();
            }
        } else if(estadoActual == SOLICITANDO_NOMBRE_BLANCO || estadoActual == SOLICITANDO_NOMBRE_NEGRO) {
            //Verificar click en botón de flecha (volver atrás)
            float flechaX = 20;
            float flechaY = windowHeight - 60;
            float flechaTamano = 40;
            
            if(clickEnBoton(x, y, flechaX, flechaY, flechaTamano, flechaTamano)) {
                //Limpiar nombres si se está volviendo desde solicitud de nombre negro
                if(estadoActual == SOLICITANDO_NOMBRE_NEGRO) {
                    nombreJugadorBlanco[0] = '\0';
                }
                //Volver al menú inicial
                estadoActual = MENU_INICIAL;
                inputActivo = 0;
                inputIndex = 0;
                inputBuffer[0] = '\0';
                glutPostRedisplay();
            }
        } else if(estadoActual == JUGANDO_UNO_VS_UNO || estadoActual == JUGANDO_UNO_VS_IA) {
            //Detectar click en el tablero
            //Usar gluUnProject con las matrices correctas
            //Primero necesitamos configurar las matrices como en dibujarJuego
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            float aspect = (float)windowWidth / (float)windowHeight;
            gluPerspective(45.0, aspect, 1.0, 100.0);
            
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            
            float centerX = 3.5;
            float centerY = 3.5;
            float centerZ = 0.0;
            float angleY = (225.0 + rotacionCamaraY) * M_PI / 180.0;
            float angleX = (45.0 + rotacionCamaraX) * M_PI / 180.0;
            float distance = zoomJuego;
            float camX = centerX + distance * cos(angleX) * sin(angleY);
            float camY = centerY + distance * sin(angleX);
            float camZ = centerZ + distance * cos(angleX) * cos(angleY);
            gluLookAt(camX, camY, camZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
            
            //Ahora obtener las matrices
            GLint viewport[4];
            GLdouble modelview[16], projection[16];
            GLdouble winX, winY;
            GLdouble posX1, posY1, posZ1;
            GLdouble posX2, posY2, posZ2;
            
            glGetIntegerv(GL_VIEWPORT, viewport);
            glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
            glGetDoublev(GL_PROJECTION_MATRIX, projection);
            
            //Restaurar matrices
            glPopMatrix();
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            
            winX = (double)x;
            winY = (double)(viewport[3] - y); // Invertir Y
            
            //Obtener dos puntos en el rayo (cerca y lejos)
            gluUnProject(winX, winY, 0.0, modelview, projection, viewport, &posX1, &posY1, &posZ1);
            gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posX2, &posY2, &posZ2);
            
            //Calcular intersección con el plano z=0 (donde está el tablero)
            if(fabs(posZ2 - posZ1) > 0.0001) {
                double t = -posZ1 / (posZ2 - posZ1);
                double worldX = posX1 + t * (posX2 - posX1);
                double worldY = posY1 + t * (posY2 - posY1);
                
                //Convertir coordenadas del mundo a casilla del tablero
                //El tablero va de (0,0) a (7,7) - cada casilla es 1x1
                int columna = (int)(worldX + 0.5); // Redondear
                int fila = (int)(worldY + 0.5);    // Redondear
                
                //Ajustar para que esté en el rango [0, 7]
                if(columna < 0) columna = 0;
                if(columna > 7) columna = 7;
                if(fila < 0) fila = 0;
                if(fila > 7) fila = 7;
                
                //Manejar selección y movimiento de piezas
            if(filaSeleccionada == -1) {
                //No hay pieza seleccionada, intentar seleccionar una
                TipoPieza pieza = tableroJuego[fila][columna];
                if(pieza != VACIO) {
                    int esBlanco = (pieza > 0);
                    //Solo se pueden seleccionar piezas del color del turno actual
                    if((turnoActual > 0 && esBlanco) || (turnoActual < 0 && !esBlanco)) {
                        filaSeleccionada = fila;
                        columnaSeleccionada = columna;
                        calcularMovimientosValidos(fila, columna);
                        glutPostRedisplay();
                    }
                }
            } else {
                //Hay una pieza seleccionada
                if(fila == filaSeleccionada && columna == columnaSeleccionada) {
                    //Click en la misma pieza, deseleccionar
                    filaSeleccionada = -1;
                    columnaSeleccionada = -1;
                    for(int i = 0; i < 8; i++) {
                        for(int j = 0; j < 8; j++) {
                            casillasValidas[i][j] = 0;
                        }
                    }
                    glutPostRedisplay();
                } else if(casillasValidas[fila][columna]) {
                    //Movimiento válido
                    //Mover la pieza
                    tableroJuego[fila][columna] = tableroJuego[filaSeleccionada][columnaSeleccionada];
                    tableroJuego[filaSeleccionada][columnaSeleccionada] = VACIO;
                    
                    //Deseleccionar
                    filaSeleccionada = -1;
                    columnaSeleccionada = -1;
                    for(int i = 0; i < 8; i++) {
                        for(int j = 0; j < 8; j++) {
                            casillasValidas[i][j] = 0;
                        }
                    }
                    
                    //Cambiar turno
                    turnoActual = -turnoActual;
                    
                    glutPostRedisplay();
                } else {
                    //Movimiento inválido, intentar seleccionar otra pieza
                    TipoPieza pieza = tableroJuego[fila][columna];
                    if(pieza != VACIO) {
                        int esBlanco = (pieza > 0);
                        if((turnoActual > 0 && esBlanco) || (turnoActual < 0 && !esBlanco)) {
                            filaSeleccionada = fila;
                            columnaSeleccionada = columna;
                            calcularMovimientosValidos(fila, columna);
                            glutPostRedisplay();
                        }
                    } else {
                        //Click en casilla vacía inválida, deseleccionar
                        filaSeleccionada = -1;
                        columnaSeleccionada = -1;
                        for(int i = 0; i < 8; i++) {
                            for(int j = 0; j < 8; j++) {
                                casillasValidas[i][j] = 0;
                            }
                        }
                        glutPostRedisplay();
                    }
                }
            }
            } // Cerrar el if de fabs(posZ2 - posZ1)
        }
    }
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mouseAjedrez = 0;
    }
    
    //Clic derecho para rotar la cámara en modo juego
    if((estadoActual == JUGANDO_UNO_VS_UNO || estadoActual == JUGANDO_UNO_VS_IA)) {
        if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
            mouseAjedrez = 1;
            lastMouseXAjedrez = x;
            lastMouseYAjedrez = y;
        }
        if(btn == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
            mouseAjedrez = 0;
        }
    }
    
    //Manejo del scroll del mouse (zoom) en modo juego
    if((estadoActual == JUGANDO_UNO_VS_UNO || estadoActual == JUGANDO_UNO_VS_IA) && 
       btn == 3 && state == GLUT_DOWN) { // GLUT_WHEEL_UP
        zoomJuego -= 1.0;
        if(zoomJuego < 10.0) zoomJuego = 10.0;
        glutPostRedisplay();
    }
    if((estadoActual == JUGANDO_UNO_VS_UNO || estadoActual == JUGANDO_UNO_VS_IA) && 
       btn == 4 && state == GLUT_DOWN) { // GLUT_WHEEL_DOWN
        zoomJuego += 1.0;
        if(zoomJuego > 50.0) zoomJuego = 50.0;
        glutPostRedisplay();
    }
}

void motionAjedrezFunc(int x, int y) {
    //En modo juego, permitir rotación con clic derecho
    if(mouseAjedrez && (estadoActual == JUGANDO_UNO_VS_UNO || estadoActual == JUGANDO_UNO_VS_IA)) {
        float deltaX = x - lastMouseXAjedrez;
        float deltaY = y - lastMouseYAjedrez;
        
        rotacionCamaraY += deltaX * 0.5;
        rotacionCamaraX += deltaY * 0.5;
        
        //Limitar la rotación vertical
        if(rotacionCamaraX > 89.0) rotacionCamaraX = 89.0;
        if(rotacionCamaraX < -89.0) rotacionCamaraX = -89.0;
        
        lastMouseXAjedrez = x;
        lastMouseYAjedrez = y;
        glutPostRedisplay();
    }
}

void keyboardtodos(unsigned char key, int x, int y) {
    //Manejar input de texto para nombres
    if(inputActivo && (estadoActual == SOLICITANDO_NOMBRE_BLANCO || estadoActual == SOLICITANDO_NOMBRE_NEGRO)) {
        if(key == 13 || key == 10) { // Enter
            if(inputIndex > 0) {
                if(estadoActual == SOLICITANDO_NOMBRE_BLANCO) {
                    strcpy(nombreJugadorBlanco, inputBuffer);
                    estadoActual = SOLICITANDO_NOMBRE_NEGRO;
                    inputIndex = 0;
                    inputBuffer[0] = '\0';
                } else if(estadoActual == SOLICITANDO_NOMBRE_NEGRO) {
                    strcpy(nombreJugadorNegro, inputBuffer);
                    estadoActual = JUGANDO_UNO_VS_UNO;
                    inputActivo = 0;
                    inputIndex = 0;
                    inputBuffer[0] = '\0';
                    inicializarTablero(); // Inicializar el tablero cuando se entra al juego
                }
            }
            glutPostRedisplay();
        } else if(key == 8 || key == 127) { // Backspace
            if(inputIndex > 0) {
                inputIndex--;
                inputBuffer[inputIndex] = '\0';
                glutPostRedisplay();
            }
        } else if(key >= 32 && key <= 126 && inputIndex < 49) { // Caracteres imprimibles
            inputBuffer[inputIndex] = key;
            inputIndex++;
            inputBuffer[inputIndex] = '\0';
            glutPostRedisplay();
        }
        return;
    }
    
    //En modo juego, mantener funcionalidad original
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

//Funciones de mouse para tablero y tablero con piezas
void mouseTableroFunc(int btn, int state, int x, int y) {
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseTablero = 1;
        lastMouseXTablero = x;
        lastMouseYTablero = y;
    }
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mouseTablero = 0;
    }
    // Manejo del scroll del mouse (zoom)
    if(btn == 3 && state == GLUT_DOWN) { // GLUT_WHEEL_UP
        cameraDistanceTablero -= 1.0;
        if(cameraDistanceTablero < 5.0) cameraDistanceTablero = 5.0;
        glutPostRedisplay();
    }
    if(btn == 4 && state == GLUT_DOWN) { // GLUT_WHEEL_DOWN
        cameraDistanceTablero += 1.0;
        if(cameraDistanceTablero > 50.0) cameraDistanceTablero = 50.0;
        glutPostRedisplay();
    }
}

void motionTableroFunc(int x, int y) {
    if(mouseTablero) {
        rotationAngleY += (x - lastMouseXTablero) * 0.5;
        rotationAngleX += (y - lastMouseYTablero) * 0.5;
        lastMouseXTablero = x;
        lastMouseYTablero = y;
        glutPostRedisplay();
    }
}

void mouseTableroConPiezasFunc(int btn, int state, int x, int y) {
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseTableroConPiezas = 1;
        lastMouseXTableroConPiezas = x;
        lastMouseYTableroConPiezas = y;
    }
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mouseTableroConPiezas = 0;
    }
    // Manejo del scroll del mouse (zoom)
    if(btn == 3 && state == GLUT_DOWN) { // GLUT_WHEEL_UP
        cameraDistanceTableroConPiezas -= 1.0;
        if(cameraDistanceTableroConPiezas < 5.0) cameraDistanceTableroConPiezas = 5.0;
        glutPostRedisplay();
    }
    if(btn == 4 && state == GLUT_DOWN) { // GLUT_WHEEL_DOWN
        cameraDistanceTableroConPiezas += 1.0;
        if(cameraDistanceTableroConPiezas > 50.0) cameraDistanceTableroConPiezas = 50.0;
        glutPostRedisplay();
    }
}

void motionTableroConPiezasFunc(int x, int y) {
    if(mouseTableroConPiezas) {
        rotationAngleY += (x - lastMouseXTableroConPiezas) * 0.5;
        rotationAngleX += (y - lastMouseYTableroConPiezas) * 0.5;
        lastMouseXTableroConPiezas = x;
        lastMouseYTableroConPiezas = y;
        glutPostRedisplay();
    }
}

//Funciones de mouse para piezas blancas y negras
void mousePiezasBlancasFunc(int btn, int state, int x, int y) {
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mousePiezasBlancas = 1;
        lastMouseXPiezasBlancas = x;
        lastMouseYPiezasBlancas = y;
    }
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mousePiezasBlancas = 0;
    }
    // Manejo del scroll del mouse (zoom)
    if(btn == 3 && state == GLUT_DOWN) { // GLUT_WHEEL_UP
        cameraZPiezasBlancas -= 0.5;
        if(cameraZPiezasBlancas < 2.0) cameraZPiezasBlancas = 2.0;
        glutPostRedisplay();
    }
    if(btn == 4 && state == GLUT_DOWN) { // GLUT_WHEEL_DOWN
        cameraZPiezasBlancas += 0.5;
        if(cameraZPiezasBlancas > 20.0) cameraZPiezasBlancas = 20.0;
        glutPostRedisplay();
    }
}

void motionPiezasBlancasFunc(int x, int y) {
    if(mousePiezasBlancas) {
        eje_y += (x - lastMouseXPiezasBlancas) * 0.01;
        eje_x += (y - lastMouseYPiezasBlancas) * 0.01;
        lastMouseXPiezasBlancas = x;
        lastMouseYPiezasBlancas = y;
        glutPostRedisplay();
    }
}

void mousePiezasNegrasFunc(int btn, int state, int x, int y) {
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mousePiezasNegras = 1;
        lastMouseXPiezasNegras = x;
        lastMouseYPiezasNegras = y;
    }
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mousePiezasNegras = 0;
    }
    // Manejo del scroll del mouse (zoom)
    if(btn == 3 && state == GLUT_DOWN) { // GLUT_WHEEL_UP
        cameraZPiezasNegras -= 0.5;
        if(cameraZPiezasNegras < 2.0) cameraZPiezasNegras = 2.0;
        glutPostRedisplay();
    }
    if(btn == 4 && state == GLUT_DOWN) { // GLUT_WHEEL_DOWN
        cameraZPiezasNegras += 0.5;
        if(cameraZPiezasNegras > 20.0) cameraZPiezasNegras = 20.0;
        glutPostRedisplay();
    }
}

void motionPiezasNegrasFunc(int x, int y) {
    if(mousePiezasNegras) {
        eje_y += (x - lastMouseXPiezasNegras) * 0.01;
        eje_x += (y - lastMouseYPiezasNegras) * 0.01;
        lastMouseXPiezasNegras = x;
        lastMouseYPiezasNegras = y;
        glutPostRedisplay();
    }
}

//Función para cargar y crear textura de la imagen
void cargarTexturaPiezaNegra() {
    if(texturaCargada && texturaPiezaNegra != 0) return;
    
    //Intentar cargar diferentes nombres de archivo
    const char* nombres[] = {"pieza_negra.png", "pieza_negra.jpg", "pieza_negra.jpeg", NULL};
    int i = 0;
    
    while(nombres[i] != NULL) {
        imagenPiezaNegra = stbi_load(nombres[i], &anchoImagen, &altoImagen, &canalesImagen, 4);
        if(imagenPiezaNegra != NULL) {
            //Generar textura solo si no existe
            if(texturaPiezaNegra == 0) {
                glGenTextures(1, &texturaPiezaNegra);
            }
            glBindTexture(GL_TEXTURE_2D, texturaPiezaNegra);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, anchoImagen, altoImagen, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagenPiezaNegra);
            
            texturaCargada = 1;
            //No liberar la memoria de la imagen todavía, la necesitamos
            break;
        }
        i++;
    }
}

//Función para cargar y crear textura de la imagen de la pieza blanca
void cargarTexturaPiezaBlanca() {
    if(texturaBlancaCargada && texturaPiezaBlanca != 0) return;
    
    //Intentar cargar diferentes nombres de archivo
    const char* nombres[] = {"pieza_blanca.png", "pieza_blanca.jpg", "pieza_blanca.jpeg", NULL};
    int i = 0;
    
    while(nombres[i] != NULL) {
        imagenPiezaBlanca = stbi_load(nombres[i], &anchoImagenBlanca, &altoImagenBlanca, &canalesImagenBlanca, 4);
        if(imagenPiezaBlanca != NULL) {
            //Generar textura solo si no existe
            if(texturaPiezaBlanca == 0) {
                glGenTextures(1, &texturaPiezaBlanca);
            }
            glBindTexture(GL_TEXTURE_2D, texturaPiezaBlanca);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, anchoImagenBlanca, altoImagenBlanca, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagenPiezaBlanca);
            
            texturaBlancaCargada = 1;
            //No liberar la memoria de la imagen todavía, la necesitamos
            break;
        }
        i++;
    }
}

//Función para dibujar texto en 2D
void dibujarTexto2D(float x, float y, const char* texto) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(x, y);
    for (int i = 0; texto[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[i]);
    }
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

//Función para dibujar un botón
void dibujarBoton(float x, float y, float ancho, float alto, const char* texto) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    //Asegurar que texturas e iluminación estén deshabilitadas
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    
    //Dibujar fondo del botón
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + ancho, y);
    glVertex2f(x + ancho, y + alto);
    glVertex2f(x, y + alto);
    glEnd();
    
    //Borde del botón
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + ancho, y);
    glVertex2f(x + ancho, y + alto);
    glVertex2f(x, y + alto);
    glEnd();
    glLineWidth(1.0);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    //Dibujar el texto usando la misma función que funciona para el título
    //Calcular posición del texto centrado
    int len = strlen(texto);
    float textoAncho = len * 9.0;
    float textoX = x + (ancho - textoAncho) / 2.0;
    float textoY = y + (alto / 2.0) - 9.0;
    
    //Usar dibujarTexto2D que sabemos que funciona
    dibujarTexto2D(textoX, textoY, texto);
}

//Función para verificar si un click está dentro de un botón
int clickEnBoton(int x, int y, float bx, float by, float ancho, float alto) {
    float glY = windowHeight - y; // Convertir coordenada Y de GLUT a OpenGL
    return (glY >= by && glY <= by + alto && x >= bx && x <= bx + ancho);
}

//Función para dibujar el menú inicial
void dibujarMenuInicial() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.898f, 0.788f, 0.635f, 1.0f);
    
    //Título "AJEDREZ" centrado
    float tituloX = windowWidth / 2 - 60;
    float tituloY = windowHeight / 2 + 100;
    dibujarTexto2D(tituloX, tituloY, "AJEDREZ");
    
    //Botón "Uno vs Uno"
    float botonX = windowWidth / 2 - 100;
    float botonY1 = windowHeight / 2 - 50;
    dibujarBoton(botonX, botonY1, 200, 50, "Uno vs Uno");
    
    //Botón "Uno vs IA"
    float botonY2 = windowHeight / 2 - 120;
    dibujarBoton(botonX, botonY2, 200, 50, "Uno vs IA");
    
    glutSwapBuffers();
}

//Función para dibujar un botón de flecha (volver atrás)
void dibujarBotonFlecha(float x, float y, float tamano) {
    glColor3f(0.3, 0.3, 0.3);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + tamano, y);
    glVertex2f(x + tamano, y + tamano);
    glVertex2f(x, y + tamano);
    glEnd();
    
    //Dibujar flecha apuntando a la izquierda
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(3.0);
    glBegin(GL_TRIANGLES);
    //Triángulo de la flecha
    float centroX = x + tamano / 2;
    float centroY = y + tamano / 2;
    float anchoFlecha = tamano * 0.3;
    glVertex2f(centroX + anchoFlecha, centroY - tamano * 0.2);
    glVertex2f(centroX - anchoFlecha, centroY);
    glVertex2f(centroX + anchoFlecha, centroY + tamano * 0.2);
    glEnd();
    
    //Línea horizontal de la flecha
    glBegin(GL_LINES);
    glVertex2f(centroX + anchoFlecha, centroY);
    glVertex2f(centroX + tamano * 0.3, centroY);
    glEnd();
    
    //Borde del botón
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + tamano, y);
    glVertex2f(x + tamano, y + tamano);
    glVertex2f(x, y + tamano);
    glEnd();
    glLineWidth(1.0);
}

//Función para dibujar pantalla de solicitud de nombre
void dibujarSolicitudNombre(int esBlanco) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.898f, 0.788f, 0.635f, 1.0f);
    
    //Botón de flecha para volver atrás (esquina superior izquierda)
    float flechaX = 20;
    float flechaY = windowHeight - 60;
    float flechaTamano = 40;
    dibujarBotonFlecha(flechaX, flechaY, flechaTamano);
    
    //Dibujar imagen de la pieza correspondiente arriba del mensaje
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    //Dibujar imagen de la pieza blanca o negra según corresponda
    if(esBlanco) {
        cargarTexturaPiezaBlanca();
        if(texturaBlancaCargada && texturaPiezaBlanca != 0) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texturaPiezaBlanca);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor3f(1.0, 1.0, 1.0);
            
            //Posición de la imagen: centrada arriba del mensaje
            float imgX = windowWidth / 2 - 60;
            float imgY = windowHeight / 2 + 150;
            float imgWidth = 120;
            float imgHeight = 120;
            
            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex2f(imgX, imgY);
            glTexCoord2f(1.0, 1.0); glVertex2f(imgX + imgWidth, imgY);
            glTexCoord2f(1.0, 0.0); glVertex2f(imgX + imgWidth, imgY + imgHeight);
            glTexCoord2f(0.0, 0.0); glVertex2f(imgX, imgY + imgHeight);
            glEnd();
            
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
        }
    } else {
        cargarTexturaPiezaNegra();
        if(texturaCargada && texturaPiezaNegra != 0) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texturaPiezaNegra);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor3f(1.0, 1.0, 1.0);
            
            //Posición de la imagen: centrada arriba del mensaje
            float imgX = windowWidth / 2 - 60;
            float imgY = windowHeight / 2 + 150;
            float imgWidth = 120;
            float imgHeight = 120;
            
            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex2f(imgX, imgY);
            glTexCoord2f(1.0, 1.0); glVertex2f(imgX + imgWidth, imgY);
            glTexCoord2f(1.0, 0.0); glVertex2f(imgX + imgWidth, imgY + imgHeight);
            glTexCoord2f(0.0, 0.0); glVertex2f(imgX, imgY + imgHeight);
            glEnd();
            
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
        }
    }
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    char mensaje[100];
    if (esBlanco) {
        sprintf(mensaje, "Ingrese nombre del jugador de piezas BLANCAS:");
    } else {
        sprintf(mensaje, "Ingrese nombre del jugador de piezas NEGRAS:");
    }
    
    float mensajeX = windowWidth / 2 - 200;
    float mensajeY = windowHeight / 2 + 50;
    dibujarTexto2D(mensajeX, mensajeY, mensaje);
    
    //Mostrar input actual
    char inputDisplay[60];
    sprintf(inputDisplay, "Nombre: %s_", inputBuffer);
    float inputX = windowWidth / 2 - 100;
    float inputY = windowHeight / 2;
    dibujarTexto2D(inputX, inputY, inputDisplay);
    
    glutSwapBuffers();
}

//Inicializar el tablero con las piezas en sus posiciones iniciales
void inicializarTablero() {
    //Limpiar tablero
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            tableroJuego[i][j] = VACIO;
        }
    }
    
    //Piezas blancas (fila 0 y 1)
    tableroJuego[0][0] = TORRE_BLANCA;   // A1
    tableroJuego[0][1] = CABALLO_BLANCO; // B1
    tableroJuego[0][2] = ALFIL_BLANCO;   // C1
    tableroJuego[0][3] = REINA_BLANCA;   // D1
    tableroJuego[0][4] = REY_BLANCO;     // E1
    tableroJuego[0][5] = ALFIL_BLANCO;   // F1
    tableroJuego[0][6] = CABALLO_BLANCO; // G1
    tableroJuego[0][7] = TORRE_BLANCA;   // H1
    
    for(int j = 0; j < 8; j++) {
        tableroJuego[1][j] = PEON_BLANCO; // Fila 2 (A2-H2)
    }
    
    //Piezas negras (fila 6 y 7)
    for(int j = 0; j < 8; j++) {
        tableroJuego[6][j] = PEON_NEGRO; // Fila 7 (A7-H7)
    }
    
    tableroJuego[7][0] = TORRE_NEGRA;   // A8
    tableroJuego[7][1] = CABALLO_NEGRO; // B8
    tableroJuego[7][2] = ALFIL_NEGRO;   // C8
    tableroJuego[7][3] = REINA_NEGRA;   // D8
    tableroJuego[7][4] = REY_NEGRO;     // E8
    tableroJuego[7][5] = ALFIL_NEGRO;   // F8
    tableroJuego[7][6] = CABALLO_NEGRO; // G8
    tableroJuego[7][7] = TORRE_NEGRA;   // H8
    
    //Inicializar turno
    turnoActual = 1; // Empiezan las blancas
    piezaSeleccionada = -1;
    filaSeleccionada = -1;
    columnaSeleccionada = -1;
    
    //Limpiar casillas válidas
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            casillasValidas[i][j] = 0;
        }
    }
}

//Verificar si una casilla tiene una pieza del color dado
int esPiezaColor(int fila, int columna, int color) {
    if(fila < 0 || fila >= 8 || columna < 0 || columna >= 8) return 0;
    TipoPieza pieza = tableroJuego[fila][columna];
    if(color > 0) {
        return (pieza > 0); // Pieza blanca
    } else {
        return (pieza < 0); // Pieza negra
    }
}

//Calcular movimientos válidos para un peón
void calcularMovimientosPeon(int fila, int columna, int esBlanco) {
    int direccion = esBlanco ? 1 : -1; // Blancas avanzan hacia arriba (fila+), negras hacia abajo (fila-)
    int filaInicial = esBlanco ? 1 : 6;
    
    //Movimiento hacia adelante (1 casilla)
    int nuevaFila = fila + direccion;
    if(nuevaFila >= 0 && nuevaFila < 8 && tableroJuego[nuevaFila][columna] == VACIO) {
        casillasValidas[nuevaFila][columna] = 1;
        
        //Si es el primer movimiento, puede avanzar 2 casillas
        if(fila == filaInicial) {
            nuevaFila = fila + 2*direccion;
            if(nuevaFila >= 0 && nuevaFila < 8 && tableroJuego[nuevaFila][columna] == VACIO) {
                casillasValidas[nuevaFila][columna] = 1;
            }
        }
    }
    
    //Captura diagonal izquierda
    nuevaFila = fila + direccion;
    int nuevaCol = columna - 1;
    if(nuevaFila >= 0 && nuevaFila < 8 && nuevaCol >= 0 && nuevaCol < 8) {
        if(tableroJuego[nuevaFila][nuevaCol] != VACIO && !esPiezaColor(nuevaFila, nuevaCol, esBlanco ? 1 : -1)) {
            casillasValidas[nuevaFila][nuevaCol] = 1;
        }
    }
    
    //Captura diagonal derecha
    nuevaCol = columna + 1;
    if(nuevaFila >= 0 && nuevaFila < 8 && nuevaCol >= 0 && nuevaCol < 8) {
        if(tableroJuego[nuevaFila][nuevaCol] != VACIO && !esPiezaColor(nuevaFila, nuevaCol, esBlanco ? 1 : -1)) {
            casillasValidas[nuevaFila][nuevaCol] = 1;
        }
    }
}

//Calcular movimientos válidos para una torre
void calcularMovimientosTorre(int fila, int columna, int esBlanco) {
    int direcciones[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}}; // Arriba, abajo, derecha, izquierda
    
    for(int d = 0; d < 4; d++) {
        for(int dist = 1; dist < 8; dist++) {
            int nuevaFila = fila + direcciones[d][0] * dist;
            int nuevaCol = columna + direcciones[d][1] * dist;
            
            if(nuevaFila < 0 || nuevaFila >= 8 || nuevaCol < 0 || nuevaCol >= 8) break;
            
            if(tableroJuego[nuevaFila][nuevaCol] == VACIO) {
                casillasValidas[nuevaFila][nuevaCol] = 1;
            } else {
                //Hay una pieza, puede capturarla si es del otro color
                if(!esPiezaColor(nuevaFila, nuevaCol, esBlanco ? 1 : -1)) {
                    casillasValidas[nuevaFila][nuevaCol] = 1;
                }
                break; // No puede pasar por encima
            }
        }
    }
}

//Calcular movimientos válidos para un alfil
void calcularMovimientosAlfil(int fila, int columna, int esBlanco) {
    int direcciones[4][2] = {{1,1}, {1,-1}, {-1,1}, {-1,-1}}; // Diagonales
    
    for(int d = 0; d < 4; d++) {
        for(int dist = 1; dist < 8; dist++) {
            int nuevaFila = fila + direcciones[d][0] * dist;
            int nuevaCol = columna + direcciones[d][1] * dist;
            
            if(nuevaFila < 0 || nuevaFila >= 8 || nuevaCol < 0 || nuevaCol >= 8) break;
            
            if(tableroJuego[nuevaFila][nuevaCol] == VACIO) {
                casillasValidas[nuevaFila][nuevaCol] = 1;
            } else {
                if(!esPiezaColor(nuevaFila, nuevaCol, esBlanco ? 1 : -1)) {
                    casillasValidas[nuevaFila][nuevaCol] = 1;
                }
                break;
            }
        }
    }
}

//Calcular movimientos válidos para un caballo
void calcularMovimientosCaballo(int fila, int columna, int esBlanco) {
    int movimientos[8][2] = {{2,1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2}};
    
    for(int m = 0; m < 8; m++) {
        int nuevaFila = fila + movimientos[m][0];
        int nuevaCol = columna + movimientos[m][1];
        
        if(nuevaFila >= 0 && nuevaFila < 8 && nuevaCol >= 0 && nuevaCol < 8) {
            if(tableroJuego[nuevaFila][nuevaCol] == VACIO || !esPiezaColor(nuevaFila, nuevaCol, esBlanco ? 1 : -1)) {
                casillasValidas[nuevaFila][nuevaCol] = 1;
            }
        }
    }
}

//Calcular movimientos válidos para una reina
void calcularMovimientosReina(int fila, int columna, int esBlanco) {
    calcularMovimientosTorre(fila, columna, esBlanco);
    calcularMovimientosAlfil(fila, columna, esBlanco);
}

//Calcular movimientos válidos para un rey
void calcularMovimientosRey(int fila, int columna, int esBlanco) {
    int movimientos[8][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
    
    for(int m = 0; m < 8; m++) {
        int nuevaFila = fila + movimientos[m][0];
        int nuevaCol = columna + movimientos[m][1];
        
        if(nuevaFila >= 0 && nuevaFila < 8 && nuevaCol >= 0 && nuevaCol < 8) {
            if(tableroJuego[nuevaFila][nuevaCol] == VACIO || !esPiezaColor(nuevaFila, nuevaCol, esBlanco ? 1 : -1)) {
                casillasValidas[nuevaFila][nuevaCol] = 1;
            }
        }
    }
}

//Calcular todos los movimientos válidos para una pieza seleccionada
void calcularMovimientosValidos(int fila, int columna) {
    //Limpiar casillas válidas
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            casillasValidas[i][j] = 0;
        }
    }
    
    TipoPieza pieza = tableroJuego[fila][columna];
    int esBlanco = (pieza > 0);
    
    switch(pieza) {
        case PEON_BLANCO:
        case PEON_NEGRO:
            calcularMovimientosPeon(fila, columna, esBlanco);
            break;
        case TORRE_BLANCA:
        case TORRE_NEGRA:
            calcularMovimientosTorre(fila, columna, esBlanco);
            break;
        case ALFIL_BLANCO:
        case ALFIL_NEGRO:
            calcularMovimientosAlfil(fila, columna, esBlanco);
            break;
        case CABALLO_BLANCO:
        case CABALLO_NEGRO:
            calcularMovimientosCaballo(fila, columna, esBlanco);
            break;
        case REINA_BLANCA:
        case REINA_NEGRA:
            calcularMovimientosReina(fila, columna, esBlanco);
            break;
        case REY_BLANCO:
        case REY_NEGRO:
            calcularMovimientosRey(fila, columna, esBlanco);
            break;
    }
}

//Dibujar un cuadro rojo en una casilla del tablero
void dibujarCuadroRojo(int fila, int columna) {
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 0.0, 0.0); // Rojo
    glTranslatef(columna + 0.5, fila + 0.5, 0.01); // Ligeramente arriba del tablero
    glScalef(0.9, 0.9, 0.1);
    
    glBegin(GL_QUADS);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glEnd();
    
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

//Función para dibujar el juego con nombres
void dibujarJuego() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.898f, 0.788f, 0.635f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    
    //Configurar proyección en perspectiva para ver las piezas
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    float aspect = (float)windowWidth / (float)windowHeight;
    gluPerspective(45.0, aspect, 1.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //Vista isométrica desde arriba - tablero recto pero con ángulo para ver las piezas
    //El tablero está en el plano XY (horizontal), centrado aproximadamente en (3.5, 3.5, 0)
    float centerX = 3.5;
    float centerY = 3.5;
    float centerZ = 0.0;
    //Vista isométrica con rotación controlada por el mouse (clic derecho)
    float angleY = (225.0 + rotacionCamaraY) * M_PI / 180.0; // Rotación horizontal (inicial 225 grados)
    float angleX = (45.0 + rotacionCamaraX) * M_PI / 180.0; // Rotación vertical (inicial 45 grados)
    
    float distance = zoomJuego;
    
    //Calcular posición de la cámara basada en rotaciones esféricas
    float camX = centerX + distance * cos(angleX) * sin(angleY);
    float camY = centerY + distance * sin(angleX);
    float camZ = centerZ + distance * cos(angleX) * cos(angleY);
    
    gluLookAt(camX, camY, camZ, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
    
    //Dibujar tablero con piezas
    float x = 0.0;
    float y = 0.0;
    float z = 0.0; // Z base del tablero
    
    dibujar_tablero();
    
    //Dibujar cuadros rojos en casillas válidas si hay una pieza seleccionada
    if(filaSeleccionada >= 0 && columnaSeleccionada >= 0) {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                if(casillasValidas[i][j]) {
                    dibujarCuadroRojo(i, j);
                }
            }
        }
    }
    
    //Habilitar depth test para que las piezas se vean correctamente
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    //Dibujar todas las piezas en el tablero
    //Las piezas se dibujan con sus funciones que ya tienen la rotación correcta
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
    
    glDisable(GL_LIGHTING);
    
    //Dibujar nombres y piezas en pantalla (2D overlay)
    //Guardar el estado de las texturas antes de cambiar matrices
    GLboolean texturaHabilitada = glIsEnabled(GL_TEXTURE_2D);
    GLint texturaActual = 0;
    if(texturaHabilitada) {
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &texturaActual);
    }
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    //Lado izquierdo - Jugador blanco
    if (strlen(nombreJugadorBlanco) > 0) {
        char textoBlanco[60];
        sprintf(textoBlanco, "%s", nombreJugadorBlanco);
        dibujarTexto2D(20, windowHeight - 30, textoBlanco);
        
        //Cargar textura si no está cargada (siempre verificar)
        cargarTexturaPiezaBlanca();
        
        //Dibujar imagen de la pieza blanca debajo del nombre
        if(texturaBlancaCargada && texturaPiezaBlanca != 0) {
            //Asegurarse de que las texturas estén habilitadas
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texturaPiezaBlanca);
            
            //Asegurar que el blending esté correcto para transparencias
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            glColor3f(1.0, 1.0, 1.0);
            
            float imgX = 20;
            float imgY = windowHeight - 150;
            float imgWidth = 120;
            float imgHeight = 120;
            
            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex2f(imgX, imgY);
            glTexCoord2f(1.0, 1.0); glVertex2f(imgX + imgWidth, imgY);
            glTexCoord2f(1.0, 0.0); glVertex2f(imgX + imgWidth, imgY + imgHeight);
            glTexCoord2f(0.0, 0.0); glVertex2f(imgX, imgY + imgHeight);
            glEnd();
            
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
        } else {
            //Si no hay imagen, dibujar pieza blanca pequeña (rey blanco simplificado)
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_QUADS);
            glVertex2f(20, windowHeight - 60);
            glVertex2f(50, windowHeight - 60);
            glVertex2f(50, windowHeight - 90);
            glVertex2f(20, windowHeight - 90);
            glEnd();
            //Corona del rey
            glColor3f(1.0, 1.0, 0.8);
            glBegin(GL_TRIANGLES);
            glVertex2f(25, windowHeight - 60);
            glVertex2f(35, windowHeight - 50);
            glVertex2f(45, windowHeight - 60);
            glEnd();
            glColor3f(0.0, 0.0, 0.0);
            glLineWidth(1.5);
            glBegin(GL_LINE_LOOP);
            glVertex2f(20, windowHeight - 60);
            glVertex2f(50, windowHeight - 60);
            glVertex2f(50, windowHeight - 90);
            glVertex2f(20, windowHeight - 90);
            glEnd();
            glBegin(GL_LINE_LOOP);
            glVertex2f(25, windowHeight - 60);
            glVertex2f(35, windowHeight - 50);
            glVertex2f(45, windowHeight - 60);
            glEnd();
        }
    }
    
    //Lado derecho - Jugador negro
    if (strlen(nombreJugadorNegro) > 0) {
        char textoNegro[60];
        sprintf(textoNegro, "%s", nombreJugadorNegro);
        float textoX = windowWidth - strlen(nombreJugadorNegro) * 10 - 60;
        dibujarTexto2D(textoX, windowHeight - 30, textoNegro);
        
        //Cargar textura si no está cargada (siempre verificar)
        cargarTexturaPiezaNegra();
        
        //Dibujar imagen de la pieza negra debajo del nombre
        if(texturaCargada && texturaPiezaNegra != 0) {
            //Asegurarse de que las texturas estén habilitadas
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texturaPiezaNegra);
            
            //Asegurar que el blending esté correcto para transparencias
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            glColor3f(1.0, 1.0, 1.0);
            
            float imgX = windowWidth - 140;
            float imgY = windowHeight - 150;
            float imgWidth = 120;
            float imgHeight = 120;
            
            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex2f(imgX, imgY);
            glTexCoord2f(1.0, 1.0); glVertex2f(imgX + imgWidth, imgY);
            glTexCoord2f(1.0, 0.0); glVertex2f(imgX + imgWidth, imgY + imgHeight);
            glTexCoord2f(0.0, 0.0); glVertex2f(imgX, imgY + imgHeight);
            glEnd();
            
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
        } else {
            //Si no hay imagen, dibujar pieza negra pequeña (rey negro simplificado)
            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_QUADS);
            glVertex2f(windowWidth - 50, windowHeight - 60);
            glVertex2f(windowWidth - 20, windowHeight - 60);
            glVertex2f(windowWidth - 20, windowHeight - 90);
            glVertex2f(windowWidth - 50, windowHeight - 90);
            glEnd();
            //Corona del rey
            glColor3f(0.2, 0.2, 0.2);
            glBegin(GL_TRIANGLES);
            glVertex2f(windowWidth - 45, windowHeight - 60);
            glVertex2f(windowWidth - 35, windowHeight - 50);
            glVertex2f(windowWidth - 25, windowHeight - 60);
            glEnd();
            glColor3f(0.5, 0.5, 0.5);
            glLineWidth(1.5);
            glBegin(GL_LINE_LOOP);
            glVertex2f(windowWidth - 50, windowHeight - 60);
            glVertex2f(windowWidth - 20, windowHeight - 60);
            glVertex2f(windowWidth - 20, windowHeight - 90);
            glVertex2f(windowWidth - 50, windowHeight - 90);
            glEnd();
            glBegin(GL_LINE_LOOP);
            glVertex2f(windowWidth - 45, windowHeight - 60);
            glVertex2f(windowWidth - 35, windowHeight - 50);
            glVertex2f(windowWidth - 25, windowHeight - 60);
            glEnd();
        }
    }
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    //Dibujar imágenes al final, después de restaurar matrices, para que siempre se vean
    //Esto asegura que las imágenes siempre se dibujen, incluso después de rotaciones o cambios de vista
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    //Dibujar imagen de la pieza blanca (lado izquierdo)
    if(strlen(nombreJugadorBlanco) > 0) {
        cargarTexturaPiezaBlanca();
        if(texturaBlancaCargada && texturaPiezaBlanca != 0) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texturaPiezaBlanca);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor3f(1.0, 1.0, 1.0);
            
            float imgX = 20;
            float imgY = windowHeight - 150;
            float imgWidth = 120;
            float imgHeight = 120;
            
            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex2f(imgX, imgY);
            glTexCoord2f(1.0, 1.0); glVertex2f(imgX + imgWidth, imgY);
            glTexCoord2f(1.0, 0.0); glVertex2f(imgX + imgWidth, imgY + imgHeight);
            glTexCoord2f(0.0, 0.0); glVertex2f(imgX, imgY + imgHeight);
            glEnd();
            
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
        }
    }
    
    //Dibujar imagen de la pieza negra (lado derecho)
    if(strlen(nombreJugadorNegro) > 0) {
        cargarTexturaPiezaNegra();
        if(texturaCargada && texturaPiezaNegra != 0) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texturaPiezaNegra);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor3f(1.0, 1.0, 1.0);
            
            float imgX = windowWidth - 140;
            float imgY = windowHeight - 150;
            float imgWidth = 120;
            float imgHeight = 120;
            
            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0); glVertex2f(imgX, imgY);
            glTexCoord2f(1.0, 1.0); glVertex2f(imgX + imgWidth, imgY);
            glTexCoord2f(1.0, 0.0); glVertex2f(imgX + imgWidth, imgY + imgHeight);
            glTexCoord2f(0.0, 0.0); glVertex2f(imgX, imgY + imgHeight);
            glEnd();
            
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
        }
    }
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glutSwapBuffers();
}

void display_ajedrez(){
    switch(estadoActual) {
        case MENU_INICIAL:
            dibujarMenuInicial();
            break;
        case SOLICITANDO_NOMBRE_BLANCO:
            dibujarSolicitudNombre(1);
            break;
        case SOLICITANDO_NOMBRE_NEGRO:
            dibujarSolicitudNombre(0);
            break;
        case JUGANDO_UNO_VS_UNO:
        case JUGANDO_UNO_VS_IA:
            dibujarJuego();
            break;
    }
}

void reshape2(int width, int height) {
    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //Para la ventana de ajedrez en modo juego, usar proyección ortográfica si está en juego
    if(estadoActual == JUGANDO_UNO_VS_UNO || estadoActual == JUGANDO_UNO_VS_IA) {
        //Proyección ortográfica para vista desde arriba sin distorsión
        float aspect = (float)width / (float)height;
        float size = zoomJuego * 0.5;
        glOrtho(-size * aspect, size * aspect, -size, size, 1.0, 100.0);
    } else {
        gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(!(estadoActual == JUGANDO_UNO_VS_UNO || estadoActual == JUGANDO_UNO_VS_IA)) {
        gluLookAt(-10.0, -10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
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
    glutMouseFunc(mousePiezasBlancasFunc);
    glutMotionFunc(motionPiezasBlancasFunc);

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
    glutMouseFunc(mousePiezasNegrasFunc);
    glutMotionFunc(motionPiezasNegrasFunc);


    //Ventana para tablero
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    tablero = glutCreateWindow("Tablero.");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display_tablero);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseTableroFunc);
    glutMotionFunc(motionTableroFunc);

    //Ventana para el tablero con piezas.
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    tableroconpiezas = glutCreateWindow("Tablero con piezas.");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display_tableroconpiezas);
    glutReshapeFunc(reshape2);
    glutMouseFunc(mouseTableroConPiezasFunc);
    glutMotionFunc(motionTableroConPiezasFunc);

    //Ventana para el ajedrez
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    ajedrez = glutCreateWindow("Ajedrez.");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display_ajedrez);
    glutReshapeFunc(reshape2);
    glutKeyboardFunc(keyboardtodos);
    glutMouseFunc(mouseAjedrezFunc);
    glutMotionFunc(motionAjedrezFunc);

    glutMainLoop(); //iniciamos el bucle principal de GLUT.
    return 0;
}
