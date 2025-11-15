#include <GL/glut.h>

float rotationAngleX = 0.0;
float rotationAngleY = 0.0;
float rotationAngleZ = 0.0;


//Función para dibujar el contorno de un cuadrado.
void contorno_cubo(float x, float y, float z) {
    glColor3f(1.0, 1.0, 1.0); //cyan.
    glLineWidth(5.0); //se establece el ancho del contorno.
    glTranslatef(x, y, z); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_LINE_LOOP); //inicia la definición de un conjunto de cuadriláteros (quads).

    glPushMatrix();
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix();

    glLineWidth(1.0); //restaurar el ancho de línea y el color.
}

//Esta función dibuja un cubo para que se pueda hacer el tablero.
void dibujar_cubo(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x, y, z); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix();

    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
    contorno_cubo(x, y, z);
}

//Esta función dibuja un cubo para que se pueda hacer el tablero.
void dibujar_cubo1(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x, y - 1, z); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 1.0, 0.5); //verde claro.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix();

    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
    contorno_cubo(x, y, z);
}

//Esta función dibuja un cubo para que se pueda hacer el tablero.
void dibujar_cubo2(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 1.0, y, z); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 1.0, 0.5); //verde claro.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.0, 0.5);
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
}

//Esta función dibuja un cubo para que se pueda hacer el tablero.
void dibujar_cubo3(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x - 1.0, y, z); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro.
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0); //naranja
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
}

void dibujar_cubo4(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x, y + 1.0, z); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 1.0, 0.5); //verde claro.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix();

    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
    contorno_cubo(x, y, z);
}

void dibujar_cubo5(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 1.0, y + 1.0, z); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 1.0, 0.5); //verde claro.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 1.0); //lila
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
}

//Esta función dibuja un cubo para que se pueda hacer el tablero.
void dibujar_cubo6(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x - 1.0, y + 1, z); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 1.0); //lila
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0); //naranja
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
}

//Esta función dibuja un cubo para que se pueda hacer el tablero.
void dibujar_cubo0(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 1, y - 1, z); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix();
}

void dibujar_cubo01(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 1, y + 1, z); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix();

    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
    contorno_cubo(x, y, z);
}

void dibujar_cubo02(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x - 1, y - 1, z); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.0, 0.5); //morado fuerte
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix();

    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
    contorno_cubo(x, y, z);
}

void dibujar_cubo03(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x - 1, y - 1, z - 1); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 1.0, 0.5); //verde claro.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.0, 0.5);
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0); //naranja
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix();

    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
    contorno_cubo(x, y, z);
}

void dibujar_cubo04(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x - 1, y - 1, z - 2); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 1.0, 0.5); //verde claro.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro.
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0); //naranja
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix();

    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
    contorno_cubo(x, y, z);
}

//Esta función dibuja un cubo para que se pueda hacer el tablero.
void dibujar_cubo7(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x - 1.0, y + 1, z - 1); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 1.0); //lila //negro
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0); //naranja
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
}

void dibujar_cubo8(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x + 1.0, y + 1.0, z - 1); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarillo
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
     glColor3f(0.5, 0.0, 0.5);
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 1.0); //negro
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
}

void dibujar_cubo9(float x, float y, float z) {
    glPushMatrix(); //guarda la matriz actual en la pila de matrices.
    glTranslatef(x, y + 1.0, z - 1); //translada el cubo a la posición especificada por (x, y, z).
    glBegin(GL_QUADS); //inicia la definición de un conjunto de cuadriláteros (quads).

    //Define las seis caras del cubo.
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara frontal inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara frontal inferior derecha.
    glVertex3f(0.5, 0.5, 0.5); //vértice 3 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 4 de la cara frontal superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, -0.5); //vértice 1 de la cara posterior inferior izquierda.
    glVertex3f(0.5, -0.5, -0.5); //vértice 2 de la cara posterior inferior derecha.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior derecha.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); //negro
    glVertex3f(-0.5, -0.5, 0.5); //vértice 1 de la cara inferior izquierda.
    glVertex3f(0.5, -0.5, 0.5); //vértice 2 de la cara inferior derecha.
    glVertex3f(0.5, -0.5, -0.5); //vértice 3 de la cara posterior inferior derecha.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 4 de la cara posterior inferior izquierda.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, 0.5); //vértice 1 de la cara frontal derecha inferior.
    glVertex3f(0.5, 0.5, 0.5); //vértice 2 de la cara frontal derecha superior.
    glVertex3f(0.5, 0.5, -0.5); //vértice 3 de la cara posterior derecha superior.
    glVertex3f(0.5, -0.5, -0.5); //vértice 4 de la cara posterior derecha inferior.
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 1.0); //lila
    glVertex3f(0.5, 0.5, 0.5); //vértice 1 de la cara frontal superior derecha.
    glVertex3f(-0.5, 0.5, 0.5); //vértice 2 de la cara frontal superior izquierda.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 3 de la cara posterior superior izquierda.
    glVertex3f(0.5, 0.5, -0.5); //vértice 4 de la cara posterior superior derecha.
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0); //naranja
    glVertex3f(-0.5, 0.5, 0.5); //vértice 1 de la cara frontal izquierda superior.
    glVertex3f(-0.5, -0.5, 0.5); //vértice 2 de la cara frontal izquierda inferior.
    glVertex3f(-0.5, -0.5, -0.5); //vértice 3 de la cara posterior izquierda inferior.
    glVertex3f(-0.5, 0.5, -0.5); //vértice 4 de la cara posterior izquierda superior.
    glEnd(); //finaliza la definición de los quads.
    glPopMatrix();

    glPopMatrix(); //restaura la matriz previamente guardada en la pila.
    contorno_cubo(x, y, z);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up the camera
    gluLookAt(5.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(rotationAngleX, 1.0, 0.0, 0.0);
    glRotatef(rotationAngleY, 0.0, 1.0, 0.0);
    glRotatef(rotationAngleZ, 0.0, 0.0, 1.0);

    // Specify coordinates for a single cube
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    glPushMatrix();
    dibujar_cubo(x, y, z); // Call dibujar_cubo with specific coordinates
    dibujar_cubo1(x, y, z);
    glPopMatrix();
    glPushMatrix();
    dibujar_cubo2(x, y, z);
    glPopMatrix();
    glPushMatrix();
    dibujar_cubo3(x, y, z);
    glPopMatrix();
    //----
    glPushMatrix();
    dibujar_cubo4(x, y, z);
    glPopMatrix();
    glPushMatrix();
    dibujar_cubo5(x, y, z);
    glPopMatrix();
    dibujar_cubo6(x, y, z);
    glPopMatrix();
    //----

    dibujar_cubo7(x, y, z);
    dibujar_cubo8(x, y, z);
    dibujar_cubo9(x, y, z);
    dibujar_cubo0(x, y, z);
    dibujar_cubo01(x, y, z);
    dibujar_cubo02(x, y, z);
    dibujar_cubo03(x, y, z);
    dibujar_cubo04(x, y, z);
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
            rotationAngleX  += 5;
            break;
        case 'y':
        case 'Y':
            rotationAngleY += 5;
            break;
        case 'z':
        case 'Z':
            rotationAngleZ += 5;
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
    glutCreateWindow("RUBIK.");
    glClearColor(1.0, 0.7, 0.7, 1.0);
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}