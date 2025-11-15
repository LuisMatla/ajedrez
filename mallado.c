#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

// Estructura del vértice
typedef struct vertice {
    float x, y, z;
    struct vertice* sgt;
} Vertice;

// Estructura del triángulo
typedef struct triangulo {
    Vertice* vertice[3];
    struct triangulo* sgt;
} Triangulo;

// Variables globales para la lista de vértices y triángulos
Vertice* primerVertice = NULL;
Triangulo* primerTriangulo = NULL;

// Prototipos de funciones
void liberarMemoriaVertices(Vertice* primerVertice);
void liberarMemoriaTriangulos(Triangulo* primerTriangulo);
void generarTriangulos(Vertice* primerVertice);
void crearListaVertices(int numVertices);
void dibujarTriangulos();
void display();

// Función para crear un nuevo vértice
Vertice* crearVertice(float x, float y, float z) {
    Vertice* nuevoVertice = (Vertice*)malloc(sizeof(Vertice));
    if (nuevoVertice != NULL) {
        nuevoVertice->x = x;
        nuevoVertice->y = y;
        nuevoVertice->z = z;
        nuevoVertice->sgt = NULL;
    }
    return nuevoVertice;
}

// Función para crear un triángulo a partir de tres vértices
Triangulo* crearTriangulo(Vertice* v1, Vertice* v2, Vertice* v3) {
    Triangulo* nuevoTriangulo = (Triangulo*)malloc(sizeof(Triangulo));
    if (nuevoTriangulo != NULL) {
        nuevoTriangulo->vertice[0] = v1;
        nuevoTriangulo->vertice[1] = v2;
        nuevoTriangulo->vertice[2] = v3;
        nuevoTriangulo->sgt = NULL;
    }
    return nuevoTriangulo;
}

// Función para liberar la memoria de los vértices
void liberarMemoriaVertices(Vertice* primerVertice) {
    while (primerVertice != NULL) {
        Vertice* temp = primerVertice;
        primerVertice = primerVertice->sgt;
        free(temp);
    }
}

// Función para liberar la memoria de los triángulos
void liberarMemoriaTriangulos(Triangulo* primerTriangulo) {
    while (primerTriangulo != NULL) {
        Triangulo* temp = primerTriangulo;
        primerTriangulo = primerTriangulo->sgt;
        free(temp);
    }
}

// Función para generar triángulos a partir de los vértices
void generarTriangulos(Vertice* primerVertice) {
    Vertice* actualVertice = primerVertice;
    int numVertices = 0;

    // Contar el número de vértices
    while (actualVertice != NULL) {
        numVertices++;
        actualVertice = actualVertice->sgt;
    }

    if (numVertices < 3) {
        printf("Se necesitan al menos tres vértices.\n");
        return;
    }

    actualVertice = primerVertice;
    Triangulo* ultimoTriangulo = NULL;

    // Crear triángulos usando tres vértices consecutivos
    for (int i = 0; i < numVertices - 2; i++) {
        Triangulo* nuevoTriangulo = crearTriangulo(actualVertice, actualVertice->sgt, actualVertice->sgt->sgt);
        if (primerTriangulo == NULL) {
            primerTriangulo = nuevoTriangulo;
        } else {
            ultimoTriangulo->sgt = nuevoTriangulo;
        }
        ultimoTriangulo = nuevoTriangulo;
        actualVertice = actualVertice->sgt;
    }
}

// Función para crear la lista de vértices
void crearListaVertices(int numVertices) {
    float x, y, z;
    Vertice* ultimoVertice = NULL;

    for (int i = 0; i < numVertices; i++) {
        printf("Ingrese las coordenadas del vértice %d (x, y, z): ", i + 1);
        scanf("%f %f %f", &x, &y, &z);

        Vertice* nuevoVertice = crearVertice(x, y, z);
        if (primerVertice == NULL) {
            primerVertice = nuevoVertice;
        } else {
            ultimoVertice->sgt = nuevoVertice;
        }
        ultimoVertice = nuevoVertice;
    }

    generarTriangulos(primerVertice);
}

// Función de dibujo de triángulos con OpenGL
void dibujarTriangulos() {
    Triangulo* actualTriangulo = primerTriangulo;

    while (actualTriangulo != NULL) {
        glBegin(GL_TRIANGLES);
        glVertex3f(actualTriangulo->vertice[0]->x, actualTriangulo->vertice[0]->y, actualTriangulo->vertice[0]->z);
        glVertex3f(actualTriangulo->vertice[1]->x, actualTriangulo->vertice[1]->y, actualTriangulo->vertice[1]->z);
        glVertex3f(actualTriangulo->vertice[2]->x, actualTriangulo->vertice[2]->y, actualTriangulo->vertice[2]->z);
        glEnd();
        actualTriangulo = actualTriangulo->sgt;
    }
}

// Función display para GLUT
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Dibujar los triángulos
    dibujarTriangulos();

    glutSwapBuffers();
}

// Función main
int main(int argc, char** argv) {
    int numVertices;
    
    printf("Ingrese el número de vértices: ");
    scanf("%d", &numVertices);

    if (numVertices < 3) {
        printf("Se necesitan al menos tres vértices para formar triángulos.\n");
        return 0;
    }

    crearListaVertices(numVertices);

    // Inicialización de GLUT y OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangulos con OpenGL");

    // Configuración de la vista
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.33, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Callback de display
    glutDisplayFunc(display);

    // Iniciar el loop de GLUT
    glutMainLoop();

    // Liberar memoria después de salir
    liberarMemoriaTriangulos(primerTriangulo);
    liberarMemoriaVertices(primerVertice);

    return 0;
}
