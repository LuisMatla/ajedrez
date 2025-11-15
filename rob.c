#include <GL/glut.h>
#include<stdio.h> 
dibujar_tablero
static float velocidad=0.0;

static int superior[3][3]={{0,0,0},{0,0,0},{0,0,0}}, 
derecha[3][3]={{1,1,1},{1,1,1},{1,1,1}}, 
frente[3][3]={{2,2,2},{2,2,2},{2,2,2}}, 
trasero[3][3]={{3,3,3},{3,3,3},{3,3,3}}, 
abajo[3][3]={{4,4,4},{4,4,4},{4,4,4}}, 
izquierda[3][3]={{5,5,5},{5,5,5},{5,5,5}}, 
temp[3][3]; 
 
int registro[300]; 
int contar=0;  
static int rotacion=0; 
int rotacion_completa=0; 
static GLfloat theta=0.0; 
static GLfloat p=0.0,q=0.0,r=0.0; 
static GLint inverso=0;  
int iniciox=0,inicioy=0; 
int movimiento=0; 

 
GLfloat vertices[][3]={{-1.0,-1.0,-1.0}, 
 
                       {1.0,-1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, //center 
                       {-1.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                        
                       {-1.0,-3.0,-1.0}, 
                       {1.0,-3.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0},  //bottom center 
                       {-1.0,-3.0,1.0}, 
                       {1.0,-3.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                        
                       {-3.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-3.0,1.0,-1.0},  //left center 
                       {-3.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-3.0,1.0,1.0}, 

                       {1.0,-1.0,-1.0}, 
                       {3.0,-1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, // right center 
                       {1.0,-1.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, 
 
                       {-1.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {1.0,3.0,-1.0}, 
                       {-1.0,3.0,-1.0}, // top center 
                       {-1.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {1.0,3.0,1.0}, 
                       {-1.0,3.0,1.0}, 
 
                       {-1.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, //front center 

                       {-1.0,-1.0,3.0}, 
                       {1.0,-1.0,3.0}, 
                       {1.0,1.0,3.0}, 
                       {-1.0,1.0,3.0}, 
 
                       {-1.0,-1.0,-3.0}, 
                       {1.0,-1.0,-3.0}, 
                       {1.0,1.0,-3.0}, 
                       {-1.0,1.0,-3.0}, //back center 
                       {-1.0,-1.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
 
                       {-3.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-1.0,3.0,-1.0}, 
                       {-3.0,3.0,-1.0}, // top left center 
                       {-3.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-1.0,3.0,1.0}, 
                       {-3.0,3.0,1.0},  
                             
                       {1.0,1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 

                       {3.0,3.0,-1.0}, 
                       {1.0,3.0,-1.0}, // top right  center 
                       {1.0,1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {3.0,3.0,1.0}, 
                       {1.0,3.0,1.0}, 
 
                       {-1.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, 
                       {1.0,3.0,1.0}, 
                       {-1.0,3.0,1.0}, // top front center 
                       {-1.0,1.0,3.0}, 
                       {1.0,1.0,3.0}, 
                       {1.0,3.0,3.0}, 
                       {-1.0,3.0,3.0}, 
 
                       {-1.0,1.0,-3.0}, 
                       {1.0,1.0,-3.0}, 
                       {1.0,3.0,-3.0}, 
                       {-1.0,3.0,-3.0}, // top back center 
                       {-1.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
                       {1.0,3.0,-1.0}, 
                       {-1.0,3.0,-1.0}, 

        {-3.0,-3.0,-1.0}, 
                       {-1.0,-3.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-3.0,-1.0,-1.0},  //bottom left center 
                       {-3.0,-3.0,1.0}, 
                       {-1.0,-3.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                       {-3.0,-1.0,1.0}, 
 
        {1.0,-3.0,-1.0}, 
                       {3.0,-3.0,-1.0}, 
                       {3.0,-1.0,-1.0}, 
                       {1.0,-1.0,-1.0},  //bottom  right center 
                       {1.0,-3.0,1.0}, 
                       {3.0,-3.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0}, 
            
        {-1.0,-3.0,1.0}, 
                       {1.0,-3.0,1.0}, 
                       {1.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0},  //bottom front center 

                       {-1.0,-3.0,3.0}, 
                       {1.0,-3.0,3.0}, 
                       {1.0,-1.0,3.0}, 
                       {-1.0,-1.0,3.0}, 
 
                       {-1.0,-3.0,-3.0}, 
                       {1.0,-3.0,-3.0}, 
                       {1.0,-1.0,-3.0}, 
                       {-1.0,-1.0,-3.0},  //bottom back center 
                       {-1.0,-3.0,-1.0}, 
                       {1.0,-3.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
 
        {-3.0,1.0,-3.0}, 
                       {-1.0,1.0,-3.0}, 
                       {-1.0,3.0,-3.0}, 
                       {-3.0,3.0,-3.0}, // top left back 
                       {-3.0,1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-1.0,3.0,-1.0}, 
                       {-3.0,3.0,-1.0}, 
 
        {-3.0,1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-1.0,3.0,1.0}, 
                       {-3.0,3.0,1.0}, // top left front 
                       {-3.0,1.0,3.0}, 
                       {-1.0,1.0,3.0}, 
                       {-1.0,3.0,3.0}, 
                       {-3.0,3.0,3.0}, 
 
        {1.0,1.0,-3.0}, 
                       {3.0,1.0,-3.0}, 
                       {3.0,3.0,-3.0}, 
                       {1.0,3.0,-3.0}, // top right  back 
                       {1.0,1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 
                       {3.0,3.0,-1.0}, 
                       {1.0,3.0,-1.0}, 
 
        {1.0,1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {3.0,3.0,1.0}, 
                       {1.0,3.0,1.0}, // top right  front 
                       {1.0,1.0,3.0}, 
                       {3.0,1.0,3.0}, 
                       {3.0,3.0,3.0}, 

                       {1.0,3.0,3.0}, 
 
        {-3.0,-1.0,-3.0}, 
                       {-1.0,-1.0,-3.0}, 
                       {-1.0,1.0,-3.0}, 
                       {-3.0,1.0,-3.0},  //ceneter left back 
                       {-3.0,-1.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-1.0,1.0,-1.0}, 
                       {-3.0,1.0,-1.0}, 
 
        {-3.0,-1.0,1.0}, 
                       {-1.0,-1.0,1.0}, 
                       {-1.0,1.0,1.0}, 
                       {-3.0,1.0,1.0},  //center left front 
                       {-3.0,-1.0,3.0}, 
                       {-1.0,-1.0,3.0}, 
                       {-1.0,1.0,3.0}, 
                       {-3.0,1.0,3.0}, 
 
        {1.0,-1.0,-3.0}, 
                       {3.0,-1.0,-3.0}, 
                       {3.0,1.0,-3.0}, 
                       {1.0,1.0,-3.0}, // center right back 
                       {1.0,-1.0,-1.0}, 

                       {3.0,-1.0,-1.0}, 
                       {3.0,1.0,-1.0}, 
                       {1.0,1.0,-1.0}, 
 
        {1.0,-1.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {3.0,1.0,1.0}, 
                       {1.0,1.0,1.0}, // center right front 
                       {1.0,-1.0,3.0}, 
                       {3.0,-1.0,3.0}, 
                       {3.0,1.0,3.0}, 
                       {1.0,1.0,3.0}, 
 
        {-3.0,-3.0,-3.0}, 
                       {-1.0,-3.0,-3.0}, 
                       {-1.0,-1.0,-3.0}, 
                       {-3.0,-1.0,-3.0},  //bottom left back 
                       {-3.0,-3.0,-1.0}, 
                       {-1.0,-3.0,-1.0}, 
                       {-1.0,-1.0,-1.0}, 
                       {-3.0,-1.0,-1.0}, 
 
        {-3.0,-3.0,1.0}, 
                       {-1.0,-3.0,1.0}, 
                       {-1.0,-1.0,1.0}, 

                       {-3.0,-1.0,1.0},  //bottom left front 
                       {-3.0,-3.0,3.0}, 
                       {-1.0,-3.0,3.0}, 
                       {-1.0,-1.0,3.0}, 
                       {-3.0,-1.0,3.0}, 
 
        {1.0,-3.0,-3.0}, 
                       {3.0,-3.0,-3.0}, 
                       {3.0,-1.0,-3.0}, 
                       {1.0,-1.0,-3.0},  //bottom  right back 
                       {1.0,-3.0,-1.0}, 
                       {3.0,-3.0,-1.0}, 
                       {3.0,-1.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
            
        {1.0,-3.0,1.0}, 
                       {3.0,-3.0,1.0}, 
                       {3.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0},  //bottom  right front 
                       {1.0,-3.0,3.0}, 
                       {3.0,-3.0,3.0}, 
                       {3.0,-1.0,3.0}, 
                       {1.0,-1.0,3.0}, 
        {0.0,7.0,0.0}, 
        {0.0,7.5,0.0}, 
        {0.5,7.5,0.0}, //speed meter 
        {0.5,7.0,0.0}
}; 
                      
GLfloat color[][3]={{194.0 / 255.0, 178.0 / 255.0, 128.0 / 255.0}, //amarillo. 
                    {250.0 / 255.0, 128.0 / 255.0, 114.0 / 255.0},  //verde claro 
                    {0.956863, 0.643137, 0.376471},  //lila
                    {255.0 / 255.0, 204.0 / 255.0, 153.0 / 255.0},  //naranja claro
                    {127.0 / 255.0, 1.0, 212.0 / 255.0},  //agumarina
                    {219.0 / 255.0, 48.0 / 255.0, 122.0 / 255.0}, //rosa mexicano. 
		{0.0,0.0,0.0}, //grey used to represent faces of cube without colour 
};


void contornito(int a,int b,int c,int d,int e) {    
	glColor3f(1.0, 1.0, 1.0); 
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

void contornocubo1() { 
	contornito(6,0,3,2,1);  
	contornito(6,2,3,7,6);  
	contornito(6,0,4,7,3);    // center piece 
	contornito(6,1,2,6,5);            
	contornito(6,4,5,6,7); 
	contornito(6,0,1,5,4);  
}
 
void contornocubo2() { 
	contornito(6,8,11,10,9);  
	contornito(6,10,11,15,14);  
	contornito(6,8,12,15,11);    // bottom center 
	contornito(6,9,10,14,13);            
	contornito(6,12,13,14,15); 
	contornito(abajo[1][1],8,9,13,12);  
} 
 
void contornocubo3() { 
	contornito(6,16,19,18,17);  
	contornito(6,18,19,23,22);  
	contornito(izquierda[1][1],16,20,23,19);    // left center 
	contornito(6,17,18,22,21);            
	contornito(6,20,21,22,23); 
	contornito(6,16,17,21,20);  
} 
 
void contornocubo4() { 
	contornito(6,24,27,26,25);  
	contornito(6,26,27,31,30);  
	contornito(6,24,28,31,27);    // right center 
	contornito(derecha[1][1],25,26,30,29);            
	contornito(6,28,29,30,31); 
	contornito(6,24,25,29,28);  
} 
 
void contornocubo5() { 
	contornito(6,32,35,34,33);  
	contornito(superior[1][1],34,35,39,38);  
	contornito(6,32,36,39,35);    // top center 
	contornito(6,33,34,38,37);            
	contornito(6,36,37,38,39); 
	contornito(6,32,33,37,36);  
} 
 
void contornocubo6() { 
	contornito(6,40,43,42,41);  
	contornito(6,42,43,47,46);  
	contornito(6,40,44,47,43);    // front center 
	contornito(6,41,42,46,45);            
	contornito(frente[1][1],44,45,46,47); 
	contornito(6,40,41,45,44);  
} 
 
void contornocubo7() { 
	contornito(trasero[1][1],48,51,50,49);  
	contornito(6,50,51,55,54);  
	contornito(6,48,52,55,51);    //back center 
	contornito(6,49,50,54,53);            
	contornito(6,52,53,54,55); 
	contornito(6,48,49,53,52);  
} 

void contornocubo8() { 
	contornito(6,56,59,58,57);  
	contornito(superior[1][0],58,59,63,62);  
	contornito(izquierda[0][1],56,60,63,59);    // superior left center 
	contornito(6,57,58,62,61);            
	contornito(6,60,61,62,63); 
	contornito(6,56,57,61,60);  
} 

void contornocubo9() { 
	contornito(6,64,67,66,65);  
	contornito(superior[1][2],66,67,71,70);  
	contornito(6,64,68,71,67);    // superior right center 
	contornito(derecha[0][1],65,66,70,69);            
	contornito(6,68,69,70,71); 
	contornito(6,64,65,69,68);  
} 
 
void contornocubo10() { 
    contornito(6, 72, 75, 74, 73);  
    contornito(superior[2][1], 74, 75, 79, 78);  
    contornito(6, 72, 76, 79, 75);    // top front center 
    contornito(6, 73, 74, 78, 77);            
    contornito(frente[0][1], 76, 77, 78, 79); 
    contornito(6, 72, 73, 77, 76);  
} 

void contornocubo11() { 
    contornito(trasero[0][1], 80, 83, 82, 81);  
    contornito(superior[0][1], 82, 83, 87, 86);  
    contornito(6, 80, 84, 87, 83);    // top back center 
    contornito(6, 81, 82, 86, 85);            
    contornito(6, 84, 85, 86, 87); 
    contornito(6, 80, 81, 85, 84);  
} 

void contornocubo12() { 
    contornito(6, 80 + 8, 83 + 8, 82 + 8, 81 + 8);  
    contornito(6, 82 + 8, 83 + 8, 87 + 8, 86 + 8);  
    contornito(izquierda[2][1], 80 + 8, 84 + 8, 87 + 8, 83 + 8);    // bottom left center 
    contornito(6, 81 + 8, 82 + 8, 86 + 8, 85 + 8);            
    contornito(6, 84 + 8, 85 + 8, 86 + 8, 87 + 8); 
    contornito(abajo[1][0], 80 + 8, 81 + 8, 85 + 8, 84 + 8);  
} 

void contornocubo13() { 
    contornito(6, 80 + 16, 83 + 16, 82 + 16, 81 + 16);  
    contornito(6, 82 + 16, 83 + 16, 87 + 16, 86 + 16);  
    contornito(6, 80 + 16, 84 + 16, 87 + 16, 83 + 16);    // bottom right center 
    contornito(derecha[2][1], 81 + 16, 82 + 16, 86 + 16, 85 + 16);            
    contornito(6, 84 + 16, 85 + 16, 86 + 16, 87 + 16); 
    contornito(abajo[1][2], 80 + 16, 81 + 16, 85 + 16, 84 + 16);  
} 

void contornocubo14() { 
    contornito(6, 80 + 24, 83 + 24, 82 + 24, 81 + 24);  
    contornito(6, 82 + 24, 83 + 24, 87 + 24, 86 + 24);  
    contornito(6, 80 + 24, 84 + 24, 87 + 24, 83 + 24);    // bottom front center 
    contornito(6, 81 + 24, 82 + 24, 86 + 24, 85 + 24);            
    contornito(frente[2][1], 84 + 24, 85 + 24, 86 + 24, 87 + 24); 
    contornito(abajo[0][1], 80 + 24, 81 + 24, 85 + 24, 84 + 24);  
} 

void contornocubo15() { 
    contornito(trasero[2][1], 112, 115, 114, 113);  
    contornito(6, 114, 115, 119, 118);  
    contornito(6, 112, 116, 119, 115);    // bottom back center 
    contornito(6, 113, 114, 118, 117);            
    contornito(6, 116, 117, 118, 119); 
    contornito(abajo[2][1], 112, 113, 117, 116);  
} 

void contornocubo16() { 
    contornito(trasero[0][2], 120, 123, 122, 121);  
    contornito(superior[0][0], 122, 123, 127, 126);  
    contornito(izquierda[0][0], 120, 124, 127, 123);    // superior left back 
    contornito(6, 121, 122, 126, 125);            
    contornito(6, 124, 125, 126, 127); 
    contornito(6, 120, 121, 125, 124);  
} 

void contornocubo17() { 
    contornito(6, 128, 131, 130, 129);  
    contornito(superior[2][0], 130, 131, 135, 134);  
    contornito(izquierda[0][2], 128, 132, 135, 131);    // superior left front 
    contornito(6, 129, 130, 134, 133);            
    contornito(frente[0][0], 132, 133, 134, 135); 
    contornito(6, 128, 129, 133, 132);  
} 

void contornocubo18() { 
    contornito(trasero[0][0], 136, 139, 138, 137);  
    contornito(superior[0][2], 138, 139, 143, 142);  
    contornito(6, 136, 140, 143, 139);    // top right back 
    contornito(derecha[0][2], 137, 138, 142, 141);            
    contornito(6, 140, 141, 142, 143); 
    contornito(6, 136, 137, 141, 140);  
} 

void contornocubo19() { 
    contornito(6, 144, 147, 146, 145);  
    contornito(superior[2][2], 146, 147, 151, 150);  
    contornito(6, 144, 148, 151, 147);    // top right front 
    contornito(derecha[0][0], 145, 146, 150, 149);            
    contornito(frente[0][2], 148, 149, 150, 151); 
    contornito(6, 144, 145, 149, 148);  
} 

void contornocubo20() { 
    contornito(trasero[1][2], 152, 155, 154, 153);  
    contornito(6, 154, 155, 159, 158);  
    contornito(izquierda[1][0], 152, 156, 159, 155);    //center left back 
    contornito(6, 153, 154, 158, 157);            
    contornito(6, 156, 157, 158, 159); 
    contornito(6, 152, 153, 157, 156);  
} 

void contornocubo21() { 
    contornito(6, 160, 163, 162, 161);  
    contornito(6, 162, 163, 167, 166);  
    contornito(izquierda[1][2], 160, 164, 167, 163);    // center left front 
    contornito(6, 161, 162, 166, 165);            
    contornito(frente[1][0], 164, 165, 166, 167); 
    contornito(6, 160, 161, 165, 164);  
} 

void contornocubo22() { 
    contornito(trasero[1][0], 168, 171, 170, 169);  
    contornito(6, 170, 171, 175, 174);  
    contornito(6, 168, 172, 175, 171);    // center right back 
    contornito(derecha[1][2], 169, 170, 174, 173);            
    contornito(6, 172, 173, 174, 175); 
    contornito(6, 168, 169, 173, 172);  
} 

void contornocubo23() { 
    contornito(6, 176, 179, 178, 177);  
    contornito(6, 178, 179, 183, 182);  
    contornito(6, 176, 180, 183, 179);    //center right front 
    contornito(derecha[1][0], 177, 178, 182, 181);            
    contornito(frente[1][2], 180, 181, 182, 183); 
    contornito(6, 176, 177, 181, 180);  
} 

void contornocubo24() { 
    contornito(trasero[2][2], 184, 187, 186, 185);  
    contornito(6, 186, 187, 191, 190);  
    contornito(izquierda[2][0], 184, 188, 191, 187);    // bottom left back 
    contornito(6, 185, 186, 190, 189);            
    contornito(6, 188, 189, 190, 191); 
    contornito(abajo[2][0], 184, 185, 189, 188);  
} 

void contornocubo25() { 
    contornito(6, 192, 195, 194, 193);  
    contornito(6, 194, 195, 199, 198);  
    contornito(izquierda[2][2], 192, 196, 199, 195);    // bottom left front 
    contornito(6, 193, 194, 198, 197);            
    contornito(frente[2][0], 196, 197, 198, 199); 
    contornito(abajo[0][0], 192, 193, 197, 196);  
} 

void contornocubo26() { 
    contornito(trasero[2][0], 200, 203, 202, 201);  
    contornito(6, 202, 203, 207, 206);  
    contornito(6, 200, 204, 207, 203);    // bottom right back 
    contornito(derecha[2][2], 201, 202, 206, 205);            
    contornito(6, 204, 205, 206, 207); 
    contornito(abajo[2][2], 200, 201, 205, 204);  
}

void contornocubo27() { 
    contornito(6, 208, 211, 210, 209);  
    contornito(6, 210, 211, 215, 214);  
    contornito(6, 208, 212, 215, 211);    // bottom right front 
    contornito(derecha[2][0], 209, 210, 214, 213);            
    contornito(frente[2][2], 212, 213, 214, 215); 
    contornito(abajo[0][2], 208, 209, 213, 212);  
}


void display() { 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity(); 
	glColor3fv(color[0]); 
	glPushMatrix();
	glRotatef(25.0+p,1.0,0.0,0.0); 
	glRotatef(-30.0+q,0.0,1.0,0.0); 
	glRotatef(0.0+r,0.0,0.0,1.0);  

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

    if(rotacion==2) {  
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
     
    glPopMatrix(); 
    glPushMatrix(); 
    glTranslatef(-.5,-4,0); 
    glScalef(velocidad/4.5,1.0,1.0); 
    glTranslatef(0.5,4,0); 
    contornito(5,216,217,218,219); 
    glPopMatrix(); 
    glFlush(); 
    glutSwapBuffers(); 
}



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
    if(a=='l' || a ==  'L') { 
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
    if(a=='k' || a ==  'K') { 
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
 
 
  
void arribac() { 
	transponer('t' || 'T'); 
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
 
void frentec() { 
    transponer('f' || 'F'); 
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
 
 
void derechac() { 
	transponer('r' || 'R'); 
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
 
void izquierdac() { 
	transponer('l' || 'L'); 
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
 
void atrasc() { 
	transponer('k' || 'k'); 
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
 
void abajoc() { 
	transponer('b' || 'B'); 
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
 
 
void giro() {
	theta+=0.2+velocidad; 
	if(theta==360.0) 
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
 
 
void mover(int x, int y) {
	if(movimiento) { 
		q=q + (x - iniciox); 
		iniciox = x; 
		p=p + (y - inicioy); 
		inicioy=y; 
		glutPostRedisplay(); 
	} 
} 
 
 
void mouse(int btn,int state,int x,int y) { 
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)  {      
	} 
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {  
		if(x>=0&&x<=2&&y>=7&&y<=9) 
		{    
		} 
		
		movimiento = 1; 
		iniciox = x; 
		inicioy=y; 
	}  
} 
 
 
static void keyboard(unsigned char key,int x,int y) { 
	if(((key=='a') || (key == 'A'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=1; 
		inverso=0; 
		registro[++contar]=1; 
		glutIdleFunc(giro); 
	} 
	if(((key=='q') || (key == 'Q'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=1; 
		inverso=1; 
		registro[++contar]=-1; 
		glutIdleFunc(giro); 
	} 
	if(((key=='s') || (key == 'S'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=2; 
		inverso=0; 
		registro[++contar]=2; 
		glutIdleFunc(giro); 
	} 
	if(((key=='w') || (key == 'W'))&&rotacion_completa==1) {
		rotacion_completa=0;
		rotacion=2; 
		inverso=1; 
		registro[++contar]=-2; 
		glutIdleFunc(giro); 
	} 
	if(((key=='d') || (key == 'D'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=3; 
		inverso=0; 
		registro[++contar]=3; 
		glutIdleFunc(giro); 
	} 
	if(((key=='e') || (key == 'E'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=3; 
		inverso=1; 
		registro[++contar]=-3; 
		glutIdleFunc(giro); 
	} 
	if(((key=='f') || (key == 'F'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=4; 
		inverso=0; 
		registro[++contar]=4; 
		glutIdleFunc(giro); 
	} 
	if(((key=='r') || (key == 'R'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=4; 
		inverso=1; 
		registro[++contar]=-4; 
		glutIdleFunc(giro); 
	} 
	if(((key=='g') || (key == 'G'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=5; 
		inverso=0; 
		registro[++contar]=5; 
		glutIdleFunc(giro); 
	} 
	if(((key=='t') || (key == 'T'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=5; 
		inverso=1; 
		registro[++contar]=-5; 
		glutIdleFunc(giro); 
	} 
	if(((key=='h') || (key == 'H'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=6; 
		inverso=0; 
		registro[++contar]=6; 
		glutIdleFunc(giro); 
	} 
	if(((key=='y') || (key == 'Y'))&&rotacion_completa==1) {
		rotacion_completa=0; 
		rotacion=6; 
		inverso=1; 
		registro[++contar]=-6; 
		glutIdleFunc(giro);  
	} 
} 
 

void myreshape(int w,int h) { 
	glViewport(0,0,w,h); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	if (w <= h) 
		glOrtho(-10.0,10.0,-10.0*(GLfloat)h/(GLfloat)w, 10.0*(GLfloat)h/(GLfloat)w,-10.0,10.0); 
	else 
		glOrtho(-10.0*(GLfloat)w/(GLfloat)h, 10.0*(GLfloat)w/(GLfloat)h,-10.0,10.0,-10.0,10.0); 
	glMatrixMode(GL_MODELVIEW); 
}
 

void mymenu(int id) { 
	if(rotacion_completa==1) {
		rotacion_completa=0; 
		switch(id) { 
			case 0: glutIdleFunc(giro);
					break;
					
			case 1:
					rotacion=1; 
					inverso=0; 
					registro[++contar]=1; 
					glutIdleFunc(giro); 
					break; 

			case 2: 
					rotacion=1; 
					inverso=1; 
					registro[++contar]=-1; 
					glutIdleFunc(giro); 
					break; 

			case 3: 
					rotacion=2; 
					inverso=0; 
					registro[++contar]=2; 
					glutIdleFunc(giro); 
					break; 
			 
			case 4: 
					rotacion=2; 
					inverso=1; 
					registro[++contar]=-2; 
					glutIdleFunc(giro); 
					break; 

			case 5: 
					rotacion=3; 
					inverso=0; 
					registro[++contar]=3; 
					glutIdleFunc(giro); 
					break; 

			case 6: 
					rotacion=3; 
					inverso=1; 
					registro[++contar]=-3; 
					glutIdleFunc(giro); 
					break; 

			case 7: 
					rotacion=4; 
					inverso=0; 
					registro[++contar]=4; 
					glutIdleFunc(giro); 
					break; 

			case 8: 
					rotacion=4; 
					inverso=1; 
					registro[++contar]=-4; 
					glutIdleFunc(giro); 
					break; 

			case 9: 
					rotacion=5; 
					inverso=0; 
					registro[++contar]=5; 
					glutIdleFunc(giro); 
					break; 

			case 10: 
					rotacion=5; 
					inverso=1; 
					registro[++contar]=-5; 
					glutIdleFunc(giro); 
					break; 

			case 11: 
					rotacion=6; 
					inverso=0; 
					registro[++contar]=6; 
					glutIdleFunc(giro); 
					break; 

			case 12: 
				rotacion=6; 
				inverso=1; 
				registro[++contar]=-6; 
				glutIdleFunc(giro); 
				break; 
					  
			case 13: 
					exit(0); 
					break; 
		} 
	} 
}

 
int main(int argc, char** argv) { 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize(500, 500); 
	glutCreateWindow("RUBIK'S CUBE"); 
	glutReshapeFunc(myreshape); 
	glutIdleFunc(giro); 
	glutMouseFunc(mouse); 
	glutMotionFunc(mover); 
	glutCreateMenu(mymenu);
	
	glutAddMenuEntry("Orientation:",0);
	glutAddMenuEntry("Top                   :a",1); 
	glutAddMenuEntry("Top Inverted    :q",2); 
	glutAddMenuEntry("Right                 :s",3); 
	glutAddMenuEntry("Right Inverted  :w",4); 
	glutAddMenuEntry("Front                 :d",5); 
	glutAddMenuEntry("Front Inverted  :e",6); 
	glutAddMenuEntry("Left                   :f",7); 
	glutAddMenuEntry("Left Inverted    :r",8); 
	glutAddMenuEntry("Back                  :g",9); 
	glutAddMenuEntry("Back Inverted   :t",10); 
	glutAddMenuEntry("Bottom              :h",11); 
	glutAddMenuEntry("Bottom Inverted :y",12);
	glutAddMenuEntry("Reverse move	 :o",0);
	glutAddMenuEntry("",0);
	glutAddMenuEntry("Rotation Controls:",0);
	glutAddMenuEntry("X-Axis	:4 & 6",0);
	glutAddMenuEntry("Y-Axis	:2 & 8",0);
	glutAddMenuEntry("Z-Axis	:1 & 9",0);
	glutAddMenuEntry("Origin	:5",0);
	glutAddMenuEntry("",0);
	glutAddMenuEntry("Rotation Speed:",0);
	glutAddMenuEntry("Increase	 :m",0);
	glutAddMenuEntry("Decrease	 :n",0);
	glutAddMenuEntry("",0);
	glutAddMenuEntry("Exit",13); 
	
	glutAttachMenu(GLUT_RIGHT_BUTTON); 
	glutKeyboardFunc(keyboard); 
	glutDisplayFunc(display); 
	glEnable(GL_DEPTH_TEST); 
	glutMainLoop(); 
	return 0; 
}
