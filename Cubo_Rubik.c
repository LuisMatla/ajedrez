#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

//variables globales para el cubo de rubik.

static int superior[3][3]={{0,0,0},{0,0,0},{0,0,0}}, 
derecha[3][3]={{1,1,1},{1,1,1},{1,1,1}}, 
frente[3][3]={{2,2,2},{2,2,2},{2,2,2}}, 
trasero[3][3]={{3,3,3},{3,3,3},{3,3,3}}, 
abajo[3][3]={{4,4,4},{4,4,4},{4,4,4}}, 
izquierda[3][3]={{5,5,5},{5,5,5},{5,5,5}};

//variables para el control del mouse del cubo de rubik.
int mouseRotacionVista = 0; //para rotar la vista con clic derecho.
int mouseRotacionPieza = 0; //para rotar piezas con clic izquierdo.
int lastMouseXRubik = 0; //última posición x del mouse para el cubo de rubik.
int lastMouseYRubik = 0; //última posición y del mouse para el cubo de rubik.
int clickInicialXRubik = 0; //posición x inicial del click para el cubo de rubik.
int clickInicialYRubik = 0; //posición y inicial del click para el cubo de rubik.
int windowWidthRubik = 500; //ancho de la ventana del cubo de rubik.
int windowHeightRubik = 500; //alto de la ventana del cubo de rubik.
int rotacionActiva = 0; //indica si hay una rotación activa con el mouse.
int caraRotando = 0; //cara que se está rotando actualmente.
float acumuladoRotacion = 0.0; //acumulado de rotación durante el arrastre. .
int filaSeleccionada = -1; //fila seleccionada (0=superior, 1=media, 2=inferior).
int columnaSeleccionada = -1; //columna seleccionada (0=izquierda, 1=centro, 2=derecha).
int tipoMovimiento = 0; //0=ninguno, 1=fila horizontal, 2=columna vertical.
 
