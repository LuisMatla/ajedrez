#include <stdio.h>
#include <math.h>

void calcularCentroYRadio() {
    float h, k, l, r; //declaramos flotante h, k y l, también r para el radio.

    float X = 1.0, Y = 1.0, Z = 1.0, A = -6.0, B = -4.0, C = 2.0, D = -2.0;
    
    // Calcular el centro
    h = -A / (2.0 * X);
    k = -B / (2.0 * Y);
    l = -C / (2.0 * Z);
    
    // Calcular el radio
    r = (h*h + k*k + l*l - D);
    
    printf("Centro: (%.2lf, %.2lf, %.2lf)\n", h, k, l);
    printf("Radio: %.2lf\n", r);
}

int main() {
    printf("Bienvenid@ a este programa. El cual te va a encontrar el radio");
    printf ("centro de una esfera, cuya ecuacion es la siguiente:\n");
    printf("x^2 + y^2 + z^2 - 6x - 4y + 2z = 2.\n");
    
    calcularCentroYRadio();
    
    return 0;
}
