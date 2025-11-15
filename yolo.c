//OpenGL, GLUT (freeGLUT)
//glutInit->Inicializar las bibliotecas de glut
//glutCreateWindow->Crear ventana de visualización
#include <GL/glut.h>
#include <GL/gl.h>

void display(void);
int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);   //Función para desplgar de diferente manera (single, double)

    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Mi primer ventanita");

    //glClearColor(1.0 ,1.0, 1.0, 0.0);

    glutDisplayFunc(display);//Función que desplega las funciones

    glutMainLoop();

    return 0;
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);//Rojo
    //glColor3f(0.0 ,0.0, 0.0);//Negro

    /*glBegin(GL_LINE_LOOP);
        glVertex2f(0.0,0.0);
        glVertex2f(100.0,100.0);
        glVertex2f(200.0,150.0);
        glVertex2f(0.0,200.0);
    glEnd();*/

    glBegin(GL_TRIANGLES);
        glVertex3f(0.0 ,0.0, 0.0);
        glVertex3f(100.0 ,150.0, 0.0);
        glVertex3f(200.0 ,150.0, 0.0);
        //glVertex3f(150.0,250.0,0.0);
    glEnd();

    glFlush();//limpiar buffer
}