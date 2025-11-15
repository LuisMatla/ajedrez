/*
Contreras Matla Luis Fernando
S21020225
INSTRUCCIONES
	-En C, utilizando OpenGL.
	-Menú:
		-Dibujar una figura:
			-Triángulo.
			-Cuadrado.
			-Prisma triángular.
			-Cubo.
		-Colores:
			-Amarillo.
			-Rojo.
			-Verde.
			-Azul.
			-Morado.
		-Movimiento.
			-Moverse en los ejes x, y, z.
		-Keyboard.
			-Utilizarla para el cambio de color.
		-SpecialKeys, Flechas (key, x, y,z).
			-GLUT_RIGHT.
				eje_x+=5;
			-GLUT_KEY_LEFT.
				eje_y+=5;
			-GLUT_KEY_DOWN
				-Terminar
PASARLO COMO ARGUMENTOS
Primero el usuario decide que quiere y ya despues desde consola se manda a llamar la figura.
*/

//Librerías que se utilizaron.
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

//Variables para el control de las figuras, colores y movimiento.
int figuraSeleccionada = 0; //0: ninguna figura seleccionada.
int colorSeleccionado = 0;  //0: ningún color seleccionado.
float eje_x = 0.0;
float eje_y = 0.0;
float eje_z = 0.0;
float eje_w = 0.0;
float eje_a = 0.0;
float eje_d = 0.0;
float cameraX = 0.0;
float cameraY = 0.0;
float cameraZ = 5.0;

//Declaramos las funciones globales.
void texto_triangulo();
void texto_cuadrado();
void texto_prisma();
void texto_cubo();
void contorno_triangulo();
void dibujarTriangulo();
void contorno_cuadrado();
void dibujarCuadrado();
void contorno_prisma_triangulo1();
void contorno_prisma_triangulo2();
void contorno_prisma_cuadrado1();
void contorno_prisma_cuadrado2();
void contorno_prisma_cuadrado3();
void dibujarPrismaTriangular();
void contorno_carafrontal();
void contorno_caratrasera();
void contorno_conectando();
void dibujarCubo();
static void reshape01();
void reshape02();
void setColorActual();
void display();
void specialKeys(int key, int x, int y);
void menu(int value);
void movimientoMenu(unsigned char key, int x, int y);
void rotarfigura(unsigned char key, int w, int a, int d);
void movercamara(int key, int x, int y);
void movimientos(unsigned char key, int x, int y);
static void init01();

//Función para agregar la palabra triángulo.
void texto_triangulo(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); //blanco.
    glRasterPos2f(-1.7, -1.7); //posición del texto.
    char text[] = "Triangulo"; //declaramos una cadena de caracteres para el texto.
    for (int i = 0; text[i] != '\0'; i++) { //iteramos a través de cada carácter de la cadena hasta llegar al carácter nulo '\0'.
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);//utilizamos la función glutBitmapCharacter para renderizar cada carácter en la posición actual.
}
    glFlush();
}

//Función para agregar la palabra cuadrado.
void texto_cuadrado(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); //blanco.
    glRasterPos2f(-1.7, -1.7); //posición del texto.
    char text[] = "Cuadrado"; //declaramos una cadena de caracteres para el texto.
    for (int i = 0; text[i] != '\0'; i++) { //iteramos a través de cada carácter de la cadena hasta llegar al carácter nulo '\0'.
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);//utilizamos la función glutBitmapCharacter para renderizar cada carácter en la posición actual.
}
    glFlush();
}

//Función para agregar la palabra prisma triangular.
void texto_prisma(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); //blanco.
    glRasterPos2f(-1.7, -1.7); //posición del texto.
    char text[] = "Prisma triangular"; //declaramos una cadena de caracteres para el texto.
    for (int i = 0; text[i] != '\0'; i++) { //iteramos a través de cada carácter de la cadena hasta llegar al carácter nulo '\0'.
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);//utilizamos la función glutBitmapCharacter para renderizar cada carácter en la posición actual.
}
    glFlush();
}

//Función para agregar la palabra cubo.
void texto_cubo(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); //blanco.
    glRasterPos2f(-1.7, -1.7); //posición del texto.
    char text[] = "Cubo"; //declaramos una cadena de caracteres para el texto.
    for (int i = 0; text[i] != '\0'; i++) { //iteramos a través de cada carácter de la cadena hasta llegar al carácter nulo '\0'.
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);//utilizamos la función glutBitmapCharacter para renderizar cada carácter en la posición actual.
}
    glFlush();
}

