#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura de vértice
struct Vertex {
    float x, y, z;
    struct Vertex* next;
};

// Función para crear un nuevo vértice
struct Vertex* crearVertice(float x, float y, float z) {
    struct Vertex* nuevoVertice = (struct Vertex*)malloc(sizeof(struct Vertex));
    if (nuevoVertice != NULL) {
        nuevoVertice->x = x;
        nuevoVertice->y = y;
        nuevoVertice->z = z;
        nuevoVertice->next = NULL;
    }
    return nuevoVertice;
}

// Estructura para contar triángulos
struct Triangulo {
    struct Vertex* vertices[3];
    struct Triangulo* next;
};

// Función para crear un nuevo triángulo
struct Triangulo* crearTriangulo(struct Vertex* v1, struct Vertex* v2, struct Vertex* v3) {
    struct Triangulo* nuevoTriangulo = (struct Triangulo*)malloc(sizeof(struct Triangulo));
    if (nuevoTriangulo != NULL) {
        nuevoTriangulo->vertices[0] = v1;
        nuevoTriangulo->vertices[1] = v2;
        nuevoTriangulo->vertices[2] = v3;
        nuevoTriangulo->next = NULL;
    }
    return nuevoTriangulo;
}

int main() {
    int numVertices;

    // Solicitar al usuario ingresar el número de vértices
    printf("Ingrese el número de vértices en la malla: ");
    scanf("%d", &numVertices);

    // Verificar que el número de vértices sea válido (al menos 3)
    if (numVertices < 3) {
        printf("El número de vértices debe ser al menos 3.\n");
        return 1;  // Salir del programa con un código de error
    }

    // Crear la lista de vértices vacía
    struct Vertex* primerVertice = NULL;
    struct Vertex* ultimoVertice = NULL;

    // Leer las coordenadas de los vértices desde el usuario y crear la lista
    for (int i = 0; i < numVertices; i++) {
        float x, y, z;
        printf("Ingrese las coordenadas del vértice %d (x y z): ", i);
        scanf("%f %f %f", &x, &y, &z);

        struct Vertex* nuevo = crearVertice(x, y, z);
        if (nuevo == NULL) {
            printf("Error al asignar memoria para el vértice.\n");
            return 1;
        }

        if (ultimoVertice == NULL) {
            primerVertice = nuevo;
            ultimoVertice = nuevo;
        } else {
            ultimoVertice->next = nuevo;
            ultimoVertice = nuevo;
        }
    }

    // Calcular el número de triángulos posibles
    int numTriangulos = numVertices / 3;

    // Crear la lista de triángulos vacía
    struct Triangulo* primerTriangulo = NULL;
    struct Triangulo* ultimoTriangulo = NULL;

    // Crear los triángulos a partir de los vértices
    struct Vertex* actualVertice = primerVertice;
    for (int i = 0; i < numTriangulos; i++) {
        struct Triangulo* nuevoTriangulo = crearTriangulo(actualVertice, actualVertice->next, actualVertice->next->next);
        if (nuevoTriangulo == NULL) {
            printf("Error al asignar memoria para el triángulo.\n");
            return 1;
        }

        if (ultimoTriangulo == NULL) {
            primerTriangulo = nuevoTriangulo;
            ultimoTriangulo = nuevoTriangulo;
        } else {
            ultimoTriangulo->next = nuevoTriangulo;
            ultimoTriangulo = nuevoTriangulo;
        }

        actualVertice = actualVertice->next->next->next;  // Avanzar al siguiente conjunto de vértices
    }

    // Imprimir los datos de la malla
    printf("Número de vértices: %d\n", numVertices);
    printf("Número de triángulos posibles: %d\n", numTriangulos);

    // Imprimir las figuras de los triángulos
    printf("\nFiguras de los triángulos formados:\n");
    struct Triangulo* actualTriangulo = primerTriangulo;
    for (int i = 0; i < numTriangulos; i++) {
        printf("Triángulo %d: (%.2f, %.2f, %.2f) - (%.2f, %.2f, %.2f) - (%.2f, %.2f, %.2f)\n",
               i,
               actualTriangulo->vertices[0]->x, actualTriangulo->vertices[0]->y, actualTriangulo->vertices[0]->z,
               actualTriangulo->vertices[1]->x, actualTriangulo->vertices[1]->y, actualTriangulo->vertices[1]->z,
               actualTriangulo->vertices[2]->x, actualTriangulo->vertices[2]->y, actualTriangulo->vertices[2]->z);
        actualTriangulo = actualTriangulo->next;
    }

    // Liberar la memoria asignada para los vértices
    actualVertice = primerVertice;
    while (actualVertice != NULL) {
        struct Vertex* siguiente = actualVertice->next;
        free(actualVertice);
        actualVertice = siguiente;
    }

    // Liberar la memoria asignada para los triángulos
    actualTriangulo = primerTriangulo;
    while (actualTriangulo != NULL) {
        struct Triangulo* siguiente = actualTriangulo->next;
        free(actualTriangulo);
        actualTriangulo = siguiente;
    }

    return 0;
}
