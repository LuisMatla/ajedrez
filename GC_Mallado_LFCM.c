/*
    Mallado del triangulo
    Contreras Matla Luis Fernando
    S21020225
    20/09/23
*/
#include <stdio.h>
#include <stdlib.h>

//se define la estructura del vertice
typedef struct vertice {
    float x, y, z;
    struct vertice* sgt;
} Vertice;

//estructura que ayuda a contar los triangulos
typedef struct triangulo {
    Vertice* vertice[3];
    struct triangulo* sgt;
} Triangulo;

//prototipo de funciones que se utilizaron en este programa
void liberarmemoriavertices(Vertice* primerVertice);
void liberarmemoriatriangulos(Triangulo* primerTriangulo);
void generartrianguloymostrarcoord(Vertice* primerVertice);
void contartriangulo(Vertice* primerVertice, int numVertices);
void ingresar();
void crearlista(int numVertices);

//cuenta el numero de triangulos que se pueden hacer
int contartriangulos(int numVertices) {
    return numVertices - 3;
}

//se crea un nuevo vertice con memoria dinamica
Vertice* crearvertice(float x, float y, float z) { //se declara a x, y, z como variable tipo flotante para que se puedan agregar variables negativas y/o variables con decimales
    Vertice* nuevoVertice = (Vertice*)malloc(sizeof(Vertice));
    if (nuevoVertice != NULL) {
        nuevoVertice->x = x;
        nuevoVertice->y = y;
        nuevoVertice->z = z;
        nuevoVertice->sgt = NULL;
    }
    return nuevoVertice;
}

//funcion para crear un Triangulo a partir de tres vertices
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

//funcion para liberar la memoria de vertice
void liberarmemoriavertices(Vertice* primerVertice) {
    while (primerVertice != NULL) {
        Vertice* temp = primerVertice;
        primerVertice = primerVertice->sgt;
        free(temp);
    }
}

//funcion para liberar memoria en triangulo
void liberarmemoriatriangulos(Triangulo* primerTriangulo) {
    while (primerTriangulo != NULL) {
        Triangulo* temp = primerTriangulo;
        primerTriangulo = primerTriangulo->sgt;
        free(temp);
    }
}

//funcion para generar triangulos a partir de vertices y muestra sus coordenadas
void generartrianguloymostrarcoord(Vertice* primerVertice) {
    int numVertices = 0;
    Vertice* actualVertice = primerVertice;
    
    //cuenta el numero de vertices
    while (actualVertice != NULL) {
        numVertices++;
        actualVertice = actualVertice->sgt;
    }

    if (numVertices < 3) {
        printf("Los puntos deben ser al menos tres(3), por favor.\n");
        return;
    }
    
    contartriangulo(primerVertice, numVertices);
}

//función para contar triangulos formados a partir de vertices y muestra sus coordenadas
void contartriangulo(Vertice* primerVertice, int numVertices) {
    int numTriangulos = contartriangulos(numVertices);
    printf("El numero de triángulos formados es: %d\n", numTriangulos); //imprime el numero de triangulos que se forman

    //se inicializan los punteros para seguir la lista de vertices y la lista de triangulos.
    Vertice* actualVertice = primerVertice;
    Triangulo* primerTriangulo = NULL;
    Triangulo* ultimoTriangulo = NULL;

    for (int i = 0; i < numTriangulos; i++) {
        Triangulo* nuevoTriangulo = crearTriangulo(actualVertice, actualVertice->sgt, actualVertice->sgt->sgt); //crea un nuevo triangulo utilizando tres vertices consecutivos
        if (nuevoTriangulo == NULL) { //verifica si se pudo crear el triangulo
            printf("Error al crear el triangulo.\n");
            //liberar memoria de triángulos y vértices antes de salir de la función.
            liberarmemoriatriangulos(primerTriangulo);
            liberarmemoriavertices(primerVertice);
            return;
        }

        printf("Triangulo %d: \n Vertices (%.2f, %.2f, %.2f) pertenecen a vertices %d, %d, %d\n",
               i, actualVertice->x, actualVertice->y, actualVertice->z,
               i, (i + 1) % numVertices, (i + 2) % numVertices);

        if (primerTriangulo == NULL) {
            primerTriangulo = nuevoTriangulo;
            ultimoTriangulo = nuevoTriangulo;
        } else {
            ultimoTriangulo->sgt = nuevoTriangulo;
            ultimoTriangulo = nuevoTriangulo;
        }

        actualVertice = actualVertice->sgt;
    }

    //muestra el ultimo triangulo
    printf("Triangulo %d: \n Vertices (%.2f, %.2f, %.2f) pertenecen a vertices %d, %d, %d\n",
           numTriangulos, actualVertice->x, actualVertice->y, actualVertice->z,
           numTriangulos, (numTriangulos + 1) % numVertices, (numTriangulos + 2) % numVertices);

    liberarmemoriatriangulos(primerTriangulo);
    liberarmemoriavertices(primerVertice);
}

//funcion para ingresar el numero de vertices y crear una lista de vertices
void ingresar() {
    int numVertices;
    printf("Ingrese el numero de vertices que quiere: ");
    scanf("%d", &numVertices);

    if (numVertices < 3) {
        printf("Los puntos deben ser al menos tres(3), por favor.\n");
        return;
    }
    crearlista(numVertices);
}

//funcion para crear una lista de vertices a partir de las coordenadas ingresadas
void crearlista(int numVertices) {
    Vertice* primerVertice = NULL;
    Vertice* ultimoVertice = NULL;

    for (int i = 0; i < numVertices; i++) {
        float x, y, z;
        printf("Ingrese las coordenadas (x, y, z) del vertice %d: ", i);
        scanf("%f %f %f", &x, &y, &z);

        //crea un nuevo vertice utilizando las coordenadas ingresadas
        Vertice* nuevoVertice = crearvertice(x, y, z);

        //verifica si se logro crear el vertice
        if (nuevoVertice == NULL) {
            printf("Error al crear el vertice.\n");
            liberarmemoriavertices(primerVertice); //libera la memoria de vertice antes de salir de la funcion
            return;
        }
        //agrega el nuevo vertice a la lista de vertices
        if (primerVertice == NULL) {
            primerVertice = nuevoVertice;
            ultimoVertice = nuevoVertice;
        } else {
            ultimoVertice->sgt = nuevoVertice;
            ultimoVertice = nuevoVertice;
        }
    }
    generartrianguloymostrarcoord(primerVertice); //llama a la funcion para poder generar el triangulo y muestre las coordenadas
}

int main(int argc, char const *argv[]) {
    ingresar();
    return 0;
}