//Función para dibujar el contorno de un triángulo.   
void contorno_triangulo() {
    glColor3f(0.0, 1.0, 1.0); //cyan.
    glLineWidth(5.0); //se establece el ancho del contorno.

    //Dibujar el contorno del triángulo.
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.0, 1.0, 0.0); //vértice inferior izquierdo.
    glVertex3f(-1.5, -1.0, 0.0); //vértice inferior derecho.
    glVertex3f(1.5, -1.0, 0.0); //vértice superior.
    glEnd();
    glLineWidth(1.0); //restaurar el ancho de línea y el color.
}

//Función para dibujar un triángulo.
void dibujarTriangulo() {
    setColorActual(); //establecemos el color actual.

    //Dibujamos el triángulo
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 1.0, 0.0); //vértice inferior izquierdo.
    glVertex3f(-1.5, -1.0, 0.0); //vértice inferior derecho.
    glVertex3f(1.5, -1.0, 0.0); //vértice superior.
    glEnd();
    contorno_triangulo(); //llamamos esta función después que se dibuje el triangulo porque si no, no se logra cambiar de color la figura.
}

//Función para dibujar el contorno de un cuadrado.
void contorno_cuadrado() {
    glColor3f(0.0, 1.0, 1.0); //cyan.
    glLineWidth(5.0); //se establece el ancho del contorno.

    //Dibujar el contorno del cuadrado.
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0, -1.0, 0.0); //esquina inferior izquierda.
    glVertex3f(1.0, -1.0, 0.0);  //esquina inferior derecha.
    glVertex3f(1.0, 1.0, 0.0);   //esquina superior derecha.
    glVertex3f(-1.0, 1.0, 0.0);  //esquina superior izquierda.
    glEnd();
    glLineWidth(1.0); //restaurar el ancho de línea y el color.
}

//Función para dibujar un cuadrado.
void dibujarCuadrado() {
    setColorActual(); //establecemos el color actual.

    //Dibujamos el cuadrado.
    glBegin(GL_QUADS);
    glVertex3f(-1.0, -1.0, 0.0); //esquina inferior izquierda.
    glVertex3f(1.0, -1.0, 0.0);  //esquina inferior derecha.
    glVertex3f(1.0, 1.0, 0.0);   //esquina superior derecha.
    glVertex3f(-1.0, 1.0, 0.0);  //esquina superior izquierda.
    glEnd();
    contorno_cuadrado(); //llamamos esta función después que se dibuje el triangulo porque si no, no se logra cambiar de color la figura.
}

//Función para dibujar el contorno del primer triángulo del prisma.
void contorno_prisma_triangulo1() {
    glColor3f(0.0, 1.0, 1.0); //cyan.
    glLineWidth(5.0); //se establece el ancho del contorno.
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0, 0.0, -1.0); //vértice inferior izquierdo.
    glVertex3f(0.0, 0.0, 0.73); //vértice inferior derecho.
    glVertex3f(1.0, 0.0, -1.0); //vértice superior.
    glEnd();
    glLineWidth(1.0); //restaurar el ancho de línea y el color.
}

//Función para dibujar el contorno del segundo triángulo del prisma.
void contorno_prisma_triangulo2() {
    glColor3f(0.0, 1.0, 1.0);  //cyan.
    glLineWidth(5.0); //se establece el ancho del contorno.
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0, 3.5, -1.0); //vértice inferior izquierdo.
    glVertex3f(0.0, 3.5, 0.73); //vértice inferior derecho.
    glVertex3f(1.0, 3.5, -1.0); //vértice superior.
    glEnd();
    glLineWidth(1.0); //restaurar el ancho de línea y el color.

}

//Función para dibujar el primer rectángulo que hace la unión de los lados de los triángulos.
void contorno_prisma_rectangulo1() {
    glColor3f(0.0, 1.0, 1.0);  //cyan.
    glLineWidth(5.0); //se establece el ancho del contorno.

    //Trazamos la primera línea.
    glBegin(GL_LINES);
    glVertex3f(0.0, 3.5, 0.73); //vértice inferior derecho del segundo triángulo.
    glVertex3f(0.0, 0.0, 0.73); //vértice inferior derecho del primer triángulo.

    //Trazamos la segunda línea.
    glBegin(GL_LINES);
    glVertex3f(-1.0, 0.0, -1.0); //vértice inferior izquierdo del primer triángulo.
    glVertex3f(-1.0, 3.5, -1.0); //vértice inferior izquierdo del segundo triángulo.
    glEnd();
    glLineWidth(1.0); //restaurar el ancho de línea y el color.
}

