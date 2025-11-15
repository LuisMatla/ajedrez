/*Programa para dibujar dos segmentos giratorios, unidos.*/

//LIBRERÍAS NECESARIAS
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
/*
  -GL_LINES = El par de puntos que corresponden a una línea.
  -GL_POINTS = Dibujar puntos en pantalla, puntos individuales.
  -GL_TRIANGLES = Para dar los tres puntos de un triángulo.
  -GL_LINE_STRIP = Segmentos de líneas conectados.
  -GL_QUADS = Cuatro puntos de un cuadrado.
  -GL_POLYGON = Dibujar un polígono

  glRotatef(eje_x, 1.0, 0.0, 0.0);
  glRotatef(eje_y, 0.0, 1.0, 0.0);
  glRotated
*/
//Vamos a travajar con ROTATE
//VARIABLES GLOBALES
double eje_x = 0.0;
double eje_y = 0.0;
double eje_z = 0.0;

/*double VectorGlobal[4] = {50,100,0,1};//Almacena las coordenadas del extremo del brazo
double VecRot[4] = {200,100,0, 1};
double center[2] = {250,250};//Almacena las coordenadas del centro de rotación del brazo.
*/
//Registro para almacenar un punto y la matriz de transformación
/*typedef struct  {
  double posicion[4];//Para representar la posición del cuerpo en el espacio.
  double matriz[4][4];//Matriz que se utilizará para rotar y trasladar la figura.
}body;

Multiplicacion de una matrix 4x4 por un vector de longitud 4, salida en vector c.
Esta función, así como la de rotar y trasladar, se encargan de las operaciones 
matemáticas necesarias para transformar los vectores al espacio 3D
void Matriz_X_Vector(double matrix[4][4],  double vector[4], double *c)
{
  for (int i = 0; i < 4; i++)
      c[i] = matrix[i][0] * vector[0] +
             matrix[i][1] * vector[1] +
             matrix[i][2] * vector[2] +
             matrix[i][3] * vector[3];
} 

Funcion para rotar el punto definido por el vectorGlobal (X,Y,Z,1) en un angulo angle.
Estamos rotando el  brazo alrededor de la articulación.
void rotar(double *vector, double angle)
{
  double seno = sin(angle);
  double coseno = cos(angle);
  
  double vectortemp[4]; 

  double matrizRot[4][4] = {{coseno, -seno, 0, 0}, //Matriz utilizada para realizar la rotación.
                {seno,  coseno, 0, 0},
                {   0,       0, 1, 0},
                {   0,       0, 0, 1}};

  Matriz_X_Vector(matrizRot,vector,vectortemp);
  
  for(int i=0; i<4; i++)
    vector[i]=vectortemp[i];
}


Funcion para trasladar el vector con salida en el vector vectorout,
es decir, para trasladar el extremo del brazo robótico al centro de 
rotación
void trasladar(double *vector, double *vectorout)
{

  double matrizTras[4][4] = {{1, 0, 0, center[0]},//Matriz utilizada pra realizar la traslación.
                  {0, 1, 0, center[1]},
                  {0, 0, 1, 0},
                  {0, 0, 0, 1}};

  Matriz_X_Vector(matrizTras,vector,vectorout);

}


  Función que inicializa OpenGL
    -Dentro de ella se establece el color de borrado y
    -el sombreado.
*/
static void init01(void) 
{
   glClearColor (1.0, 1.0, 1.0, 0.0);  // clear to color RGB A
   glShadeModel (GL_SMOOTH); // The default value is GL_SMOOTH
}


  /*Función para visualizar.
    -Limpia la pantalla,
    -dibuja los segmentos y
    -actualiza.*/

static void display01(void)
{
  //double vectortemp[4]; 
  //trasladar(VectorGlobal,vectortemp); //Para calcular la posición del brazo, traslada el vector al centro de la ventana.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpiar ventana en el color del clear color definido en glClearColor()
  glLoadIdentity();
  glPushMatrix();
    glRotatef(eje_x, 1.0, 0.0, 0.0);
    glRotatef(eje_y, 0.0, 1.0, 0.0);
    glRotatef(eje_z, 0.0, 0.0, 1.0);

    // Dibuja una esfera en alambre // Desplaza la esfera en alambre
 // Color azul
    glColor3f(0.0, 0.0, 1.0); // Color azul
    glutWireTorus(0.5, 1.5, 30, 30);
  glPopMatrix();
  glFlush (); // el dibujo, no será visible de incio. Use glutSwapBuffers(); if GLUT_DOUBLE
  //glutSwapBuffers(); //el dibujo será visible desde inicio.
  glutPostRedisplay();//refrescar la ventana
}



/*
  Función que ajusta la vista, se llama cuando la ventana cambia de 
  tamaño.
*/
static void reshape01(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); // set view to ALL
   glMatrixMode (GL_PROJECTION); // use PROJECTION matrix
   glLoadIdentity (); // and load it...
   // set to whole screen
   gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);
}

/*
  Función que maneja los eventos de teclado.
*/
static void keyboard01(unsigned char key, int x, int y)
{
   if((key == 0x1b)||(key == 'q')||(key == 'Q'))
      exit(0); // terminar programa
   else
    /*
      KEYS o TECLAS
      -key==GLUT_KEY_LEFT
      -GLUT_KEY_UP
      -GLUT_KEY_DOWN
      -GLUT_KEY_RIGHT
    */
     if ((key=='X') || (key == 'x'))//Rotar, se llama función rotar()
       {
        eje_x+=5;
           /*printf("Vector Inicial %f, %f, %f\n",VectorGlobal[0], VectorGlobal[1],VectorGlobal[2]);
           rotar(VectorGlobal, -.05);
         rotar(VecRot, -.05);

           printf("Vector final %f, %f, %f\n",VectorGlobal[0], VectorGlobal[1],VectorGlobal[2]);*/
       }else if ((key=='Y') || (key == 'y'))
       {
        eje_y+=5;
       }else if ((key=='Z') || (key == 'z'))
       {
        eje_z+=5;
       }
   glutSwapBuffers();//Para intercambiar los buffers de color de la ventana, hace que el dibujo sea visible.
   glutPostRedisplay();//refrescar
}

/* 
  Función principal, en ella:
    -Se establece la configuración del todo,
    -se inicializa GLUT, 
    -se crea la ventana y
    -se mandan llamar las funciones necesarias.
*/
int main(int argc, char *argv[]) {


  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(300, 200);
  glutCreateWindow("TORO 3D");

  //Habilitar la profundidad del z-buffer
  glEnable(GL_DEPTH_TEST);

  init01();

  //Para imprimir la cadena de que se utiliza para los render y la versión de OPENGL
  const GLubyte* renderer = glGetString(GL_RENDERER); //Obtener cadena Render
  const GLubyte* version = glGetString(GL_VERSION); // Obtener cadena versión
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(-5, 5, -5, 5, -5, 5);
  printf("Renderer: %s\n", renderer);
  printf("Versión de OpenGL que soporta: %s\n", version);
  glutDisplayFunc(display01);
  glutReshapeFunc(reshape01);
  glutKeyboardFunc(keyboard01);
  glutMainLoop();
  return 0;
} 