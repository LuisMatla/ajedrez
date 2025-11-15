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


//Esta función nos ayuda a poder que se grafique el caballo.
void dibujar_Caballo() {

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


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Llama a la función para dibujar el caballo
    dibujar_Caballo();

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
    glutCreateWindow("Knight Piece");

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
