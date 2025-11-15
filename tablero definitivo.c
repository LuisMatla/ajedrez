#include <GL/glut.h>

float rotationAngleX = 0.0;
float rotationAngleY = 0.0;
float rotationAngleZ = 0.0;

void drawCube(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glBegin(GL_QUADS);
    // Define the six faces of the cube
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);

    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);

    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);

    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);

    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    glPopMatrix();
}


void drawChessboard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            float x = i * 1.0;
            float y = j * 1.0;
            float z = 0.0;

            // Alternate the color of the cubes to create a checkerboard pattern
            if ((i + j) % 2 == 0) {
                glColor3f(1.0, 0.75, 0.8); // White
            } else {
                glColor3f(0.5, 0.0, 0.5); // Black
            }

            drawCube(x, y, z);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up the camera
    gluLookAt(5.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(rotationAngleX, 1.0, 0.0, 0.0);
    glRotatef(rotationAngleY, 0.0, 1.0, 0.0);
    glRotatef(rotationAngleZ, 0.0, 0.0, 1.0);

    drawChessboard();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'x':
        case 'X':
            rotationAngleX += 5.0;
            break;
        case 'y':
        case 'Y':
            rotationAngleY += 5.0;
            break;
        case 'z':
        case 'Z':
            rotationAngleZ += 5.0;
            break;
        case 27:  // ESC key
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("Tablero 1");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}