#include <GL/glut.h>

void display(void); // Prototipo de la función

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(200, 200);
  glutCreateWindow("Dibujo de una caja");

  glClearColor(1.0, 1.0, 1.0, 0.0);

  glutDisplayFunc(display);
  glutMainLoop();

  return 0;
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0, 0.0, 1.0); // Color morado (RGB: 1.0, 0.0, 1.0)

  glBegin(GL_LINE_LOOP);

  // Cara frontal
  glVertex3f(300, 0, 200);  // v0
  glVertex3f(0, 0, 200);    // v1
  glVertex3f(0, 200, 200);  // v2
  glVertex3f(300, 200, 200);  // v3

  glEnd();

  glBegin(GL_LINE_LOOP);

  // Cara trasera
  glVertex3f(300, 200, 0);  // v4
  glVertex3f(0, 200, 0);    // v5
  glVertex3f(0, 0, 0);      // v6
  glVertex3f(300, 0, 0);    // Repetimos v0 para cerrar la caja

  glEnd();

  // Conectar las caras frontal y trasera
  glBegin(GL_LINES);
  glVertex3f(300, 0, 200);  // v0
  glVertex3f(300, 0, 0);    // v4

  glVertex3f(0, 0, 200);    // v1
  glVertex3f(0, 0, 0);      // v6

  glVertex3f(0, 200, 200);  // v2
  glVertex3f(0, 200, 0);    // v5

  glVertex3f(300, 200, 200);  // v3
  glVertex3f(300, 200, 0);    // v3

  glEnd();

  glutSwapBuffers();
}
