// Ayman JARI | Reda RAMZI | Abdou LAHAT SYLLA | Groupe TP5

#include <stdio.h>
#include <stdlib.h>
#include "AlgoAVL.h"


void initialiserM(M * m, Grille * G){
  m->tab = (AVL **) malloc (sizeof (AVL *) * G->nbcoul);
  for (int i = 0; i < G->nbcoul; i++){
    m->tab[i] = (AVL *) malloc (sizeof (AVL) * G->m);
  }
}

void remplirM(M *m,Grille * G){
  int i,j;int c = 0;
  while(c < G->nbcoul){
    for ( i = 0; i < G->m; i++) {
      for ( j = 0; j < G->n; j++) {
        if(G->T[i][j].fond==c &&(G->T[i][j].fond!=G->T[i][j].piece) ){
          insert_AVL(&(m->tab[c][i]),j);
        }
      }
    }
    c++;
  }
}

void libererM(M * m, Grille * G){
  for(int x = 0; x < G->nbcoul; x++){
    for(int y = 0; y < G->m; y++){
      free_tree_AVL(m->tab[x][y]);
    }
  }
}

void RechherchePlusProcheCase(M * m, Grille * G, int * k, int * l){
  int resk,resl;int y = 0;
  while ( m->tab[G->T[G->ir][G->jr].robot][y] == NULL ) {
    y++;
  }
  resk = y ;
  resl = AVLPlusProcheCase(m->tab[G->T[G->ir][G->jr].robot][y],G->ir,G->jr);
  int x;
  for (x = 0; x < G->m; x++) {
    if (m->tab[G->T[G->ir][G->jr].robot][x] != NULL) {

      if (TailleChemin(x,AVLPlusProcheCase(m->tab[G->T[G->ir][G->jr].robot][x],G->ir,G->jr),G->ir,G->jr) < TailleChemin(resk,resl,G->ir,G->jr)){
        resk = x;
        resl = AVLPlusProcheCase(m->tab[G->T[G->ir][G->jr].robot][x],G->ir,G->jr);

      }
    }
  }
  *k = resk ;
  *l = resl;

}

void algorithme_avl(Grille * G, Solution * S){
  M m;
  initialiserM(&m, G);
  remplirM(&m, G);
  int k, l;
  while(G->cptr_noire != G->n * G->m ){
      if(G->T[G->ir][G->jr].robot == -1){
        RechercheCaseNaif_nn(G, G->ir, G->jr, &k, &l);
      }
      else{
        RechherchePlusProcheCase(&m, G,&k, &l);
        delete_AVL(&(m.tab[G->T[G->ir][G->jr].robot][k]), l);
      }
      PlusCourtChemin(S, G->ir, G->jr, k, l);
      changement_case(G, k, l);
      Ajout_action(S, 'S');
      swap_case(G);
  }
  libererM(&m, G);
}
