#include <GL/glut.h>
//<OpenGL/glut.h>
void display(void);

int main(int argc, char **argv) {
    // Inicializar GLUT
    glutInit(&argc, argv);

    // Definir el modo de visualización: RGB, buffer simple, y habilitar el buffer de profundidad
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    
    // Establecer el tamaño de la ventana
    glutInitWindowSize(500, 500);

    // Establecer la posición inicial de la ventana
    glutInitWindowPosition(100, 100);

    // Crear la ventana con un título
    glutCreateWindow("Mi primer ventanita, jiji.");

    // Definir el color de fondo
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Asignar la función de dibujado
    glutDisplayFunc(display);

    // Iniciar el loop de procesamiento de eventos de GLUT
    glutMainLoop();
    return 0;
}

void display(void) {
    // Limpiar el buffer de color
    glClear(GL_COLOR_BUFFER_BIT);

    // Establecer el color de los objetos a dibujar (rojo)
    glColor3f(1.0, 0.0, 0.0); // función correcta para establecer color en RGB

    // Dibujar líneas
    glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);   // Vértice inicial
        glVertex2f(100.0, 100.0); // Vértice final
        glVertex2f(200.0, 150.0);
        glVertex2f(200.0, 250.0);
    glEnd();

    // Dibujar triángulos
    glBegin(GL_TRIANGLES);
        glVertex2f(15.0, 20.0);  // Vértice 1
        glVertex2f(100.0, 100.0); // Vértice 2
        glVertex2f(200.0, 150.0); // Vértice 3
    glEnd();

    // Forzar la ejecución de todas las operaciones GL
    glFlush();
}