//Función para dibujar el segundo rectángulo que hace la unión de los lados de los triángulos.
void contorno_prisma_rectangulo2() {
    glColor3f(0.0, 1.0, 1.0);  //cyan.
    glLineWidth(5.0); //se establece el ancho del contorno.

    //Trazamos la primera línea.   
    glBegin(GL_LINES);
    glVertex3f(-1.0, 0.0, -1.0); //vértice inferior izquierdo del primer triángulo.
    glVertex3f(-1.0, 3.5, -1.0); //vértice inferior izquierdo del primer triángulo.

    //Trazamos la segunda línea.
    glBegin(GL_LINES);
    glVertex3f(1.0, 3.5, -1.0); //vértice superior del segundo triángulo.
    glVertex3f(1.0, 0.0, -1.0); //vértice superior del primer triángulo.
    glEnd();
    glLineWidth(1.0); //restaurar el ancho de línea y el color.
}

// Función para dibujar un prisma triangular
void dibujarPrismaTriangular() {
    setColorActual(); //establecemos el color actual.

    //Dibujamos el triángulo
	glBegin(GL_TRIANGLES);
    glVertex3f(-1.0, 0.0, -1.0); //vértice inferior izquierdo.
    glVertex3f(0.0, 0.0, 0.73); //vértice inferior derecho.
    glVertex3f(1.0, 0.0, -1.0); //vértice superior.
    glEnd();
    contorno_prisma_triangulo1(); //llamamos esta función después que se dibuje el triangulo porque si no, no se logra cambiar de color la figura.

    setColorActual();
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0, 3.5, -1.0); //vértice inferior izquierdo.
    glVertex3f(0.0, 3.5, 0.73); //vértice inferior derecho.
    glVertex3f(1.0, 3.5, -1.0); //vértice superior.
    glEnd();
    contorno_prisma_triangulo2(); //llamamos esta función después que se dibuje el triangulo porque si no, no se logra cambiar de color la figura.

    setColorActual();
    glBegin(GL_QUADS);
    glVertex3f(-1.0, 0.0, -1.0); //esquina inferior izquierda
    glVertex3f(0.0, 0.0, 0.73); //esquina inferior derecha
    glVertex3f(0.0, 3.5, 0.73); //esquina superior izquierda.
    glVertex3f(-1.0, 3.5, -1.0); //esquina superior derecha.
    glEnd();
    contorno_prisma_rectangulo1(); //llamamos esta función después que se dibuje el triangulo porque si no, no se logra cambiar de color la figura.

    setColorActual();
    glBegin(GL_QUADS);
    glVertex3f(-1.0, 0.0, -1.0); //esquina inferior izquierda.
    glVertex3f(1.0, 0.0, -1.0); //esquina inferior derecha.
    glVertex3f(1.0, 3.5, -1.0); //esquina superior derecha.
    glVertex3f(-1.0, 3.5, -1.0); //esquina superior izquierda.
    glEnd();
    contorno_prisma_rectangulo2(); //llamamos esta función después que se dibuje el triangulo porque si no, no se logra cambiar de color la figura.

    setColorActual();
    glBegin(GL_QUADS);
    glVertex3f(-1.0, 0.0, -1.0); //esquina inferior izquierda.
    glVertex3f(0.0, 0.0, 0.73); //esquina inferior derecha.
    glVertex3f(1.0, 3.5, -1.0); //esquina superior derecha.
    glVertex3f(0.0, 3.5, 0.73); //esquina superior izquierda.
    glEnd();
}

//Función para dibujar el controno de la cara frontal del cubo.
void contorno_carafrontal(){
    glColor3f(0.0, 1.0, 1.0); //cyan.
    glLineWidth(5.0); //se establece el ancho del contorno.
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();
    glLineWidth(1.0); //restaurar el ancho de línea y el color.
}

