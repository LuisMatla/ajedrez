//Contreras Matlaa Luis Fernando.

/*Programa para dibujar dos segmentos giratorios, unidos.*/

//LIBRERÍAS NECESARIAS
#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

//VARIABLES GLOBALES
double VectorGlobal[4] = {100, 100, 0, 1}; // Almacena las coordenadas del extremo del primer segmento
double center[2] = {250, 250}; // Almacena las coordenadas del centro de rotación del primer segmento
double anguloSegmento2 = 0.0; // Ángulo de rotación del segundo segmento

//Registro para almacenar un punto y la matriz de transformación
typedef struct {
    double posicion[4]; // Para representar la posición del cuerpo en el espacio.
    double matriz[4][4]; // Matriz que se utilizará para rotar y trasladar la figura.
} body;

/* Multiplicación de una matriz 4x4 por un vector de longitud 4, salida en vector c.
   Esta función, así como la de rotar y trasladar, se encargan de las operaciones 
   matemáticas necesarias para transformar los vectores al espacio 3D */
void Matriz_X_Vector(double matrix[4][4], double vector[4], double *c) {
    for (int i = 0; i < 4; i++) {
        c[i] = matrix[i][0] * vector[0] +
               matrix[i][1] * vector[1] +
               matrix[i][2] * vector[2] +
               matrix[i][3] * vector[3];
    }
}

/* Función para rotar el punto definido por el vectorGlobal (X, Y, Z, 1) en un ángulo angle.
   Estamos rotando el brazo alrededor de la articulación. */
void rotar(double *vector, double angle) {
    double seno = sin(angle);
    double coseno = cos(angle);

    double vectortemp[4];

    double matrizRot[4][4] = {{coseno, -seno, 0, 0}, // Matriz utilizada para realizar la rotación.
                              {seno, coseno, 0, 0},
                              {0, 0, 1, 0},
                              {0, 0, 0, 1}};

    Matriz_X_Vector(matrizRot, vector, vectortemp);

    for (int i = 0; i < 4; i++) {
        vector[i] = vectortemp[i];
    }
}

/* Función para trasladar el vector con salida en el vector vectorout,
   es decir, para trasladar el extremo del brazo robótico al centro de rotación */
void trasladar(double *vector, double *vectorout) {
    double matrizTras[4][4] = {{1, 0, 0, center[0]}, // Matriz utilizada para realizar la traslación.
                              {0, 1, 0, center[1]},
                              {0, 0, 1, 0},
                              {0, 0, 0, 1}};

    Matriz_X_Vector(matrizTras, vector, vectorout);
}

/*
  Función que inicializa OpenGL
    -Dentro de ella se establece el color de borrado y
    -el sombreado.
*/
static void init01(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0); // clear to color RGB A
    glShadeModel(GL_FLAT); // The default value is GL_SMOOTH
}

/*
  Función para visualizar.
    -Limpia la pantalla,
    -dibuja los segmentos y
    -actualiza.
*/
static void display01(void) {
    double vectortemp[4];
    trasladar(VectorGlobal, vectortemp); // Para calcular la posición del brazo, traslada el vector al centro de la ventana.
    glClear(GL_COLOR_BUFFER_BIT); // Limpiar ventana en el color del clear color definido en glClearColor()
    glColor3f(1.0, 0.0, 0.0); // Color del dibujo en rojo

    // PARA LAS TRANSFORMACIONES
    glPushMatrix(); // Es una pila de matrices para graficar.
    // Dibujando líneas para representar el primer segmento del brazo.
    glBegin(GL_LINES); // Se define que se dibujarán líneas
    glVertex3f(center[0], center[1], 0); // Primer punto para dibujar
    glVertex3f(vectortemp[0], vectortemp[1], vectortemp[2]); // Segundo punto de la línea
    glEnd();

    // Dibujar el segundo segmento giratorio
    double longitudSegmento2 = 100.0; // Longitud del segundo segmento
    double x2 = vectortemp[0] + longitudSegmento2 * cos(anguloSegmento2);
    double y2 = vectortemp[1] + longitudSegmento2 * sin(anguloSegmento2);

    glBegin(GL_LINES);
    glVertex3f(vectortemp[0], vectortemp[1], vectortemp[2]);
    glVertex3f(x2, y2, 0);
    glEnd();

    glPopMatrix(); // Es una pila de matrices para graficar

    glFlush(); // El dibujo, no será visible de inicio. Use glutSwapBuffers(); if GLUT_DOUBLE
    // glutSwapBuffers(); // El dibujo será visible desde inicio.
    glutPostRedisplay(); // Refrescar la ventana
}

/*
  Función que ajusta la vista, se llama cuando la ventana cambia de 
  tamaño.
*/
static void reshape01(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // Set view to ALL
    glMatrixMode(GL_PROJECTION); // Use PROJECTION matrix
    glLoadIdentity(); // and load it...
    // Set to whole screen
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

/*
  Función que maneja los eventos de teclado.
*/
static void keyboard01(unsigned char key, int x, int y) {
    if ((key == 0x1b) || (key == 'q') || (key == 'Q'))
        exit(0); // Terminar programa
    else if ((key == 'R') || (key == 'r')) {
        printf("Vector Inicial %f, %f, %f\n", VectorGlobal[0], VectorGlobal[1], VectorGlobal[2]);
        rotar(VectorGlobal, -0.1);
        rotar(anguloSegmento2, 0.1);
        printf("Vector final %f, %f, %f\n", VectorGlobal[0], VectorGlobal[1], VectorGlobal[2]);
    }
    else if ((key == 'L') || (key == 'l')) {
        printf("Vector Inicial %f, %f, %f\n", VectorGlobal[0], VectorGlobal[1], VectorGlobal[2]);
        rotar(VectorGlobal, 0.1);
        rotar(anguloSegmento2, -0.1);
        printf("Vector final %f, %f, %f\n", VectorGlobal[0], VectorGlobal[1], VectorGlobal[2]);
    }
    else if ((key == 'u') || (key == 'U')) {
        // Incrementa el ángulo del segundo segmento
        anguloSegmento2 += 0.1;
        if (anguloSegmento2 > 2 * M_PI)
            anguloSegmento2 -= 2 * M_PI;

        glutPostRedisplay(); // Refrescar la ventana para mostrar el nuevo estado del segundo segmento
    }
    else if ((key == 'I') || (key == 'i')) {
        anguloSegmento2 -= 0.1;
        if (anguloSegmento2 < 0)
            anguloSegmento2 += 2 * M_PI;
    }

    glutSwapBuffers(); // Para intercambiar los buffers de color de la ventana, hace que el dibujo sea visible.
}

/* Función principal, en ella:
    -Se establece la configuración del todo,
    -se inicializa GLUT,
    -se crea la ventana y
    -se mandan llamar las funciones necesarias. */
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("BRACITO ^.^");

    init01();

    // Para imprimir la cadena de que se utiliza para los render y la versión de OPENGL
    const GLubyte *renderer = glGetString(GL_RENDERER); // Obtener cadena Render
    const GLubyte *version = glGetString(GL_VERSION); // Obtener cadena versión

    printf("Renderer: %s\n", renderer);
    printf("Versión de OpenGL que soporta: %s\n", version);
    glutDisplayFunc(display01);
    glutReshapeFunc(reshape01);
    glutKeyboardFunc(keyboard01);
    glutMainLoop();
    return 0;
}
