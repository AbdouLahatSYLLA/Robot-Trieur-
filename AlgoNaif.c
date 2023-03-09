// Ayman JARI | Reda RAMZI | Abdou LAHAT SYLLA | Groupe TP5

#include "AlgoNaif.h"
#include <stdlib.h>
#include <stdio.h>

//Question 1.1 -------------------------------------------------------------------

/*
Prouvons, par induction sur un entier n, que pour tout chemin de longueur n allant
d'une case (j,l) à une case (k,l), la distance (|i-k|+|j-l|) est inférieure ou égale
à n.

Cas de base : n = 0

Si la longueur d'un chemin allant d'une case (i,j) à une case (k,l) est n = 0,
cela signifie que les cases (i,j) et (k,l) sont confondues et qu'on a alors i = k
et j = l.
Donc |i-k|+|j-l| <= n,
<=> |i-i|+|j-j| <= n (car k = i et l = j)
<=> 0 <= 0

Ceci est vrai donc l'induction est vérifiée pour n = 0.

Induction : Supposons que |i-k|+|j-l| <= n, montrons alors que |i-k|+|j-l| <= n+1.

|i-k|+|j-l| <= n
<=> |i-k|+|j-l| <= n+1 (car n < n+1 comme n >= 0)

Conclusion :

Nous avons donc prouvé, par induction sur un entier n, que pour tout chemin de
longueur n allant d'une case (j,l) à une case (k,l), la distance (|i-k|+|j-l|) est
inférieure ou égale à n.
*/

//Question 1.2 -------------------------------------------------------------------

void PlusCourtChemin(Solution * S, int i, int j, int k, int l){
    int difflig = k - i;
    int diffcol = l - j;
    if(difflig > 0){
        for(int x = 0; x < difflig; x++){
            Ajout_action(S, 'D');
        }
    }
    else{
        for(int x = 0; x > difflig; x--){
            Ajout_action(S, 'U');
        }
    }
    if(diffcol > 0){
        for(int x = 0; x < diffcol; x++){
            Ajout_action(S, 'R');
        }
    }
    else{
        for(int x = 0; x > diffcol; x--){
            Ajout_action(S, 'L');
        }
    }
}
//Question 1.3 -------------------------------------------------------------------

/*
a) Si la condition (G.T[i][j].fond == G.T[i][j].piece) est vraie,
alors la case située à la i-ème colonne à la j-ème ligne est noire.

b) Si la condition (G.T[i][j].piece != -1) est vraie, alors la pièce
de la case située à la i-ème ligne à la j-ème colonne n'est pas
noire.

c) Si la condition (G.T[G.ir][G.jr].robot == -1) est vraie, alors
le robot ne porte pas de pièce.

d) Dans le cas où le robot porte une pièce, la couleur de cette
pièce est G.T[G.ir][G.jr].robot.
*/

//Question 1.4 -------------------------------------------------------------------

int TailleChemin(int i, int j, int k, int l){
    int ligne = k - i;
    int colonne = l - j;
    if(ligne < 0){
        ligne = - ligne;
    }
    if(colonne < 0){
        colonne = - colonne;
    }
    return ligne + colonne;
}

void RechercheCaseNaif_c(Grille * G, int c, int i, int j, int * k, int * l){
  int resk, resl;
  int trouve = 0;
  for(int x = 0; x < G->m; x++){
    for(int y = 0; y < G->n; y++){
      if(G->T[x][y].fond == c && G->T[x][y].fond != G->T[x][y].piece){
        if(trouve){
          if(TailleChemin(i, j, x, y) < TailleChemin(i, j, resk, resl)){
            resk = x;
            resl = y;
          }
        }
        else{
          resk = x;
          resl = y;
          trouve = 1;
        }
      }
    }
  }
  *k = resk;
  *l = resl;
}

void RechercheCaseNaif_nn(Grille * G, int i, int j, int * k, int * l){
  int resk, resl;
  int trouve = 0;
  for(int x = 0; x < G->m; x++){
    for(int y = 0; y < G->n; y++){
      if(G->T[x][y].piece != -1 && G->T[x][y].fond != G->T[x][y].piece){
        if(trouve){
          if(TailleChemin(i, j, x, y) < TailleChemin(i, j, resk, resl)){
            resk = x;
            resl = y;
          }
        }
        else{
          resk = x;
          resl = y;
          trouve = 1;
        }
      }
    }
  }
  *k = resk;
  *l = resl;
}

//Question 1.5 -------------------------------------------------------------------

void algorithme_naif(Grille * G, Solution * S){
    int k, l;
    while(G->cptr_noire != G->n * G->m){
        if(G->T[G->ir][G->jr].robot == -1){
            RechercheCaseNaif_nn(G, G->ir, G->jr, &k, &l);
        }
        else{
            RechercheCaseNaif_c(G, G->T[G->ir][G->jr].robot, G->ir, G->jr, &k, &l);
        }
        PlusCourtChemin(S, G->ir, G->jr, k, l);
        changement_case(G, k, l);
        Ajout_action(S, 'S');
        swap_case(G);
    }
}

//Question 1.6 -------------------------------------------------------------------

/*
La fonction donne des solutions correctes pour des grilles de petite taille et
les grilles pour lesquelles elles fonctionnent en moins de 30 secondes ont
jusqu'à 120.000 cases environ.
*/

//Question 1.7 -------------------------------------------------------------------



//Question 1.8 -------------------------------------------------------------------

/*
Notre code est bien organisé, nous avons crée un programme main.c qui lors de son
exécution prend en paramètres un nombre de lignes, un nombre de colonnes, un
nombre de couleurs, un numéro de graine ainsi qu'un numéro de méthode. Le programme
va alors nous donner une solution S en fonction de la grille et de la méthode choisies
et va l'afficher sur le terminal et l'écrire sur le disque. La méthode dite "naïve"
correspond au numéro 1.
*/
