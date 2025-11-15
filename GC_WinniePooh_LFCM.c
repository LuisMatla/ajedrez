/*
    Contreras Matla Luis Fernando
    S21020225
*/

#include <GL/glut.h>
#include <math.h>

void dibujarCirculo(float x, float y, float radio) {
    const float PI = 3.14159265359; // Definimos PI como una constante.
    int tamanio = 100; // Número de lados del polígono (para simular un círculo).

    glBegin(GL_POLYGON); // Iniciamos un nuevo polígono en OpenGL.

    for (int i = 0; i < tamanio; i++) { // Iniciamos un bucle para calcular los vértices del polígono (en este caso, los puntos del círculo).
        float theta = 2.0f * PI * (float)i / tamanio; // Calculamos el ángulo "theta" para el vértice actual.
        float cx = x + radio * cos(theta); // Calculamos la coordenada x del vértice actual del círculo.
        float cy = y + radio * sin(theta); // Calculamos la coordenada y del vértice actual del círculo.
        glVertex3f(cx, cy, 0.0); // Definimos un vértice en las coordenadas (cx, cy, 0.0).
    }

    glEnd(); // Finalizamos el polígono en OpenGL.
}



void dibujarCirculoConContorno(float cx, float cy, float r, float lineWidth) {
    
    int num_segmentos = 100; //declarar el número de segmentos que se utilizarán para aproximar el círculo.
    float theta = 2.0f * 3.1415926f / num_segmentos; //calcular el ángulo entre cada segmento del círculo.
    
    //Calcular el coseno y el seno de theta, que se utilizarán en las rotaciones.
    float cos_theta = cosf(theta);
    float sin_theta = sinf(theta);
    
    //Inicializar las coordenadas iniciales del primer punto en el círculo.
    float x = r;
    float y = 0.0;

    //Establecer el ancho de línea para el contorno.
    glLineWidth(lineWidth);
    glBegin(GL_LINE_LOOP);

    //Iterar a través de los segmentos para dibujar el círculo.
    for (int i = 0; i < num_segmentos; i++) {
        glVertex2f(x + cx, y + cy);// agregar el punto actual al bucle de línea en OpenGL.
        //Calcular las nuevas coordenadas (x, y) para el siguiente punto.
        float new_x = x * cos_theta - y * sin_theta;
        y = x * sin_theta + y * cos_theta;
        x = new_x;
    }

    // Finalizar el bucle de línea en OpenGL.
    glEnd();

    // Restaurar el ancho de línea a 1.0 (valor predeterminado).
    glLineWidth(1.0);
}


void dibujarOso() {
    glClear(GL_COLOR_BUFFER_BIT);

    //Cuerpo del oso (círculo).
    glColor3f(1.0, 1.0, 0.0); //amarillo
    dibujarCirculo(0.0, -0.4, 0.3);

    //Contorno del cuerpo del oso (círculo).
    glColor3f(0.0, 0.0, 0.0); //negro
    dibujarCirculoConContorno(0.0, -0.4, 0.3, 0.02); 

    //Orejas (círculos).
    glColor3f(1.0, 1.0, 0.0); //amarillo
    dibujarCirculo(-0.15, 0.2, 0.1); //oreja izquierda
    dibujarCirculo(0.15, 0.2, 0.1);  //oreja derecha.

    //Contorno de las orejas (círculos).
    glColor3f(0.0, 0.0, 0.0); //negro
    dibujarCirculoConContorno(-0.15, 0.2, 0.1, 0.02); //mano izquierda
    dibujarCirculoConContorno(0.15, 0.2, 0.1, 0.02);  //mano derecha

    //Cabeza del oso (círculo).
    glColor3f(1.0, 1.0, 0.0); 
    dibujarCirculo(0.0, 0.0, 0.2);

    //Contorno de la cabeza del oso (círculo).
    glColor3f(0.0, 0.0, 0.0); //negro
    dibujarCirculoConContorno(0.0, 0.0, 0.2, 0.02);

    //Ojos (círculos pequeños).
    glColor3f(0.0, 0.0, 0.0); //negro
    dibujarCirculo(-0.08, 0.07, 0.02); //ojo izquierdo
    dibujarCirculo(0.08, 0.07, 0.02); //ojo derecho

    //Nariz (triángulo invertido).
    glColor3f(0.0, 0.0, 0.0); //negro
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, -0.07, 0.0); //vértice superior
    glVertex3f(-0.05, -0.01, 0.0); //vértice inferior izquierdo
    glVertex3f(0.05, -0.01, 0.0); //vértice inferior derecho
    glEnd();

    //Boca (línea).
    glLineWidth(2.0); //ancho de línea
    glBegin(GL_LINES);
    glVertex3f(-0.05, -0.15, 0.0);
    glVertex3f(0.05, -0.15, 0.0);
    glEnd();
    glLineWidth(1.0); //restaurar el ancho de línea

    //Interior de las orejas (círculos).
    glColor3f(0.0, 0.0, 0.0); //negro
    dibujarCirculoConContorno(-0.15, 0.2, 0.05, 0.02); //Mano izquierda
    dibujarCirculoConContorno(0.15, 0.2, 0.05, 0.02);  //Mano derecha

    //Interior de las orejas (círculos)
    glColor3f(1.0, 0.5, 0.0); //naranja
    dibujarCirculo(-0.15, 0.2, 0.05); //oreja izquierda
    dibujarCirculo(0.15, 0.2, 0.05);  //oreja derecha

    //Agregar la camisa roja (parte inferior)
    glColor3f(1.0, 0.0, 0.0); //rojo
    glBegin(GL_POLYGON);
    glVertex3f(-0.35, -0.4, 0.0); //esquina inferior izquierda
    glVertex3f(0.35, -0.4, 0.0);  //esquina inferior derecha
    glVertex3f(0.3, -0.25, 0.0);   //esquina superior derecha
    glVertex3f(-0.3, -0.25, 0.0);  //esquina superior izquierda
    glEnd();

    //Manos (círculos).
    glColor3f(1.0, 1.0, 0.0); //naranja
    dibujarCirculo(-0.25, -0.2, 0.1); //mano izquierda
    dibujarCirculo(0.25, -0.2, 0.1); //mano derecha

    //Piernas (círculos).
    glColor3f(1.0, 1.0, 0.0);  //naranja
    dibujarCirculo(-0.15, -0.65, 0.1); //pierna izquierda
    dibujarCirculo(0.15, -0.65, 0.1);  //pierna derecha

    //Manos (círculos) con contorno negro.
    glColor3f(0.0, 0.0, 0.0); //negro
    dibujarCirculoConContorno(-0.25, -0.2, 0.1, 0.02); //mano izquierda
    dibujarCirculoConContorno(0.25, -0.2, 0.1, 0.02);  //mano derecha

    //Piernas (círculos) con contorno negro.
    dibujarCirculoConContorno(-0.15, -0.65, 0.1, 0.02); //pierna izquierda
    dibujarCirculoConContorno(0.15, -0.65, 0.1, 0.02);  //pierna derecha
    glFlush();
}

void inicializar() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Winnie Pooh");

    inicializar();

    glutDisplayFunc(dibujarOso);

    glutMainLoop();

    return 0;
}
