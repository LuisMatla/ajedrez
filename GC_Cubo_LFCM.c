//Contreras Matla Luis Fernando

#include <GL/glut.h>

// Prototipos de funciones
static void desplegar(void);
static void init01(void);
static void reshape01(int w, int h);

int main(int argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("Dibujo de caja");

    init01();
    glutDisplayFunc(desplegar);
    glutReshapeFunc(reshape01);
    glutMainLoop();
    return 0;
}

static void init01(void) 
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Establecer el color de fondo a blanco
    glShadeModel(GL_FLAT);
}

static void reshape01(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h); // Establecer vista
    glMatrixMode(GL_PROJECTION); // Usando la matriz de proyección
    glLoadIdentity(); // y cargándola
    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

static void desplegar(void) 
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpiar ventana en el color del clear color definido en glClearColor() 
    glColor3f(0.5, 0, 0.5);

    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5, -0.5, 0.5);//esquina inferior izquierda
    glVertex3f(0.5, -0.5, 0.5);//esquina inferior derecha
    glVertex3f(0.5, 0.5, 0.5);//essquina superior derecha
    glVertex3f(-0.5, 0.5, 0.5);//esquina superior izquierda
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.25, -0.25, 0.25);//nueva esquina inferior izquierda
    glVertex3f(0.75, -0.25, 0.25);//nueva esquina inferior derecha
    glVertex3f(0.75, 0.75, 0.25);//nueva esquina superior derecha
    glVertex3f(-0.25, 0.75, 0.25);//nueva esquina superior izquierda
    glEnd();

    glBegin(GL_LINES); 
    //conexion esquina inferior izquierda
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.25, -0.25, 0.25);
    //conexion esquina inferior derecha
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.75, -0.25, 0.25);
    //conexion esquina superior derecha
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.75, 0.75, 0.25); 
    //conexion esquina superior izquierda
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.25, 0.75, 0.25);
    glEnd();
    glutSwapBuffers();
}

