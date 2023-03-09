// Ayman JARI | Reda RAMZI | Abdou LAHAT SYLLA | Groupe TP5

#include <stdlib.h>
#include <stdio.h>
#include "AlgoParCouleur.h"

//Question 3.1 -------------------------------------------------------------------

/*
Voir dans la bibliothèque "LDC.h".
*/

//Question 3.2 -------------------------------------------------------------------

CelluleLDC * LDCrechercherPlusProcheCase(LDC * ldc, int i, int j){
  CelluleLDC * cel = ldc->premier;
  CelluleLDC * res = ldc->premier;
  for(cel = ldc->premier->suiv; cel != NULL; cel = cel->suiv){
    if(TailleChemin(i, j, cel->i, cel->j) < TailleChemin(i, j,res->i, res->j)){
      res = cel;
    }
  }
  return res;
}

//Question 3.3 -------------------------------------------------------------------

void algorithme_parcouleur(Grille * G, Solution * S){
  LDC * TC = (LDC *) malloc(sizeof(LDC) * G->nbcoul);
  for(int coul = 0; coul < G->nbcoul; coul++){
    LDCInitialise(&TC[coul]);
    for(int x = 0; x < G->m; x++){
      for(int y = G->n - 1; y >=0; y--){
        if(G->T[x][y].fond == coul && G->T[x][y].fond != G->T[x][y].piece){
          LDCInsererEnFin(&TC[coul], x, y);
        }
      }
    }
  }
  int k, l;
  CelluleLDC * cel = (CelluleLDC *) malloc(sizeof(CelluleLDC));
  while(G->cptr_noire != G->n * G->m){
      if(G->T[G->ir][G->jr].robot == -1){
          RechercheCaseNaif_nn(G, G->ir, G->jr, &k, &l);
      }
      else{
          cel = LDCrechercherPlusProcheCase(&TC[G->T[G->ir][G->jr].robot], G->ir, G->jr);
          k = cel->i;
          l = cel->j;
          LDCenleverCellule(&TC[G->T[G->ir][G->jr].robot], cel);
      }
      PlusCourtChemin(S, G->ir, G->jr, k, l);
      changement_case(G, k, l);
      Ajout_action(S, 'S');
      swap_case(G);
  }
  for(int i = 0; i < G->nbcoul; i++){
    LDCdesalloue(&TC[i]);
  }
}
