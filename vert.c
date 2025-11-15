
#include <stdio.h>
#include <stdlib.h>

//Se define la estructura para el vertice.
typedef struct nodo{
	float x, y, z;
	struct nodo * sgt;
}Vertices;

//Estructura para contar los triangulos.
typedef struct nodo{
    struct Vertices* vertice[3];
    struct Nodo*sgt;
}Triangulo;


Vertices* crearVertice(float x, float y, float z){
	Vertices* nuevoVertice = (Vertices*)malloc(sizeof(Vertices));
    if(nuevoVertice != NULL){
		nuevoVetice->x=x;
		nuevoVetice->y=y;
		nuevoVetice->z=z;
		nuevoVetice->next=NULL;
	}
	return nuevoVertice;
}

Triangulo* crearTriangulo(Vertices* v1, Vertices* v2, Vertices* v3){
	Triangulo* nuevoTriangulo = (Triangulo*)malloc(sizeof(Triangulo));
    if(nuevoTriangulo != NULL){
		nuevoTriangulo->vertice[0]=v1;
		nuevoTriangulo->vertice[1]=v2;
		nuevoTriangulo->vertice[2]=v3;
		nuevoTriangulo->next=NULL;
	}
	return nuevoTriangulo;
}

void vert(int *Vertices) {
   //int i, j; declara e inicializa dentro del for, excepto si es DevC++
   if(*Vertices < 3){ //indica el valor que se está guardando en la memoria
        puts("Los puntos deben ser mayor a tres(3), por favor.");
		return 1;
    } else {
		for(i = 0; i < *Vertices: i++){
			printf("Ingrese el número de vértices que quiere: \n");
			scanf("d", &numVertices);
		}
	}
}
void crearlista(*Vertices){
	vert(int *Vertices);
	Vertices* primerVertice=NULL;
	Vertices* ultimoVertice=NULL;

	for (int i=0; i < numVertices;i++ ){
		float x
	}
}

   