static int rotacion=0; //rotación actual del cubo.
int rotacion_completa=0; //indica si la rotación está completa.
static GLfloat theta=0.0; //ángulo de rotación actual.
static GLfloat p=0.0,q=0.0; //ángulos de rotación de la vista.
static GLint inverso=0; //indica si la rotación es inversa.
int iniciox=0,inicioy=0; //posición inicial del mouse para rotación de vista.
float cuboRubikScale = 1.0; //escala para zoom del cubo de rubik.

 
GLfloat vertices[][3]={{-1.0,-1.0,-1.0}, 
 
                       {1.0,-1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-1.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                        
                       {-1.0,-3.0,-1.0}, 
                       {1.0,-3.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0},  
                       {-1.0,-3.0,1.0}, 
                       {1.0,-3.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                        
                       {-3.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-3.0,1.0,-1.0},  
                       {-3.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-3.0,1.0,1.0}, 

                       {1.0,-1.0,-1.0}, 
                       {3.0,-1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, // right center .
                       {1.0,-1.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, 
 
                       {-1.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {1.0,3.0,-1.0}, 
                       {-1.0,3.0,-1.0}, // top center .
                       {-1.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {1.0,3.0,1.0}, 
                       {-1.0,3.0,1.0}, 
 
                       {-1.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, //front center .

                       {-1.0,-1.0,3.0}, 
                       {1.0,-1.0,3.0}, 
                       {1.0,1.0,3.0}, 
                       {-1.0,1.0,3.0}, 
 
                       {-1.0,-1.0,-3.0}, 
                       {1.0,-1.0,-3.0}, 
                       {1.0,1.0,-3.0}, 
                       {-1.0,1.0,-3.0}, //back center .
                       {-1.0,-1.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
 
                       {-3.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-1.0,3.0,-1.0}, 
                       {-3.0,3.0,-1.0}, // top left center .
                       {-3.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-1.0,3.0,1.0}, 
                       {-3.0,3.0,1.0},  
                             
                       {1.0,1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 

                       {3.0,3.0,-1.0}, 
                       {1.0,3.0,-1.0}, // top right  center .
                       {1.0,1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {3.0,3.0,1.0}, 
                       {1.0,3.0,1.0}, 
 
                       {-1.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {1.0,3.0,1.0}, 
                       {-1.0,3.0,1.0}, // top front center .
                       {-1.0,1.0,3.0}, 
                       {1.0,1.0,3.0}, 
                       {1.0,3.0,3.0}, 
                       {-1.0,3.0,3.0}, 
 
                       {-1.0,1.0,-3.0}, 
                       {1.0,1.0,-3.0}, 
                       {1.0,3.0,-3.0}, 
                       {-1.0,3.0,-3.0}, // top back center .
                       {-1.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {1.0,3.0,-1.0}, 
                       {-1.0,3.0,-1.0}, 

        {-3.0,-3.0,-1.0}, 
                       {-1.0,-3.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-3.0,-1.0,-1.0},  //bottom left center .
                       {-3.0,-3.0,1.0}, 
                       {-1.0,-3.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                       {-3.0,-1.0,1.0}, 
 
        {1.0,-3.0,-1.0}, 
                       {3.0,-3.0,-1.0}, 
                       {3.0,-1.0,-1.0}, 
                       {1.0,-1.0,-1.0},  //bottom  right center .
                       {1.0,-3.0,1.0}, 
                       {3.0,-3.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0}, 
            
        {-1.0,-3.0,1.0}, 
                       {1.0,-3.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0},  //bottom front center .

                       {-1.0,-3.0,3.0}, 
                       {1.0,-3.0,3.0}, 
                       {1.0,-1.0,3.0}, 
                       {-1.0,-1.0,3.0}, 
 
                       {-1.0,-3.0,-3.0}, 
                       {1.0,-3.0,-3.0}, 
                       {1.0,-1.0,-3.0}, 
                       {-1.0,-1.0,-3.0},  //bottom back center .
                       {-1.0,-3.0,-1.0}, 
                       {1.0,-3.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
 
        {-3.0,1.0,-3.0}, 
                       {-1.0,1.0,-3.0}, 
                       {-1.0,3.0,-3.0}, 
                       {-3.0,3.0,-3.0}, // top left back .
                       {-3.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-1.0,3.0,-1.0}, 
                       {-3.0,3.0,-1.0}, 
 
        {-3.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-1.0,3.0,1.0}, 
                       {-3.0,3.0,1.0}, // top left front .
                       {-3.0,1.0,3.0}, 
                       {-1.0,1.0,3.0}, 
                       {-1.0,3.0,3.0}, 
                       {-3.0,3.0,3.0}, 
 
        {1.0,1.0,-3.0}, 
                       {3.0,1.0,-3.0}, 
                       {3.0,3.0,-3.0}, 
                       {1.0,3.0,-3.0}, // top right  back .
                       {1.0,1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 
                       {3.0,3.0,-1.0}, 
                       {1.0,3.0,-1.0}, 
 
        {1.0,1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {3.0,3.0,1.0}, 
                       {1.0,3.0,1.0}, // top right  front .
                       {1.0,1.0,3.0}, 
                       {3.0,1.0,3.0}, 
                       {3.0,3.0,3.0}, 

                       {1.0,3.0,3.0}, 
 
        {-3.0,-1.0,-3.0}, 
                       {-1.0,-1.0,-3.0}, 
                       {-1.0,1.0,-3.0}, 
                       {-3.0,1.0,-3.0},  //ceneter left back .
                       {-3.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-3.0,1.0,-1.0}, 
 
        {-3.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-3.0,1.0,1.0},  //center left front .
                       {-3.0,-1.0,3.0}, 
                       {-1.0,-1.0,3.0}, 
                       {-1.0,1.0,3.0}, 
                       {-3.0,1.0,3.0}, 
 
        {1.0,-1.0,-3.0}, 
                       {3.0,-1.0,-3.0}, 
                       {3.0,1.0,-3.0}, 
                       {1.0,1.0,-3.0}, // center right back .
                       {1.0,-1.0,-1.0}, 

                       {3.0,-1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
 
        {1.0,-1.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, // center right front .
                       {1.0,-1.0,3.0}, 
                       {3.0,-1.0,3.0}, 
                       {3.0,1.0,3.0}, 
                       {1.0,1.0,3.0}, 
 
        {-3.0,-3.0,-3.0}, 
                       {-1.0,-3.0,-3.0}, 
                       {-1.0,-1.0,-3.0}, 
                       {-3.0,-1.0,-3.0},  //bottom left back .
                       {-3.0,-3.0,-1.0}, 
                       {-1.0,-3.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-3.0,-1.0,-1.0}, 
 
        {-3.0,-3.0,1.0}, 
                       {-1.0,-3.0,1.0}, 
                       {-1.0,-1.0,1.0}, 

                       {-3.0,-1.0,1.0},  //bottom left front .
                       {-3.0,-3.0,3.0}, 
                       {-1.0,-3.0,3.0}, 
                       {-1.0,-1.0,3.0}, 
                       {-3.0,-1.0,3.0}, 
 
        {1.0,-3.0,-3.0}, 
                       {3.0,-3.0,-3.0}, 
                       {3.0,-1.0,-3.0}, 
                       {1.0,-1.0,-3.0},  //bottom  right back .
                       {1.0,-3.0,-1.0}, 
                       {3.0,-3.0,-1.0}, 
                       {3.0,-1.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
            
        {1.0,-3.0,1.0}, 
                       {3.0,-3.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0},  //bottom  right front .
                       {1.0,-3.0,3.0}, 
                       {3.0,-3.0,3.0}, 
                       {3.0,-1.0,3.0}, 
                       {1.0,-1.0,3.0}, 
        {0.0,7.0,0.0}, 
        {0.0,7.5,0.0}, 
        {0.5,7.5,0.0}, //speed meter .
        {0.5,7.0,0.0}
}; 

GLfloat color[][3]={{194.0 / 255.0, 178.0 / 255.0, 128.0 / 255.0}, //amarillo. .
                    {250.0 / 255.0, 128.0 / 255.0, 114.0 / 255.0},  //verde claro .
                    {0.956863, 0.643137, 0.376471},  //lila.
                    {255.0 / 255.0, 204.0 / 255.0, 153.0 / 255.0},  //naranja claro.
                    {127.0 / 255.0, 1.0, 212.0 / 255.0},  //agumarina.
                    {219.0 / 255.0, 48.0 / 255.0, 122.0 / 255.0}, //rosa mexicano. .
		{0.0,0.0,0.0}, //negro.
};

//dibuja un contorno de un cubito con el color especificado.
void contornito(int a,int b,int c,int d,int e) {    
	glColor3f(1.0, 1.0, 1.0); //blanco.
	glLineWidth(5.0); 
	glBegin(GL_LINE_LOOP); 
	glVertex3fv(vertices[b]); 
	glVertex3fv(vertices[c]); 
	glVertex3fv(vertices[d]); 
	glVertex3fv(vertices[e]); 
	glEnd(); 

	glColor3fv(color[a]); 
	glBegin(GL_POLYGON); 
	glVertex3fv(vertices[b]); 
	glVertex3fv(vertices[c]); 
	glVertex3fv(vertices[d]); 
	glVertex3fv(vertices[e]); 
	glEnd(); 
} 

//dibuja el cubito central del cubo de rubik.
void contornocubo1() { 
	contornito(6,0,3,2,1);  
	contornito(6,2,3,7,6);  
	contornito(6,0,4,7,3);    
	contornito(6,1,2,6,5);            
	contornito(6,4,5,6,7); 
	contornito(6,0,1,5,4);  
}

//dibuja el cubito inferior central del cubo de rubik.
void contornocubo2() { 
	contornito(6,8,11,10,9);  
	contornito(6,10,11,15,14);  
	contornito(6,8,12,15,11);   
	contornito(6,9,10,14,13);            
	contornito(6,12,13,14,15); 
	contornito(abajo[1][1],8,9,13,12);  
} 

//dibuja el cubito izquierdo central del cubo de rubik.
void contornocubo3() { 
	contornito(6,16,19,18,17);  
	contornito(6,18,19,23,22);  
	contornito(izquierda[1][1],16,20,23,19);    
	contornito(6,17,18,22,21);            
	contornito(6,20,21,22,23); 
	contornito(6,16,17,21,20);  
} 

//dibuja el cubito derecho central del cubo de rubik.
void contornocubo4() { 
	contornito(6,24,27,26,25);  
	contornito(6,26,27,31,30);  
	contornito(6,24,28,31,27);    
	contornito(derecha[1][1],25,26,30,29);            
	contornito(6,28,29,30,31); 
	contornito(6,24,25,29,28);  
} 

//dibuja el cubito superior central del cubo de rubik.
void contornocubo5() { 
	contornito(6,32,35,34,33);  
	contornito(superior[1][1],34,35,39,38);  
	contornito(6,32,36,39,35);    
	contornito(6,33,34,38,37);            
	contornito(6,36,37,38,39); 
	contornito(6,32,33,37,36);  
} 

//dibuja el cubito frontal central del cubo de rubik.
void contornocubo6() { 
	contornito(6,40,43,42,41);  
	contornito(6,42,43,47,46);  
	contornito(6,40,44,47,43);   
	contornito(6,41,42,46,45);            
	contornito(frente[1][1],44,45,46,47); 
	contornito(6,40,41,45,44);  
} 

//dibuja el cubito trasero central del cubo de rubik.
void contornocubo7() { 
	contornito(trasero[1][1],48,51,50,49);  
	contornito(6,50,51,55,54);  
	contornito(6,48,52,55,51);   
	contornito(6,49,50,54,53);            
	contornito(6,52,53,54,55); 
	contornito(6,48,49,53,52);  
} 

//dibuja el cubito superior-izquierdo del cubo de rubik.
void contornocubo8() { 
	contornito(6,56,59,58,57);  
	contornito(superior[1][0],58,59,63,62);  
	contornito(izquierda[0][1],56,60,63,59);    
	contornito(6,57,58,62,61);            
	contornito(6,60,61,62,63); 
	contornito(6,56,57,61,60);  
} 

//dibuja el cubito superior-derecho del cubo de rubik.
void contornocubo9() { 
	contornito(6,64,67,66,65);  
	contornito(superior[1][2],66,67,71,70);  
	contornito(6,64,68,71,67);   
	contornito(derecha[0][1],65,66,70,69);            
	contornito(6,68,69,70,71); 
	contornito(6,64,65,69,68);  
} 

//dibuja el cubito superior-frontal del cubo de rubik.
void contornocubo10() { 
    contornito(6, 72, 75, 74, 73);  
    contornito(superior[2][1], 74, 75, 79, 78);  
    contornito(6, 72, 76, 79, 75);    
    contornito(6, 73, 74, 78, 77);            
    contornito(frente[0][1], 76, 77, 78, 79); 
    contornito(6, 72, 73, 77, 76);  
} 

//dibuja el cubito superior-trasero del cubo de rubik.
void contornocubo11() { 
    contornito(trasero[0][1], 80, 83, 82, 81);  
    contornito(superior[0][1], 82, 83, 87, 86);  
    contornito(6, 80, 84, 87, 83);    
    contornito(6, 81, 82, 86, 85);            
    contornito(6, 84, 85, 86, 87); 
    contornito(6, 80, 81, 85, 84);  
} 

//dibuja el cubito inferior-izquierdo del cubo de rubik.
void contornocubo12() { 
    contornito(6, 80 + 8, 83 + 8, 82 + 8, 81 + 8);  
    contornito(6, 82 + 8, 83 + 8, 87 + 8, 86 + 8);  
    contornito(izquierda[2][1], 80 + 8, 84 + 8, 87 + 8, 83 + 8);    
    contornito(6, 81 + 8, 82 + 8, 86 + 8, 85 + 8);            
    contornito(6, 84 + 8, 85 + 8, 86 + 8, 87 + 8); 
    contornito(abajo[1][0], 80 + 8, 81 + 8, 85 + 8, 84 + 8);  
} 

//dibuja el cubito inferior-derecho del cubo de rubik.
void contornocubo13() { 
    contornito(6, 80 + 16, 83 + 16, 82 + 16, 81 + 16);  
    contornito(6, 82 + 16, 83 + 16, 87 + 16, 86 + 16);  
    contornito(6, 80 + 16, 84 + 16, 87 + 16, 83 + 16);    
    contornito(derecha[2][1], 81 + 16, 82 + 16, 86 + 16, 85 + 16);            
    contornito(6, 84 + 16, 85 + 16, 86 + 16, 87 + 16); 
    contornito(abajo[1][2], 80 + 16, 81 + 16, 85 + 16, 84 + 16);  
} 

//dibuja el cubito inferior-frontal del cubo de rubik.
void contornocubo14() { 
    contornito(6, 80 + 24, 83 + 24, 82 + 24, 81 + 24);  
    contornito(6, 82 + 24, 83 + 24, 87 + 24, 86 + 24);  
    contornito(6, 80 + 24, 84 + 24, 87 + 24, 83 + 24);   
    contornito(6, 81 + 24, 82 + 24, 86 + 24, 85 + 24);            
    contornito(frente[2][1], 84 + 24, 85 + 24, 86 + 24, 87 + 24); 
    contornito(abajo[0][1], 80 + 24, 81 + 24, 85 + 24, 84 + 24);  
} 

//dibuja el cubito inferior-trasero del cubo de rubik.
void contornocubo15() { 
    contornito(trasero[2][1], 112, 115, 114, 113);  
    contornito(6, 114, 115, 119, 118);  
    contornito(6, 112, 116, 119, 115);   
    contornito(6, 113, 114, 118, 117);            
    contornito(6, 116, 117, 118, 119); 
    contornito(abajo[2][1], 112, 113, 117, 116);  
} 

//dibuja el cubito esquina superior-izquierda-trasera del cubo de rubik.
void contornocubo16() { 
    contornito(trasero[0][2], 120, 123, 122, 121);  
    contornito(superior[0][0], 122, 123, 127, 126);  
    contornito(izquierda[0][0], 120, 124, 127, 123);    
    contornito(6, 121, 122, 126, 125);            
    contornito(6, 124, 125, 126, 127); 
    contornito(6, 120, 121, 125, 124);  
} 

//dibuja el cubito esquina superior-izquierda-frontal del cubo de rubik.
void contornocubo17() { 
    contornito(6, 128, 131, 130, 129);  
    contornito(superior[2][0], 130, 131, 135, 134);  
    contornito(izquierda[0][2], 128, 132, 135, 131);    
    contornito(6, 129, 130, 134, 133);            
    contornito(frente[0][0], 132, 133, 134, 135); 
    contornito(6, 128, 129, 133, 132);  
} 

//dibuja el cubito esquina superior-derecha-trasera del cubo de rubik.
void contornocubo18() { 
    contornito(trasero[0][0], 136, 139, 138, 137);  
    contornito(superior[0][2], 138, 139, 143, 142);  
    contornito(6, 136, 140, 143, 139);    
    contornito(derecha[0][2], 137, 138, 142, 141);            
    contornito(6, 140, 141, 142, 143); 
    contornito(6, 136, 137, 141, 140);  
} 

//dibuja el cubito esquina superior-derecha-frontal del cubo de rubik.
void contornocubo19() { 
    contornito(6, 144, 147, 146, 145);  
    contornito(superior[2][2], 146, 147, 151, 150);  
    contornito(6, 144, 148, 151, 147);    
    contornito(derecha[0][0], 145, 146, 150, 149);            
    contornito(frente[0][2], 148, 149, 150, 151); 
    contornito(6, 144, 145, 149, 148);  
} 

//dibuja el cubito esquina media-izquierda-trasera del cubo de rubik.
void contornocubo20() { 
    contornito(trasero[1][2], 152, 155, 154, 153);  
    contornito(6, 154, 155, 159, 158);  
    contornito(izquierda[1][0], 152, 156, 159, 155);  
    contornito(6, 153, 154, 158, 157);            
    contornito(6, 156, 157, 158, 159); 
    contornito(6, 152, 153, 157, 156);  
} 

//dibuja el cubito esquina media-izquierda-frontal del cubo de rubik.
void contornocubo21() { 
    contornito(6, 160, 163, 162, 161);  
    contornito(6, 162, 163, 167, 166);  
    contornito(izquierda[1][2], 160, 164, 167, 163);     
    contornito(6, 161, 162, 166, 165);            
    contornito(frente[1][0], 164, 165, 166, 167); 
    contornito(6, 160, 161, 165, 164);  
} 

//dibuja el cubito esquina media-derecha-trasera del cubo de rubik.
void contornocubo22() { 
    contornito(trasero[1][0], 168, 171, 170, 169);  
    contornito(6, 170, 171, 175, 174);  
    contornito(6, 168, 172, 175, 171); 
    contornito(derecha[1][2], 169, 170, 174, 173);            
    contornito(6, 172, 173, 174, 175); 
    contornito(6, 168, 169, 173, 172);  
} 

//dibuja el cubito esquina media-derecha-frontal del cubo de rubik.
void contornocubo23() { 
    contornito(6, 176, 179, 178, 177);  
    contornito(6, 178, 179, 183, 182);  
    contornito(6, 176, 180, 183, 179);    
    contornito(derecha[1][0], 177, 178, 182, 181);            
    contornito(frente[1][2], 180, 181, 182, 183); 
    contornito(6, 176, 177, 181, 180);  
} 

//dibuja el cubito esquina inferior-izquierda-trasera del cubo de rubik.
void contornocubo24() { 
    contornito(trasero[2][2], 184, 187, 186, 185);  
    contornito(6, 186, 187, 191, 190);  
    contornito(izquierda[2][0], 184, 188, 191, 187);    
    contornito(6, 185, 186, 190, 189);            
    contornito(6, 188, 189, 190, 191); 
    contornito(abajo[2][0], 184, 185, 189, 188);  
} 

//dibuja el cubito esquina inferior-izquierda-frontal del cubo de rubik.
void contornocubo25() { 
    contornito(6, 192, 195, 194, 193);  
    contornito(6, 194, 195, 199, 198);  
    contornito(izquierda[2][2], 192, 196, 199, 195);    
    contornito(6, 193, 194, 198, 197);            
    contornito(frente[2][0], 196, 197, 198, 199); 
    contornito(abajo[0][0], 192, 193, 197, 196);  
} 

//dibuja el cubito esquina inferior-derecha-trasera del cubo de rubik.
void contornocubo26() { 
    contornito(trasero[2][0], 200, 203, 202, 201);  
    contornito(6, 202, 203, 207, 206);  
    contornito(6, 200, 204, 207, 203);   
    contornito(derecha[2][2], 201, 202, 206, 205);            
    contornito(6, 204, 205, 206, 207); 
    contornito(abajo[2][2], 200, 201, 205, 204);  
}

//dibuja el cubito esquina inferior-derecha-frontal del cubo de rubik.
void contornocubo27() { 
    contornito(6, 208, 211, 210, 209);  
    contornito(6, 210, 211, 215, 214);  
    contornito(6, 208, 212, 215, 211);    
    contornito(derecha[2][0], 209, 210, 214, 213);            
    contornito(frente[2][2], 212, 213, 214, 215); 
    contornito(abajo[0][2], 208, 209, 213, 212);  
}

//función principal de renderizado que dibuja el cubo de rubik completo.
void display() { 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity(); 
	glColor3fv(color[0]); 
	glPushMatrix();
	glScalef(cuboRubikScale, cuboRubikScale, cuboRubikScale); //aplicar zoom.
	glRotatef(25.0+p,1.0,0.0,0.0); 
	glRotatef(-30.0+q,0.0,1.0,0.0); 
	glRotatef(0.0,0.0,0.0,1.0);  

    if(rotacion == 0) {  
        contornocubo1(); 
        contornocubo2(); 
        contornocubo3(); 
        contornocubo4(); 
        contornocubo5(); 
        contornocubo6(); 
        contornocubo7(); 
        contornocubo8();  
        contornocubo9(); 
        contornocubo10(); 
        contornocubo11(); 
        contornocubo12(); 
        contornocubo13(); 
        contornocubo14(); 
        contornocubo15(); 
        contornocubo16(); 
        contornocubo17(); 
        contornocubo18(); 
        contornocubo19(); 
        contornocubo20(); 
        contornocubo21(); 
        contornocubo22(); 
        contornocubo23(); 
        contornocubo24(); 
        contornocubo25(); 
        contornocubo26(); 
        contornocubo27(); 
    }

    if (rotacion == 1) { 
        //dibujar cubitos que no se mueven.
        contornocubo1(); 
        contornocubo2(); 
        contornocubo3(); 
        contornocubo4(); 
        contornocubo6(); 
        contornocubo7(); 
        contornocubo12(); 
        contornocubo13(); 
        contornocubo14(); 
        contornocubo15(); 
        contornocubo20(); 
        contornocubo21(); 
        contornocubo22(); 
        contornocubo23(); 
        contornocubo24(); 
        contornocubo25(); 
        contornocubo26(); 
        contornocubo27(); 
        
        //aplicar rotación solo a la fila/columna seleccionada.
        if(tipoMovimiento == 1 && filaSeleccionada == 0) {
            //fila superior (0-1-2) - rotar horizontalmente.
            if (inverso == 0) {
                glRotatef(-theta, 0.0, 1.0, 0.0); 
            } 
            else { 
                glRotatef(theta, 0.0, 1.0, 0.0); 
            } 
            contornocubo5(); 
            contornocubo8();  
            contornocubo9(); 
            contornocubo10(); 
            contornocubo11(); 
            contornocubo16(); 
            contornocubo17(); 
            contornocubo18(); 
            contornocubo19(); 
        } else if(tipoMovimiento == 2 && columnaSeleccionada == 1) {
            //columna centro (1-4-7) - rotar verticalmente.
            if (inverso == 0) {
                glRotatef(-theta, 0.0, 1.0, 0.0); 
            } 
            else { 
                glRotatef(theta, 0.0, 1.0, 0.0); 
            } 
            contornocubo5(); 
            contornocubo1(); 
            contornocubo6(); 
            contornocubo7(); 
            contornocubo10(); 
            contornocubo11(); 
            contornocubo14(); 
            contornocubo15(); 
            contornocubo18(); 
            contornocubo19(); 
            contornocubo22(); 
            contornocubo23(); 
        } else {
            //rotación completa de cara superior.
            if (inverso == 0) {
                glRotatef(-theta, 0.0, 1.0, 0.0); 
            } 
            else { 
                glRotatef(theta, 0.0, 1.0, 0.0); 
            } 
            contornocubo5(); 
            contornocubo8();  
            contornocubo9(); 
            contornocubo10(); 
            contornocubo11(); 
            contornocubo16(); 
            contornocubo17(); 
            contornocubo18(); 
            contornocubo19(); 
        }
    }

    if(rotacion==2) {  
        //dibujar cubitos que no se mueven.
        contornocubo1(); 
        contornocubo2(); 
        contornocubo3(); 
        contornocubo5(); 
        contornocubo6(); 
        contornocubo7(); 
        contornocubo8();  
        contornocubo10(); 
        contornocubo11(); 
        contornocubo12(); 
        contornocubo14(); 
        contornocubo15(); 
        contornocubo16(); 
        contornocubo17(); 
        contornocubo20(); 
        contornocubo21(); 
        contornocubo24(); 
        contornocubo25(); 
        
        //aplicar rotación solo a la fila/columna seleccionada.
        if(tipoMovimiento == 2 && columnaSeleccionada == 2) {
            //columna derecha (2-5-8) - rotar verticalmente.
            if(inverso==0) { 
                glRotatef(-theta,1.0,0.0,0.0); 
            } 
            else {
                glRotatef(theta,1.0,0.0,0.0); 
            } 
            contornocubo4(); 
            contornocubo9(); 
            contornocubo13(); 
            contornocubo18(); 
            contornocubo19(); 
            contornocubo22(); 
            contornocubo23(); 
            contornocubo26(); 
            contornocubo27(); 
        } else {
            //rotación completa de cara derecha.
            if(inverso==0) { 
                glRotatef(-theta,1.0,0.0,0.0); 
            } 
            else {
                glRotatef(theta,1.0,0.0,0.0); 
            } 
            contornocubo4(); 
            contornocubo9(); 
            contornocubo13(); 
            contornocubo18(); 
            contornocubo19(); 
            contornocubo22(); 
            contornocubo23(); 
            contornocubo26(); 
            contornocubo27(); 
        }
    } 
    if(rotacion==3) { 
        contornocubo1(); 
        contornocubo2(); 
        contornocubo3(); 
        contornocubo4(); 
        contornocubo5(); 
        contornocubo7(); 
        contornocubo8();  
        contornocubo9(); 
        contornocubo11(); 
        contornocubo12(); 
        contornocubo13(); 
        contornocubo15(); 
        contornocubo16(); 
        contornocubo18(); 
        contornocubo20(); 
        contornocubo22(); 
        contornocubo24(); 
        contornocubo26(); 
        if(inverso==0) { 
            glRotatef(-theta,0.0,0.0,1.0); 
        } 
        else { 
            glRotatef(theta,0.0,0.0,1.0); 
        } 
        contornocubo6(); 
        contornocubo10(); 
        contornocubo14(); 
        contornocubo17(); 
        contornocubo19(); 
        contornocubo21(); 
        contornocubo23(); 
        contornocubo25(); 
        contornocubo27(); 
    } 
    if(rotacion==4) {  
        //dibujar cubitos que no se mueven.
        contornocubo1(); 
        contornocubo2(); 
        contornocubo4(); 
        contornocubo5(); 
        contornocubo6(); 
        contornocubo7(); 
        contornocubo9(); 
        contornocubo10(); 
        contornocubo11(); 
        contornocubo13(); 
        contornocubo14(); 
        contornocubo15(); 
        contornocubo18(); 
        contornocubo19(); 
        contornocubo22(); 
        contornocubo23(); 
        contornocubo26(); 
        contornocubo27(); 
        
        //aplicar rotación solo a la fila/columna seleccionada.
        if(tipoMovimiento == 2 && columnaSeleccionada == 0) {
            //columna izquierda (0-3-6) - rotar verticalmente.
            if(inverso==0) {
                glRotatef(theta,1.0,0.0,0.0); 
            } 
            else {
                glRotatef(-theta,1.0,0.0,0.0); 
            } 
            contornocubo3(); 
            contornocubo8();  
            contornocubo12(); 
            contornocubo16(); 
            contornocubo17(); 
            contornocubo20(); 
            contornocubo21(); 
            contornocubo24(); 
            contornocubo25(); 
        } else {
            //rotación completa de cara izquierda.
            if(inverso==0) {
                glRotatef(theta,1.0,0.0,0.0); 
            } 
            else {
                glRotatef(-theta,1.0,0.0,0.0); 
            } 
            contornocubo3(); 
            contornocubo8();  
            contornocubo12(); 
            contornocubo16(); 
            contornocubo17(); 
            contornocubo20(); 
            contornocubo21(); 
            contornocubo24(); 
            contornocubo25(); 
        }
    }


    if(rotacion==5) {  
        contornocubo1(); 
        contornocubo2(); 
        contornocubo3(); 
        contornocubo4(); 
        contornocubo5(); 
        contornocubo6(); 
        contornocubo8();  
        contornocubo9(); 
        contornocubo10(); 
        contornocubo12(); 
        contornocubo13(); 
        contornocubo14(); 
        contornocubo17(); 
        contornocubo19(); 
        contornocubo21(); 
        contornocubo23(); 
        contornocubo25(); 
        contornocubo27(); 
        if(inverso==0) {
            glRotatef(theta,0.0,0.0,1.0); 
        } 
        else { 
            glRotatef(-theta,0.0,0.0,1.0); 
        } 
        contornocubo7(); 
        contornocubo11(); 
        contornocubo15(); 
        contornocubo16(); 
        contornocubo18(); 
        contornocubo20(); 
        contornocubo22(); 
        contornocubo24(); 
        contornocubo26(); 
    } 
    if(rotacion==6) {  
        //dibujar cubitos que no se mueven.
        contornocubo1(); 
        contornocubo3(); 
        contornocubo4(); 
        contornocubo5(); 
        contornocubo6(); 
        contornocubo7(); 
        contornocubo8();  
        contornocubo9(); 
        contornocubo10(); 
        contornocubo11(); 
        contornocubo16(); 
        contornocubo17(); 
        contornocubo18(); 
        contornocubo19(); 
        contornocubo20(); 
        contornocubo21(); 
        contornocubo22(); 
        contornocubo23(); 
        
        //aplicar rotación solo a la fila/columna seleccionada.
        if(tipoMovimiento == 1 && filaSeleccionada == 2) {
            //fila inferior (6-7-8) - rotar horizontalmente.
            if(inverso==0) {
                glRotatef(theta,0.0,1.0,0.0); 
            } 
            else {
                glRotatef(-theta,0.0,1.0,0.0); 
            } 
            contornocubo2(); 
            contornocubo12(); 
            contornocubo13(); 
            contornocubo14(); 
            contornocubo15(); 
            contornocubo24(); 
            contornocubo25(); 
            contornocubo26(); 
            contornocubo27(); 
        } else if(tipoMovimiento == 2 && columnaSeleccionada == 0) {
            //columna izquierda (0-3-6) - rotar verticalmente.
            if(inverso==0) {
                glRotatef(-theta,1.0,0.0,0.0); 
            } 
            else {
                glRotatef(theta,1.0,0.0,0.0); 
            } 
            contornocubo2(); 
            contornocubo12(); 
            contornocubo3(); 
            contornocubo8(); 
            contornocubo16(); 
            contornocubo17(); 
            contornocubo20(); 
            contornocubo21(); 
            contornocubo24(); 
            contornocubo25(); 
        } else {
            //rotación completa de cara inferior.
            if(inverso==0) {
                glRotatef(theta,0.0,1.0,0.0); 
            } 
            else {
                glRotatef(-theta,0.0,1.0,0.0); 
            } 
            contornocubo2(); 
            contornocubo12(); 
            contornocubo13(); 
            contornocubo14(); 
            contornocubo15(); 
            contornocubo24(); 
            contornocubo25(); 
            contornocubo26(); 
            contornocubo27(); 
        }
    }
     
    glPopMatrix(); 
    glFlush(); 
    glutSwapBuffers(); 
}

//transpone los elementos de una cara del cubo de rubik según el carácter especificado.
void transponer(char a) {  
    if(a == 'r' || a == 'R') { 
        int temp; 
        temp = derecha[0][0]; 
        derecha[0][0] = derecha[2][0]; 
        derecha[2][0] = derecha[2][2]; 
        derecha[2][2] = derecha[0][2]; 
        derecha[0][2] = temp; 
        temp = derecha[1][0]; 
        derecha[1][0] = derecha[2][1]; 
        derecha[2][1] = derecha[1][2]; 
        derecha[1][2] = derecha[0][1]; 
        derecha[0][1] = temp;  
    } 

    if(a=='t' || a == 'T') { 
        int temp; 
        temp=superior[0][0]; 
        superior[0][0]=superior[2][0]; 
        superior[2][0]=superior[2][2]; 
        superior[2][2]=superior[0][2]; 
        superior[0][2]=temp; 
        temp=superior[1][0]; 
        superior[1][0]=superior[2][1]; 
        superior[2][1]=superior[1][2]; 
        superior[1][2]=superior[0][1]; 
        superior[0][1]=temp; 
    } 
    if(a=='f' || a == 'F') { 
        int temp; 
        temp=frente[0][0]; 
        frente[0][0]=frente[2][0]; 
        frente[2][0]=frente[2][2]; 
        frente[2][2]=frente[0][2]; 
        frente[0][2]=temp; 
        temp=frente[1][0]; 
        frente[1][0]=frente[2][1]; 
        frente[2][1]=frente[1][2]; 
        frente[1][2]=frente[0][1]; 
        frente[0][1]=temp; 
    } 
    if(a=='l' || a == 'L') { 
        int temp; 
        temp=izquierda[0][0]; 
        izquierda[0][0]=izquierda[2][0]; 
        izquierda[2][0]=izquierda[2][2]; 
        izquierda[2][2]=izquierda[0][2]; 
        izquierda[0][2]=temp; 
        temp=izquierda[1][0]; 
        izquierda[1][0]=izquierda[2][1]; 
        izquierda[2][1]=izquierda[1][2]; 
        izquierda[1][2]=izquierda[0][1]; 
        izquierda[0][1]=temp; 
    } 
    if(a=='k' || a == 'K') { 
        int temp; 
        temp=trasero[0][0]; 
        trasero[0][0]=trasero[2][0]; 
        trasero[2][0]=trasero[2][2]; 
        trasero[2][2]=trasero[0][2]; 
        trasero[0][2]=temp; 
        temp=trasero[1][0]; 
        trasero[1][0]=trasero[2][1]; 
        trasero[2][1]=trasero[1][2]; 
        trasero[1][2]=trasero[0][1]; 
        trasero[0][1]=temp; 
    } 
    if(a=='b' || a == 'B') { 
        int temp; 
        temp=abajo[0][0]; 
        abajo[0][0]=abajo[2][0]; 
        abajo[2][0]=abajo[2][2]; 
        abajo[2][2]=abajo[0][2]; 
        abajo[0][2]=temp; 
        temp=abajo[1][0]; 
        abajo[1][0]=abajo[2][1]; 
        abajo[2][1]=abajo[1][2]; 
        abajo[1][2]=abajo[0][1]; 
        abajo[0][1]=temp; 
    } 
}

//rota solo una fila específica del cubo de rubik.
void rotarFila(int fila) {
	if(fila == 0) {
		//fila superior (0-1-2).
		int temp1=frente[0][0];
		int temp2=frente[0][1];
		int temp3=frente[0][2];
		frente[0][0]=derecha[0][0];
		frente[0][1]=derecha[0][1];
		frente[0][2]=derecha[0][2];
		derecha[0][0]=trasero[0][0];
		derecha[0][1]=trasero[0][1];
		derecha[0][2]=trasero[0][2];
		trasero[0][0]=izquierda[0][0];
		trasero[0][1]=izquierda[0][1];
		trasero[0][2]=izquierda[0][2];
		izquierda[0][0]=temp1;
		izquierda[0][1]=temp2;
		izquierda[0][2]=temp3;
	} else if(fila == 2) {
		//fila inferior (6-7-8).
		int temp1=frente[2][0];
		int temp2=frente[2][1];
		int temp3=frente[2][2];
		frente[2][0]=izquierda[2][0];
		frente[2][1]=izquierda[2][1];
		frente[2][2]=izquierda[2][2];
		izquierda[2][0]=trasero[2][0];
		izquierda[2][1]=trasero[2][1];
		izquierda[2][2]=trasero[2][2];
		trasero[2][0]=derecha[2][0];
		trasero[2][1]=derecha[2][1];
		trasero[2][2]=derecha[2][2];
		derecha[2][0]=temp1;
		derecha[2][1]=temp2;
		derecha[2][2]=temp3;
	}
}

//rota solo una columna específica del cubo de rubik.
void rotarColumna(int columna) {
	if(columna == 0) {
		//columna izquierda (0-3-6).
		int temp1=frente[0][0];
		int temp2=frente[1][0];
		int temp3=frente[2][0];
		frente[0][0]=superior[0][0];
		frente[1][0]=superior[1][0];
		frente[2][0]=superior[2][0];
		superior[0][0]=trasero[2][2];
		superior[1][0]=trasero[1][2];
		superior[2][0]=trasero[0][2];
		trasero[2][2]=abajo[0][0];
		trasero[1][2]=abajo[1][0];
		trasero[0][2]=abajo[2][0];
		abajo[0][0]=temp1;
		abajo[1][0]=temp2;
		abajo[2][0]=temp3;
	} else if(columna == 2) {
		//columna derecha (2-5-8).
		int temp1=superior[0][2];
		int temp2=superior[1][2];
		int temp3=superior[2][2];
		superior[0][2]=frente[0][2];
		superior[1][2]=frente[1][2];
		superior[2][2]=frente[2][2];
		frente[0][2]=abajo[0][2];
		frente[1][2]=abajo[1][2];
		frente[2][2]=abajo[2][2];
		abajo[0][2]=trasero[2][0];
		abajo[1][2]=trasero[1][0];
		abajo[2][2]=trasero[0][0];
		trasero[2][0]=temp1;
		trasero[1][0]=temp2;
		trasero[0][0]=temp3;
	}
}

//rota la cara superior del cubo de rubik en sentido horario.
void arribac() { 
	transponer('T'); 
	int temp1=frente[0][0]; 
	int temp2=frente[0][1]; 
	int temp3=frente[0][2]; 

	frente[0][0]=derecha[0][0]; 
	frente[0][1]=derecha[0][1]; 
	frente[0][2]=derecha[0][2]; 
	 
	derecha[0][0]=trasero[0][0]; 
	derecha[0][1]=trasero[0][1]; 
	derecha[0][2]=trasero[0][2]; 
	 
	trasero[0][0]=izquierda[0][0]; 
	trasero[0][1]=izquierda[0][1]; 
	trasero[0][2]=izquierda[0][2]; 
	 
	izquierda[0][0]=temp1; 
	izquierda[0][1]=temp2; 
	izquierda[0][2]=temp3; 
} 

//rota la cara frontal del cubo de rubik en sentido horario.
void frentec() { 
    transponer('F'); 
    int temp1=izquierda[0][2]; 
    int temp2=izquierda[1][2]; 
    int temp3=izquierda[2][2]; 
     
    izquierda[0][2]=abajo[0][0]; 
    izquierda[1][2]=abajo[0][1]; 
    izquierda[2][2]=abajo[0][2]; 
     
    abajo[0][0]=derecha[2][0]; 
    abajo[0][1]=derecha[1][0]; 
    abajo[0][2]=derecha[0][0]; 
     
    derecha[2][0]=superior[2][2]; 
    derecha[1][0]=superior[2][1]; 
    derecha[0][0]=superior[2][0]; 
     
    superior[2][2]=temp1; 
    superior[2][1]=temp2; 
    superior[2][0]=temp3; 
}

//rota la cara derecha del cubo de rubik en sentido horario.
void derechac() { 
	transponer('R'); 
	int temp1=superior[0][2]; 
	int temp2=superior[1][2]; 
	int temp3=superior[2][2]; 
	 
	superior[0][2]=frente[0][2]; 
	superior[1][2]=frente[1][2]; 
	superior[2][2]=frente[2][2]; 
	 
	frente[0][2]=abajo[0][2]; 
	frente[1][2]=abajo[1][2]; 
	frente[2][2]=abajo[2][2]; 
	 
	abajo[0][2]=trasero[2][0]; 
	abajo[1][2]=trasero[1][0]; 
	abajo[2][2]=trasero[0][0]; 
	 
	trasero[2][0]=temp1; 
	trasero[1][0]=temp2; 
	trasero[0][0]=temp3; 
} 

//rota la cara izquierda del cubo de rubik en sentido horario.
void izquierdac() { 
	transponer('L'); 
	int temp1=frente[0][0]; 
	int temp2=frente[1][0]; 
	int temp3=frente[2][0]; 
	 
	frente[0][0]=superior[0][0]; 
	frente[1][0]=superior[1][0]; 
	frente[2][0]=superior[2][0]; 

	superior[0][0]=trasero[2][2]; 
	superior[1][0]=trasero[1][2]; 
	superior[2][0]=trasero[0][2]; 
	 
	trasero[2][2]=abajo[0][0]; 
	trasero[1][2]=abajo[1][0]; 
	trasero[0][2]=abajo[2][0]; 

	abajo[0][0]=temp1; 
	abajo[1][0]=temp2; 
	abajo[2][0]=temp3;  
} 

//rota la cara trasera del cubo de rubik en sentido horario.
void atrasc() { 
	transponer('K'); 
	int temp1=superior[0][0]; 
	int temp2=superior[0][1]; 
	int temp3=superior[0][2]; 
	 
	superior[0][0]=derecha[0][2]; 
	superior[0][1]=derecha[1][2]; 
	superior[0][2]=derecha[2][2]; 
	 
	derecha[0][2]=abajo[2][2]; 
	derecha[1][2]=abajo[2][1]; 
	derecha[2][2]=abajo[2][0]; 

	abajo[2][2]=izquierda[2][0]; 
	abajo[2][1]=izquierda[1][0]; 
	abajo[2][0]=izquierda[0][0]; 

	izquierda[2][0]=temp1; 
	izquierda[1][0]=temp2; 
	izquierda[0][0]=temp3; 
} 

//rota la cara inferior del cubo de rubik en sentido horario.
void abajoc() { 
	transponer('B'); 
	int temp1=frente[2][0]; 
	int temp2=frente[2][1]; 
	int temp3=frente[2][2]; 

	frente[2][0]=izquierda[2][0]; 
	frente[2][1]=izquierda[2][1]; 
	frente[2][2]=izquierda[2][2]; 

	izquierda[2][0]=trasero[2][0]; 
	izquierda[2][1]=trasero[2][1]; 
	izquierda[2][2]=trasero[2][2]; 

	trasero[2][0]=derecha[2][0]; 
	trasero[2][1]=derecha[2][1]; 
	trasero[2][2]=derecha[2][2]; 

	derecha[2][0]=temp1; 
	derecha[2][1]=temp2; 
	derecha[2][2]=temp3; 
} 

//función de animación que controla la rotación automática de las caras del cubo.
void giro() {
	theta+=1.0; 
	if(theta>=360.0) 
		theta-=360.0; 
	if(theta>=90.0) { 
		rotacion_completa=1; 
		glutIdleFunc(NULL); 
		if(rotacion==1&&inverso==0) { 
			arribac(); 
		} 
		if(rotacion==1&&inverso==1) { 
			arribac(); 
			arribac(); 
			arribac(); 
		} 
		if(rotacion==2&&inverso==0) { 
			derechac(); 
		} 
		if(rotacion==2&&inverso==1) { 
			derechac(); 
			derechac(); 
			derechac(); 
		} 
		if(rotacion==3&&inverso==0) { 
			frentec(); 
		} 
		if(rotacion==3&&inverso==1) { 
			frentec(); 
			frentec(); 
			frentec(); 
		} 
		if(rotacion==4&&inverso==0) { 
			izquierdac(); 
		} 
		if(rotacion==4&&inverso==1) { 
			izquierdac(); 
			izquierdac(); 
			izquierdac(); 
		} 
		if(rotacion==5&&inverso==0) { 
			atrasc(); 
		} 
		if(rotacion==5&&inverso==1) { 
			atrasc(); 
			atrasc(); 
			atrasc(); 
		} 
		if(rotacion==6&&inverso==0) { 
			abajoc(); 
		} 
		if(rotacion==6&&inverso==1) { 
			abajoc(); 
			abajoc(); 
			abajoc(); 
		} 
		rotacion=0; 
		theta=0;  
	}  
	glutPostRedisplay(); 
} 

//maneja el movimiento del mouse para rotar la vista del cubo.
void mover(int x, int y) {
	//rotar la vista del cubo con clic derecho.
	if(mouseRotacionVista) { 
		q=q + (x - iniciox); 
		iniciox = x; 
		p=p + (y - inicioy); 
		inicioy=y; 
		glutPostRedisplay(); 
	}
} 

//maneja los eventos del mouse incluyendo clicks y scroll para controlar el cubo.
void mouse(int btn,int state,int x,int y) { 
	//clic derecho: rotar la vista del cubo.
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) {
		mouseRotacionVista = 1;
		iniciox = x;
		inicioy = y;
	}
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_UP) {
		mouseRotacionVista = 0;
	}
	
	//manejo del scroll del mouse (zoom) para el cubo de rubik.
	if(btn == 3 && state == GLUT_DOWN) { //GLUT_WHEEL_UP
		cuboRubikScale += 0.1;
		if(cuboRubikScale > 3.0) cuboRubikScale = 3.0;
		glutPostRedisplay();
	}
	if(btn == 4 && state == GLUT_DOWN) { //GLUT_WHEEL_DOWN
		cuboRubikScale -= 0.1;
		if(cuboRubikScale < 0.3) cuboRubikScale = 0.3;
		glutPostRedisplay();
	}
} 

//maneja las teclas del teclado para rotar las caras del cubo.
void keyboard(unsigned char key, int x, int y) {
	if(((key=='a') || (key == 'A')) && rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=1; 
		inverso=0; 
		glutIdleFunc(giro); 
	} 
	if(((key=='q') || (key == 'Q')) && rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=1; 
		inverso=1; 
		glutIdleFunc(giro); 
	} 
	if(((key=='s') || (key == 'S')) && rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=2; 
		inverso=0; 
		glutIdleFunc(giro); 
	} 
	if(((key=='w') || (key == 'W')) && rotacion_completa==1) {
		rotacion_completa=0;
		rotacion=2; 
		inverso=1; 
		glutIdleFunc(giro); 
	} 
	if(((key=='d') || (key == 'D')) && rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=3; 
		inverso=0; 
		glutIdleFunc(giro); 
	} 
	if(((key=='e') || (key == 'E')) && rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=3; 
		inverso=1; 
		glutIdleFunc(giro); 
	} 
	if(((key=='f') || (key == 'F')) && rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=4; 
		inverso=0; 
		glutIdleFunc(giro); 
	} 
	if(((key=='r') || (key == 'R')) && rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=4; 
		inverso=1; 
		glutIdleFunc(giro); 
	} 
	if(((key=='g') || (key == 'G')) && rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=5; 
		inverso=0; 
		glutIdleFunc(giro); 
	} 
	if(((key=='t') || (key == 'T')) && rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=5; 
		inverso=1; 
		glutIdleFunc(giro); 
	} 
	if(((key=='h') || (key == 'H')) && rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=6; 
		inverso=0; 
		glutIdleFunc(giro); 
	} 
	if(((key=='y') || (key == 'Y')) && rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=6; 
		inverso=1; 
		glutIdleFunc(giro);  
	} 
}

//ajusta la proyección de la ventana cuando se redimensiona.
void myreshape(int w,int h) { 
	windowWidthRubik = w;
	windowHeightRubik = h;
	glViewport(0,0,w,h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	if (w <= h) 
		glOrtho(-10.0,10.0,-10.0*(GLfloat)h/(GLfloat)w, 10.0*(GLfloat)h/(GLfloat)w,-10.0,10.0); 
	else 
		glOrtho(-10.0*(GLfloat)w/(GLfloat)h, 10.0*(GLfloat)w/(GLfloat)h,-10.0,10.0,-10.0,10.0); 
	glMatrixMode(GL_MODELVIEW); 
}

//función principal que inicializa glut y crea la ventana del cubo de rubik.
int main(int argc, char** argv) {
    int cuborubik; //id de la ventana del cubo de rubik.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //ventana para el cubo de rubik.
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    cuborubik = glutCreateWindow("CUBO RUBIK.");
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(myreshape); 
    glutIdleFunc(giro); 
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse); 
    glutMotionFunc(mover); 
    glutDisplayFunc(display); 
    glEnable(GL_DEPTH_TEST); 
    glutMainLoop(); //iniciamos el bucle principal de glut.
    return 0;
}