//Función para dibujar el controno de la cara trasera del cubo.
void contorno_caratrasera(){
    glColor3f(0.0, 1.0, 1.0);  //cyan.
    glLineWidth(5.0); //se establece el ancho del contorno.
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0, -1.0, -1.0); 
    glVertex3f(1.0, -1.0, -1.0);  
    glVertex3f(1.0, 1.0, -1.0);   
    glVertex3f(-1.0, 1.0, -1.0);  
    glEnd();
    glLineWidth(1.0); //restaurar el ancho de línea y el color.
}

//Función para dibujar el controno donde se van a conectar las dos caras del cubo.
void contorno_conectando(){
    glColor3f(0.0, 1.0, 1.0);  //cyan.
    glLineWidth(5.0); //se establece el ancho del contorno.
    
    glBegin(GL_LINES);
    glVertex3f(-1.0, -1.0, 1.0); 
    glVertex3f(-1.0, -1.0, -1.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(1.0, -1.0, 1.0);    
    glVertex3f(1.0, -1.0, -1.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(1.0, 1.0, 1.0);   
    glVertex3f(1.0, 1.0, -1.0); 
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-1.0, 1.0, 1.0);  
    glVertex3f(-1.0, 1.0, -1.0);      
    glEnd();
}

//Función para dibujar un cubo con contornos.
void dibujarCubo() {
    setColorActual(); //establecemos el color actual.

    //Dibujamos la cara frontal del cubo.
    glBegin(GL_QUADS);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();
    contorno_carafrontal(); //llamamos esta función después de que se dibuje el triángulo porque si no, no se logra cambiar de color la figura.

    //Cara trasera.
    setColorActual();
    glBegin(GL_QUADS);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
    contorno_caratrasera(); //llamamos esta función después de que se dibuje el triángulo porque si no, no se logra cambiar de color la figura.

    //Cara inferior.
    setColorActual();
    glBegin(GL_QUADS);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);

    //Cara lateral derecha.
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);

    //Cara superior.
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);

    //Cara lateral izquierda.
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
    contorno_conectando(); //llamamos esta función después de que se dibuje el triángulo porque si no, no se logra cambiar de color la figura.
}

// Función para manejar el cambio de tamaño de la ventana.
static void reshape01(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); //establecemos la ventana de visualización (viewport) con las dimensiones dadas.
    glMatrixMode(GL_PROJECTION); //seleccionamos y configuramos la matriz de proyección
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h); //configuramos una proyección ortográfica 2D
    reshape02(w, h);
}

//Función que configura la proyección y el área de visualización en la ventana.
void reshape02(int w, int h) {
    glViewport(0, 0, w, h); //establece el área de visualización en función del tamaño de la ventana.
    glMatrixMode(GL_PROJECTION); //cambia a la matriz de proyección y carga una matriz de identidad.
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0); // establece la perspectiva de la cámara usando gluPerspective.
    glMatrixMode(GL_MODELVIEW); //cambia a la matriz de modelo-vista.
}


//Función para establecer el color actual.
void setColorActual() {

    //Se evalúa la opción de color seleccionada.
    switch (colorSeleccionado) {
    case 1:
        glColor3f(1.0, 1.0, 0.0); //amarillo.
        break;
    case 2:
        glColor3f(1.0, 0.0, 0.0); //rojo.
        break;
    case 3:
        glColor3f(0.0, 1.0, 0.0); //verde.
        break;
    case 4:
        glColor3f(0.0, 0.0, 1.0); //azul.
        break;
    case 5:
        glColor3f(0.5, 0.0, 0.5); //morado.
        break;
    default:
        glColor3f(1.0, 1.0, 1.0); //blanco (valor predeterminado).
    }
}


//Función de visualización.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpiamos el búfer de color.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //cargamos la matriz de modelo-vista identidad.
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //configura la matriz de vista para la cámara.

    //Aplicamos las traslaciones y rotaciones según las variables de posición y rotación.
    glTranslatef(eje_x, eje_y, eje_z);
    glRotatef(eje_x, 1.0, 0.0, 0.0);
    glRotatef(eje_y, 0.0, 1.0, 0.0);
    glRotatef(eje_z, 0.0, 0.0, 1.0);

    glRotatef(eje_w, 1.0, 0.0, 0.0);
    glRotatef(eje_a, 0.0, 1.0, 0.0);
    glRotatef(eje_d, 0.0, 0.0, 1.0);

    //Seleccionamos la figura según la opción del menú.
    switch (figuraSeleccionada) {
        case 1:
            //Renderizamos el texto y el triángulo.
            texto_triangulo();
            dibujarTriangulo();
            break;
        case 2:
            //Renderizamos el texto y el cuadrado.
            texto_cuadrado();
            dibujarCuadrado();
            break;
        case 3:
            //Renderizamos el texto y el prisma triangular.
            texto_prisma();
            dibujarPrismaTriangular();
            break;
        case 4:
            //Renderizamos el texto y el cubo.
            texto_cubo();
            dibujarCubo();
            break;
    }
    glFlush(); //forzamos el renderizado.
}


