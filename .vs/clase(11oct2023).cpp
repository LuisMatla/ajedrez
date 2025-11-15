/*Nuestro primer ejemplito
OpenGL, GLUT

GLUT es una biblioteca de gráficos, de proposito general, nos permite operaciones de rederizacion de OpenGL

GLUT es multiplataforma, OSX, Windows, Linux

glut -> inicializar las bibliotecas de GUT
glutCreateWindow-> Crear ventana de visualización
*/

#include <GL/glut.h>
//<OpenGL/glut.h>
void display(void);


int main(int argc, char const *argv[]){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB, GLUT_SINGLE, GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Mi primer ventanita, jiji.");

    glClearColor(1.0, 1.0, 1.0, 0.0); //color que se quiere que limpie.
    
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor(1.0, 0.0, 0.0);//rojo
    //glColor(0.0, 0.0, 0.0);//negro

    glBegin(GL_LINES);
        glVertex2f(0.0, 0, 0);
        glVertex2f(100, 100.0, 0);
        glVertex2f(200, 150, 0);
        glVertex2f(200, 250, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(15, 20.0);
        glVertex2f(100, 100.0);
        glVertex2f(200, 150.0);
        //glVertex2f(200, 250.0);
    glEnd();

    glFlush();
}