#include <GL/glut.h>

float rotationAngleX = 0.0;
float rotationAngleY = 0.0;
float rotationAngleZ = 0.0;

//Esta función dibuja un cubo para que se pueda hacer el tablero.
void dibujar_cubo(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x, y, z); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.

    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.

    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.

    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.

    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.

    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
}

//Esta función me ayuda a que mi tablero se dibuje por completo tomando como referencia y tamaños del cubo anterior.
void dibujar_tablero() {
    for (int i = 0; i < 8; ++i) { //itera a través de las filas del tablero..
        for (int j = 0; j < 8; ++j) { //itera a través de las columnas del tablero.
            float x = i * 1.0; //calcula la posición x del cubo en el tablero.
            float y = j * 1.0; //calcula la posición y del cubo en el tablero.
            float z = 0.0; //la posición z se mantiene en 0 para el tablero en 2D.
            
            if ((i + j) % 2 == 0) { //verifica si la suma de la fila y la columna es par para alternar colores.
                glColor3f(1.0, 0.75, 0.8); //establece el color blanco para las casillas pares.
            } else {
                glColor3f(0.5, 0.0, 0.5); //establece un color morado para las casillas impares.
            }

            dibujar_cubo(x, y, z); //llama a la función dibujar_cubo con las coordenadas calculadas.
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up the camera
    gluLookAt(5.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(rotationAngleX, 1.0, 0.0, 0.0);
    glRotatef(rotationAngleY, 0.0, 1.0, 0.0);
    glRotatef(rotationAngleZ, 0.0, 0.0, 1.0);

    dibujar_tablero();

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