//Función para manejar las teclas especiales.
void specialKeys(int key, int x, int y) {

    //Evaluamos la tecla especial presionada.
    switch (key) {

        //Si es la tecla de flecha derecha, incrementamos la posición en el eje x.
        case GLUT_KEY_RIGHT:
            eje_x += 0.1;
            break;

        //Si es la tecla de flecha izquierda, incrementamos la posición en el eje y.
        case GLUT_KEY_LEFT:
            eje_y += 0.1;
            break;

        //Si es la tecla de flecha abajo, salimos del programa.
        case GLUT_KEY_DOWN:
            exit(0);
            break;
    }  
    glutSwapBuffers();
    glutPostRedisplay(); //solicitamos una redibujado de la escena.
}

//Función para manejar las selecciones del menú.
void menu(int value) {
    if (value >= 1 && value <= 4) { //verificamos si el valor está en el rango de 1 a 4, correspondiente a las figuras.
        figuraSeleccionada = value; //asignamos el valor de la figura seleccionada.
    } 
    else if (value >= 11 && value <= 15) { //si no, verificamos si el valor está en el rango de 11 a 15, correspondiente a los colores.
        colorSeleccionado = value - 10; //asignamos el valor del color seleccionado ajustando el rango.
    }
    glutPostRedisplay(); //solicitamos una redibujado de la escena.
}

//Función para manejar las teclas 'x', 'y' y 'z'.
void movimientoMenu(unsigned char key, int x, int y) {
    switch (key) { //evaluamos la tecla presionada.

        //Si es 'x' o 'X', incrementamos la posición en el eje x.
        case 'x':
        case 'X':
            eje_x += 0.1;
            break;

        //Si es 'y' o 'Y', incrementamos la posición en el eje y.
        case 'y':
        case 'Y':
            eje_y += 0.1;
            break;

        //Si es 'z' o 'Z', incrementamos la posición en el eje z.
        case 'z':
        case 'Z':
            eje_z += 0.1;
            break;
    }
    glutPostRedisplay(); //solicitamos una redibujado de la escena.
}

//Función para manejar las teclas 'w', 'a' y 'd' para rotar la figura.
void rotarfigura(unsigned char key, int w, int a, int d) {
    switch (key) { //evaluamos la tecla presionada.

        //Si es 'w' o 'W', incrementamos el ángulo de rotación en el eje w.
        case 'w':
        case 'W':
            eje_w += 5;
            break;

        //Si es 'a' o 'A', incrementamos el ángulo de rotación en el eje a.
        case 'a':
        case 'A':
            eje_a += 5;
            break;
        //Si es 'd' o 'D', incrementamos el ángulo de rotación en el eje d.
        case 'd':
        case 'D':
            eje_d += 5;
            break;
    }
    glutPostRedisplay(); //solicitamos una redibujado de la escena.
}

//Función para manejar las teclas 'o', 'p', 'i' y 'u' para mover la figura.
void movercamara(int key, int x, int y) {
    switch (key) { //evaluamos la tecla presionada

    //Si es 'O' u 'o', se mueve la cámara positivamente en el eje x.   
    case 'O':
    case 'o':
        cameraX -= 0.1;
        break;

    //Si es 'P' o 'p', se mueve la cámara negativamente en el eje x. 
    case 'P':
    case 'p':
        cameraX += 0.1;
        break;

    //Si es 'I' o 'i', se mueve la cámara positivamente en el eje y.
    case 'I':
    case 'i':
        cameraY += 0.1;
        break;

    //Si es 'U' o 'u', se mueve la cámara negativamente en el eje y.
    case 'U':
    case 'u':
        cameraY -= 0.1;
        break;
    }
    glutPostRedisplay();
}


