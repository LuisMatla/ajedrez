//Contreras Matla Luis Fernando S21020225.
/*
Programa sencillo:
Imprimir un triángulo con *
Desde consola, le debeos decir la altura
*/

#include<stdio.h>
#include <stdlib.h> //esto es para que el atoi nos sirva

void dibujar_triangulo(int *alt) {
   //int i, j; declara e inicializa dentro del for, excepto si es DevC++
   if(*alt<=1){ //indica el valor que se está guardando en la memoria
        puts("Altura debe ser mayor a uno(1), por favor.");
    } else {
        for (int i = 0; i < *alt; i++) {
            for (int j = 0; j < *alt - i - 1; j++) {
                printf(" ");
            }
            for (int k = 0; k < 2 * i + 1; k++) {
                printf("*");
            }
            printf("\n");
        }
    }
}
int main(int argc, char const* argv[]){
	int alt;
	//utilizamos argc y argv[0]
	if(argc !=2){
		printf("Formato esperado %s:  altura\n", argv[0]); //esto ayuda para que nos de 
		return 1;
	}
	alt=atoi(argv[1]);//convertir un caracter a entero

	//Imprimir al usuario el formato
	dibujar_triangulo(&alt);
	return 0;
}


