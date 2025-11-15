#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Establecer el color del texto (por ejemplo, blanco)
    glColor3f(1.0, 1.0, 1.0);

    // Establecer la posición del texto (por ejemplo, en la esquina inferior izquierda)
    glRasterPos2f(-0.9, -0.9);

    // Imprimir el texto usando glutBitmapCharacter
    char text[] = "Hola, OpenGL!";
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL Texto");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
