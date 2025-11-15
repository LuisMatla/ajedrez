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
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);    // Set display window color to black
   glShadeModel (GL_SMOOTH); // The default value is GL_SMOOTH
    glMatrixMode(GL_PROJECTION);        // Set projection parameters
    gluOrtho2D(0.0, 800.0, 0.0, 800.0);
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpiar ventana en el color del clear color definido en glClearColor()
    glLoadIdentity();
    glRotatef(eje_x, 1.0, 0.0, 0.0);
    glRotatef(eje_y, 0.0, 1.0, 0.0);
    glRotatef(eje_z, 0.0, 0.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT);    // Clear display window
    int f = 0;
    for (int x = 0; x <= 800; x += 100) {
        for (int y = 0; y <= 800; y += 100) {
            if (f) {
                glColor3f(1.0, 1.0, 1.0);
                f = 0;
            }
            else {
                glColor3f(0.0, 0.0, 0.0);
                f = 1;
            }
            glBegin(GL_QUADS);
            glVertex2i(x, y);
            glVertex2i(x, y + 100);
            glVertex2i(x + 100, y + 100);
            glVertex2i(x + 100, y);
            glEnd();
        }
    }

    glFlush();    // Process all OpenGL routines
}

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

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);                            // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // Set display mode

    glutInitWindowPosition(300, 50);                // Set window position
    glutInitWindowSize(800, 800);                    // Set window size
    glutCreateWindow("chess-board"); 
      //Habilitar la profundidad del z-buffer
  glEnable(GL_DEPTH_TEST);               // Create display window
    init();                            // Execute initialization procedure
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
