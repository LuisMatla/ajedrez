#include <stdio.h>
#include <math.h>

// Definición de las estructuras.
typedef struct esfera{
    float equis;
    float ye;
    float zeta;
    float tot;
} Esfera;

typedef struct centro{
    float h;
    float k;
    float l;
} Centro;

// Prototipos de funciones.
void bienvenida();
void valores(Esfera *esfera);
void muestra_ecuacion(Esfera esfera);
Centro calcular_centro(Esfera e);
float calcular_radio(Esfera e, Centro centro);
Esfera calcular_ecuacion(Centro centro, float radio);
void dar_centro_y_radio(Centro *centro, float *radio);

void valores(Esfera *esfera) {
    printf("Ingresa el valor de tu x:\n");
    scanf("%f", &esfera->equis);
    printf("Ingresa el valor de tu y:\n");
    scanf("%f", &esfera->ye);
    printf("Ingresa el valor de tu z:\n");
    scanf("%f", &esfera->zeta);
    printf("Ingrese el valor total:\n");
    scanf("%f", &esfera->tot);
}// Función para ingresar valores de la ecuación de la esfera.


void muestra_ecuacion(Esfera esfera) {
    printf("La ecuación es la siguiente:\n");
    printf("x^2 + y^2 + z^2 + (%.0f)x + (%.0f)y + (%.0f)z = %.0f.\n", esfera.equis, esfera.ye, esfera.zeta, esfera.tot);
}// Función para mostrar la ecuación de la esfera.

Centro calcular_centro(Esfera e) {
    Centro centro;
    centro.h = -e.equis / 2.0;
    centro.k = -e.ye / 2.0;
    centro.l = -e.zeta / 2.0;
    printf("Centro: (%.1f, %.1f, %.1f).\n", centro.h, centro.k, centro.l);
    return centro;
}// Función para calcular el centro de la esfera.

float calcular_radio(Esfera e, Centro centro) {
    float a = -e.tot;
    float r = sqrt(centro.h * centro.h + centro.k * centro.k + centro.l * centro.l - a);
    printf("Radio: %.1f.\n", r);
    return r;
}// Función para calcular el radio de la esfera.

Esfera calcular_ecuacion(Centro centro, float radio) {
    Esfera esfera;
    esfera.equis = -2.0 * centro.h;
    esfera.ye = -2.0 * centro.k;
    esfera.zeta = -2.0 * centro.l;
    esfera.tot = centro.h * centro.h + centro.k * centro.k + centro.l * centro.l - radio * radio;
    esfera.tot = fabs(esfera.tot);
    return esfera;
}// Función para calcular la ecuación de la esfera a partir de h, k, l y r.

void dar_centro_y_radio(Centro *centro, float *radio) {
    printf("Ingresa el valor de h (centro x):\n");
    scanf("%f", &centro->h);
    printf("Ingresa el valor de k (centro y):\n");
    scanf("%f", &centro->k);
    printf("Ingresa el valor de l (centro z):\n");
    scanf("%f", &centro->l);
    printf("Ingresa el valor del radio:\n");
    scanf("%f", radio);
}// Función para ingresar el centro y el radio de la esfera.

void bienvenida() {
    printf("Bienvenid@ a este programa. El cual tiene dos opciones:\n");
}// Función para mostrar un mensaje de bienvenida.

void menu() {
    int opcion;
    
    do {
        Esfera esfera;
        Centro centro;
        float radio;
        
        bienvenida();
        
        printf("Seleccione una de las siguientes opciones:\n");
        printf("[1] Ingresar los valores de su ecuacion.\n");
        printf("[2] Ingresar el centro y radio.\n");
        printf("[3] Salir del programa.\n");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                valores(&esfera);
                muestra_ecuacion(esfera);
                centro = calcular_centro(esfera);
                radio = calcular_radio(esfera, centro);
                break;
            case 2:
                dar_centro_y_radio(&centro, &radio);
                esfera = calcular_ecuacion(centro, radio);
                muestra_ecuacion(esfera);
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 3);
}

int main(int argc, char const *argv[]) {
    menu();
    return 0;
}