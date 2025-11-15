//OpenGL, GLUT (freeGLUT)
//glutInit->Inicializar las bibliotecas de glut
//glutCreateWindow->Crear ventana de visualización
//gcc -o .\Pentagono.exe .\Pentagono.c -lfreeglut -lopengl32
//glViewport
//glMatrixMode
//gluOrtho2D

#include <GL/glut.h>
#include <GL/gl.h>
double variable=0.0;

static void display(void);
static void keyboard01(unsigned char key, int x, int y);
static void reshape01(int w,int h);
static void init01(void);


int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   //Función para desplgar de diferente manera (single, double)

    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Movimiento");
    init01();
    glutDisplayFunc(display);//Función que desplega las funciones
    glutReshapeFunc(reshape01);
    glutKeyboardFunc(keyboard01);
    glutMainLoop();

    return 0;
}
//static, para que no se pueda utilizar por otras (?) solo se puede utilizar en ese proyecto


static void init01(void)
{
    glClearColor(1 ,1, 1, 0);
    glShadeModel(GL_FLAT);
}

static void reshape01(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
}

static void keyboard01(unsigned char key, int x, int y)
{
    if ((key==0x1b)||(key=='q')||(key=='Q'))
        exit(0);
    else
        if((key=='R')||(key=='r'))//rotar
        {
            variable +=10;
        }

    if ((key==0x1b)||(key=='q')||(key=='Q'))
        exit(0);
    else
        if((key=='A')||(key=='a'))//rotar
        {
            variable -=10;
        }
    //glLoadIdentity();
    //glutSwapBuffers();
    glutPostRedisplay();//refrescar
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);//Rojo

    glBegin(GL_LINE);
        glVertex2f(0 ,0);
        glVertex2f(0.4 ,-0.2);
    glEnd();

    glutSwapBuffers();//limpiar buffer
}