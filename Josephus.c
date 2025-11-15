#include <stdio.h>
#include <stdlib.h>
#include<time.h>

typedef struct nodo {
  int dato;
  struct nodo *sgt;
} Nodo;



void insert(Nodo **, int);
void printReverse(Nodo *aux);
Nodo *buscar(Nodo *, int);
void print(Nodo *aux);

const char ESTUDIANTES[36][50] = {"AVILA TORRUCO EDUARDO",
"BECERRA MONDRAGON RAYMUNDO ",
"BERMUDEZ JIMENEZ ERIKA YARETH",
"BRAVO IBAÑEZ LUIS FERNANDO ",
"CAMACHO VERGARA DANIEL GUILLERMO",
"CONTRERAS MATLA LUIS FERNANDO ",
"CONTRERAS SANTOS RICARDO ",
"CORTEZ MORENO JULIO CESAR ",
"CUETO SUNUN GLENDI MICHELLE ",
"FERNANDEZ SANTIAGO JOSE ",
"FIGUEROA MONROY EMILIANO ",
"GALINDO CASTILLO DALIA JULISSA ",
"GARCIA ARCOS KENEDY ALONSO ",
"GARCIA LOPEZ EDUARDO ",
"GARCIA VELANDIA SAMUEL OBED ",
"GARIN PEREZ JACQUELINNE ",
"GOMEZ MUCIÑO ROBERTO ",
"GUEVARA MORALES RUBEN SAID ",
"HERNANDEZ TASSINARI JOSSELYN ",
"HERRERA SANCHEZ DAMARA ELIZABETH",
"LAGUNES ALVAREZ ROBERTO ",
"LAGUNES CEBALLOS YAHIR ",
"LOPEZ RODRIGUEZ JESUS EDUARDO ",
"MARISCAL FRANCISCO KARLA OFELIA ",
"MEDINA TAFOLLA JORDAN ",
"MURGUIA PAVAN DANIEL DE JESUS ",
"PEREDA CATANA DORISOL DE LOS ANGELES",
"POLICARPIO MORAN MICHELL ALEXIS ",
"REYNA CANCIO NERU ",
"RIOS VALTIERRA BRYANT ALVIERY ",
"SIXTEGA ESCRIBANO MIGUEL ANGEL ",
"TEJEDA HUERTA DENISS ALEXIS",
"VALDES PALMERO JAIR DE JESUS ",
"VILLAR CAPARROSO JOSE ANTONIO ",
"YEPEZ RICARDEZ MAURICIO ",
"ZAMUDIO BARRAN CARLOS RODOLFO "};

Nodo *createNodo(int dato) {
  Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
  if (!nodo)
    return NULL;

  nodo->dato = dato;
  nodo->sgt = nodo;
  return nodo;
}

// Apuntando siempre al último insertado
void insertC(Nodo **DP, int dato) {
  Nodo *newNodo = createNodo(dato);
  if (!newNodo)
    return;

  if (*DP) {
    newNodo->sgt = (*DP)->sgt;
    (*DP)->sgt = newNodo;
  }
  *DP = newNodo;
}

Nodo *getNodoC(Nodo *lc, int datoABuscar) {
  Nodo *temp = lc;
  if (!temp)
    return NULL;

  do {
    if (temp->sgt->dato == datoABuscar)
      return temp;
    temp = temp->sgt;
  } while (temp != lc);

  return NULL;
}

void eliminarNodo(Nodo **lc, Nodo *anteriorB) {
  Nodo *nodoAEliminar = anteriorB->sgt;
  if (anteriorB == nodoAEliminar) {
    *lc = NULL;
    free(nodoAEliminar);
    return;
  }
  if (nodoAEliminar == *lc) {
    *lc = anteriorB;
  }

  anteriorB->sgt = nodoAEliminar->sgt;
  free(nodoAEliminar);
}

// Sólo acepta números del 2 al ..
Nodo *josephus(Nodo **lc, int c) {
  Nodo *actual = *lc;
  if (!actual)
    return NULL;

  int cont = c;

  while (actual != actual->sgt) {
    if (cont == 2) {
      eliminarNodo(
          lc,
          actual); // le estoy mandando el nodo anterior al que quiero eliminar
      cont = c;
    } else {
      cont--;
    }
    actual = actual->sgt;
  }
  return actual;
}

// Imprimir en orden de llegada
void printC(Nodo *lc) {
  Nodo *temp = lc;
  if (!temp)
    return;

  temp = lc->sgt;

  do {
    printf("%d %s ", temp->dato, temp != lc ? "->" : "");
    temp = temp->sgt;
  } while (temp != lc->sgt);
}

int main() {
  Nodo *listaCircular = NULL;
  srand(time(NULL));

  
  int inicioRand = rand() % 36 + 1;
  
  for (int i = 0; i < 36; i++)
    insertC(&listaCircular, i);

  while(inicioRand > 0){
    listaCircular = listaCircular->sgt;
    inicioRand--;
  }
  
  
  int id = josephus(&listaCircular, 2012)->dato;
  printf("%s siendo el número %d en la lista", ESTUDIANTES[id], id + 1);
  return 0;
}