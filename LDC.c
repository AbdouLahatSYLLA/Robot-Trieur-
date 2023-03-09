// Ayman JARI | Reda RAMZI | Abdou LAHAT SYLLA | Groupe TP5

#include <stdlib.h>
#include <stdio.h>
#include "LDC.h"

/* implémentation des fonctions de la Question 3.1*/
/* qui alloue et retourne une cellule*/
CelluleLDC * creerCellule (int i , int j ){
  CelluleLDC * res = (CelluleLDC*)malloc(sizeof(CelluleLDC));
  res->i = i;
  res->j = j;
  res->prec = NULL;
  res->suiv = NULL;
  return res;
}


/* qui initialise une liste */
void LDCInitialise ( LDC * ldc ) {

  ldc->premier = NULL;
  ldc->dernier = NULL;
}


/* qui teste si la liste est vide */
int LDCVide ( LDC * ldc ) {

  if(ldc->premier==NULL && ldc->dernier==NULL )
    return 1;
  return 0;
}


/* qui insere une nouvelle cellule en fin */
void LDCInsererEnFin ( LDC * ldc , int i , int j ) {

  CelluleLDC * cel = creerCellule(i, j);

  if(LDCVide(ldc)){
    ldc->premier = cel;
    ldc->dernier = cel;
  }
  else{
    ldc->dernier->suiv = cel;
    cel->prec = ldc->dernier;
    cel->suiv = NULL;
    ldc->dernier = cel;
  }
}


/* qui supprime une cellule a partir d un pointeur sur la cellule */
void LDCenleverCellule ( LDC * ldc , CelluleLDC * cel ) {
  CelluleLDC* a = cel->prec;
  CelluleLDC* b = cel->suiv;

  if(a == NULL)
    ldc->premier = b;
  else
    a->suiv = b;

  if(b == NULL)
    ldc->dernier = a;
  else
    b->prec = a;

  free(cel);
}


/* un affichage en cas de besoin pour debugage */
void LDCafficher ( LDC * ldc ) {
  CelluleLDC *cel;

  printf("Voici la liste :\n");
  for(cel=ldc->premier; cel!=NULL; cel=cel->suiv){
    printf("[ %d , %d ]", cel->i, cel->j);
  }
  printf("\n");
}


/* qui desalloue toute la liste (si elle n est pas vide a la fin) */
void LDCdesalloue ( LDC * ldc ) {

  CelluleLDC* cel;
  CelluleLDC* a;

  for(cel=ldc->premier; cel!=NULL; cel=cel->suiv){
    a = cel;
    a = a->suiv;
    free(a);
  }
  ldc->premier = NULL;
  ldc->dernier = NULL;
}