//Función para manejar movimientos basados en teclas.
void movimientos(unsigned char key, int x, int y) {
    movimientoMenu(key, x, y);
    rotarfigura(key, 0, 0, 0);  
    movercamara(key, x, y);
}

//Esta función inicializa algunos estados de OpenGL.
static void init01(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0); //establece el color de fondo como blanco.
   glShadeModel(GL_SMOOTH); //establece el modelo de sombreado como suavizado (GL_SMOOTH).
}

//Función principal.
int main(int argc, char** argv) { 
    glutInit(&argc, argv); //inicializamos GLUT.

    // Configuramos el modo de visualización y creamos la ventana.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("MENU :D.");
    init01(); //llamamos a la función de inicialización.

    //Configuramos el color de fondo y la proyección ortográfica.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glOrtho(-5, 5, -5, 5, -5, 5);

    int figuraMenu = glutCreateMenu(menu); //creamos los menús.

    //Agregamos opciones al menú de figuras.
    glutAddMenuEntry("Triangulo", 1);
    glutAddMenuEntry("Cuadrado", 2);
    glutAddMenuEntry("Prisma Triangular", 3);
    glutAddMenuEntry("Cubo", 4);

    int colorMenu = glutCreateMenu(menu);

    //Agregamos opciones al menú de colores.
    glutAddMenuEntry("Amarillo", 11);
    glutAddMenuEntry("Rojo", 12);
    glutAddMenuEntry("Verde", 13);
    glutAddMenuEntry("Azul", 14);
    glutAddMenuEntry("Morado", 15);

    
    int moverSubMenuID = glutCreateMenu(movimientoMenu); //creamos submenús para mover y rotar.

    //Agregamos opciones al submenú de mover.
    glutAddMenuEntry("Mover en X (tecla 'x')", 'x');
    glutAddMenuEntry("Mover en Y (tecla 'y')", 'y');
    glutAddMenuEntry("Mover en Z (tecla 'z')", 'z');

    int rotarfig = glutCreateMenu(rotarfigura);

    //Agregamos opciones al submenú de rotar.
    glutAddMenuEntry("Rotar en X (tecla 'w')", 'w');
    glutAddMenuEntry("Rotar en Y (tecla 'a')", 'a');
    glutAddMenuEntry("Rotar en Z (tecla 'd')", 'd');

    int llavesSubMenuID = glutCreateMenu(specialKeys); //creamos submenús para las teclas especiales.

    //Agregamos opciones al submenú de teclas especiales.
    glutAddMenuEntry("Mover en X (tecla 'derecha')", GLUT_KEY_RIGHT);
    glutAddMenuEntry("Mover en Y (tecla 'izquierda')", GLUT_KEY_LEFT);
    glutAddMenuEntry("Salir del programa (tecla 'abajo')", 27); //27 representa la tecla Esc.

    int movcam = glutCreateMenu(movercamara); //creamos submenús para mover la cámara.

    //Agregamos opciones al submenú de mover la cámara.
    glutAddMenuEntry("Mover camara en X positivo (tecla 'p')", 'p');
    glutAddMenuEntry("Mover camara en X negativo (tecla 'o')", 'o');
    glutAddMenuEntry("Mover camara en Y positivo (tecla 'i')", 'i');
    glutAddMenuEntry("Mover camara en Y negativo (tecla 'u')", 'u');

    
    glutCreateMenu(menu); //creamos el menú principal.

    //Agregamos submenús al menú principal.
    glutAddSubMenu("Dibujar figura", figuraMenu);
    glutAddSubMenu("Colores", colorMenu);
    glutAddSubMenu("Ejes", moverSubMenuID);
    glutAddSubMenu("Llaves especiales", llavesSubMenuID);
    glutAddSubMenu("Rotar", rotarfig);
    glutAddSubMenu("Mover camara", movcam);

    
    glutAttachMenu(GLUT_RIGHT_BUTTON); //adjuntamos el menú principal al botón derecho del ratón.

    //Definimos las funciones de visualización y redimensionamiento.
    glutDisplayFunc(display);
    glutReshapeFunc(reshape01);

    //Definimos las funciones para las teclas especiales y teclas normales.
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(movimientos);

    glutMainLoop(); //iniciamos el bucle principal de GLUT.
    return 0;
}