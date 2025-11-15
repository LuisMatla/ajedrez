#include <GL/glut.h>

// Variables para el control de la cámara
float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 5.0f;

// Función de inicialización
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

// Función de dibujo
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Configura la matriz de vista para la cámara
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Dibuja tu figura aquí
    glutWireCube(1.0);

    glutSwapBuffers();
}

// Función de redimensionamiento de la ventana
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Función de manejo de teclas especiales (para controlar la cámara)
void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        cameraX -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        cameraX += 0.1f;
        break;
    case GLUT_KEY_UP:
        cameraY += 0.1f;
        break;
    case GLUT_KEY_DOWN:
        cameraY -= 0.1f;
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("OpenGL Camera Example");
    glutInitWindowSize(800, 600);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);

    init();

    glutMainLoop();
    return 0;
}
