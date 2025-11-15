#include <GL/glut.h>

double variable =0.0;

//Prototipo función
static void desplegar(void);
static void reshape01(int w, int h);
static void init01(void);
static void keyboard01(unsigned char key, int x, int y);


int main(int argc, char *argv[]) 
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(300, 200);
  glutCreateWindow("Tutorial Linea");
  init01();
  glutDisplayFunc(desplegar);//
  glutReshapeFunc(reshape01);
  glutKeyboardFunc(keyboard01); 
  glutMainLoop();
  return 0;

}

static void desplegar(void)
{

  glClear(GL_COLOR_BUFFER_BIT); //limpiar ventana en el color del clear color definido en glClearColor()
  glColor3f(0,0,0);//Negro
  glPushMatrix();


  //El primer segmento del brazo
  glBegin(GL_LINES); //se define que se dibujaran lineas
    glVertex3f(variable, 250, 0) ; //primer punto para dibujar
    glVertex3f(100,150,0); // segundo punto de la linea
  glEnd();

    glBegin(GL_LINES);
  glVertex3f(variable, 250, 0); // El vértice de la segunda línea es el extremo de la primera
  glVertex3f(150, 150, 0); // Cambia las coordenadas como desees
  glEnd();

  glPopMatrix();
  glutSwapBuffers();

}

// se llama cuando la ventana cambia de tamaño
static void reshape01(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); // Establecer vista
   glMatrixMode (GL_PROJECTION); // Usando la matriz de proyección
   glLoadIdentity (); //y cargandola
   // pantalla completa
   gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

//Valores de inicio
static void init01(void) 
{
   glClearColor (1.0, 1.0, 1.0, 0.0);  // claro a color RGB A
   glShadeModel (GL_FLAT); // El valor default es GL_SMOOTH
}


//Llamado en cada caracter del TECLADO
static void keyboard01(unsigned char key, int x, int y)
{
   if ((key == 0x1b) || (key == 'q') || (key == 'Q'))
      exit(0); // Terminar el programa
   else if (key == 'R' || key == 'r')
   {
      variable += 5; // Girar hacia la derecha
   }
   else if (key == 'L' || key == 'l')
   {
      variable -= 5; // Girar hacia la izquierda
   }
   glutPostRedisplay();
}

