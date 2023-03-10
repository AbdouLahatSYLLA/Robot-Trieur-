// Ayman JARI | Reda RAMZI | Abdou LAHAT SYLLA | Groupe TP5

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "AlgoCirculaire.h"
#include "Grille.h"
#include "Solution.h"
#include "AlgoNaif.h"

/*________Question 2.1________*/
void RechercheCaseCirculaire_c(Grille *G, int c, int i, int j, int *k, int *l){
  int resk, lg, ld;
  int L = 0;

  while(L>=0){
    resk = i-L;
    lg = j;
    ld = j;

    while(resk<=i){
      if(resk>=0 && resk < G->m && lg>=0 && lg < G->n){
        if(G->T[resk][lg].fond == c && G->T[resk][lg].fond != G->T[resk][lg].piece){
          *k = resk;
          *l = lg;
          return;
        }
      }
      if(resk>=0 && resk < G->m && ld>=0 && ld < G->n){
        if(G->T[resk][ld].fond == c && G->T[resk][ld].fond != G->T[resk][ld].piece){
          *k = resk;
          *l = ld;
          return;
        }
      }
      resk = resk+1;
      lg = lg - 1;
      ld = ld + 1;
    }

    resk = i+1;
    lg = j - L + 1;
    ld = j + L - 1;

    while(resk<=i+L){
      if(resk>=0 && resk < G->m && lg>=0 && lg < G->n){
        if(G->T[resk][lg].fond == c && G->T[resk][lg].fond != G->T[resk][lg].piece){
          *k = resk;
          *l = lg;
          return;
        }
      }
      if(resk>=0 && resk < G->m && ld>=0 && ld < G->n){
        if(G->T[resk][ld].fond == c && G->T[resk][ld].fond != G->T[resk][ld].piece){
          *k = resk;
          *l = ld;
          return;
        }
      }
      resk = resk + 1;
      lg = lg + 1;
      ld = ld - 1;
    }
    L++;
  }
}

void RechercheCaseCirculaire_nn(Grille *G, int i, int j, int *k, int *l){
  int resk, lg, ld;
  int L = 0;

  while(L>=0){
    resk = i-L;
    lg = j;
    ld = j;

    while(resk<=i){
      if(resk>=0 && resk < G->m && lg>=0 && lg < G->n){
        if(G->T[resk][lg].piece != -1 && G->T[resk][lg].fond != G->T[resk][lg].piece){
          *k = resk;
          *l = lg;
          return;
        }
      }
      if(resk>=0 && resk < G->m && ld>=0 && ld < G->n){
        if(G->T[resk][ld].piece != -1 && G->T[resk][ld].fond != G->T[resk][ld].piece){
          *k = resk;
          *l = ld;
          return;
        }
      }
      resk = resk + 1;
      lg = lg - 1;
      ld = ld + 1;
    }

    resk = i+1;
    lg = j - L + 1;
    ld = j + L - 1;

    while(resk<=i+L){
      if(resk>=0 && resk < G->m && lg>=0 && lg < G->n){
        if(G->T[resk][lg].piece != -1 && G->T[resk][lg].fond != G->T[resk][lg].piece){
          *k = resk;
          *l = lg;
          return;
        }
      }
      if(resk>=0 && resk < G->m && ld>=0 && ld < G->n){
        if(G->T[resk][ld].piece != -1 && G->T[resk][ld].fond != G->T[resk][ld].piece){
          *k = resk;
          *l = ld;
          return;
        }
      }
      resk = resk + 1;
      lg = lg + 1;
      ld = ld - 1;
    }
    L++;
  }
}

void algorithme_circulaire(Grille * G, Solution * S){
  int k;
  int l;
  G->ir = 0;
  G->jr = 0;

  while(G->cptr_noire != G->n * G->m){
    if(G->T[G->ir][G->jr].robot == -1){
        RechercheCaseCirculaire_nn(G, G->ir, G->jr, &k, &l);
    }
    else{
        RechercheCaseCirculaire_c(G, G->T[G->ir][G->jr].robot, G->ir, G->jr, &k, &l);
    }
    PlusCourtChemin(S, G->ir, G->jr, k, l);
    changement_case(G, k, l);
    Ajout_action(S, 'S');
    swap_case(G);
  }
}



/*________Question 2.2________*/
/*
Fixons une valeur 50 pour la couleur et une graine de 5.

Pour la m??thode naive, le nombre de case maximal pour lequel cette m??thode s'execute en moin de 30 secondes
est 119 025 (soit un grille 345x345 avec 50 couleur et une graine ??gale ?? 5).

Pour la m??thode circulaire, le nombre de case maximal pour lequel cette m??thode s'??xecute en moin de 30 secondes
est 189 225 (soit une grille de taille 435x435 avec 50 couleur et une graine ??gale ?? 5).
*/


/*________Question 2.3________*/
/*
En se placant dans le cas d'une grille ?? m lignes et n colonnes avec m = n (donc
une grille de n^2 cases) on obtient les r??sultats suivants :

Voici la complexit?? des diff??rentes fonctions de la version na??ve :

- PlusCourtChemin : 0(n) car dans le pire cas on cherche le plus court chemin
entre la case (0, 0) et la case (n - 1, n - 1) qui est de distance 2n.

- TailleChemin : O(1) car peut importe la distance entre les deux cases le
nombre d'op??rations sera le m??me.

- RechercheCaseNaif_c et RechercheCaseNaif_nn : O(n^2) car dans chacune des
fonctions on parcourt chaque case de la grille quelle que soit la situation.

- algorithme_naif : Cette fonction fait appel a plusieurs autre fonction, voyons leur complexit??.
  - complexit?? de swap : O(1)
  - complexit?? de changement_case : O(1)
  - complexit?? de PlusCourtChemin : O(n)
  - complexit?? de Ajout_action : O(1)
  -complexit?? de RechercheCaseNaif_c / RechercheCaseNaif_nn : O(n^2)
La boucle while nous impose d'arreter lorsque toute les case sont noirs, donc on vas parcourir n*n case
ce qui donne une complexit?? de O(n??).
On fais aussi appel a RechercheCaseNaif_c ou RechercheCaseNaif_nn qui ne s'??xecute pas en m??me temps.
Donc on a O(n??) * O(n??) quo donne finalement O(n???)

Pour conclure, la complexit?? de la m??thode naive est O(n???)


Voici la complexit?? des diff??rentes fonctions de la version circulaire :

- PlusCourtChemin : 0(n) car dans le pire cas on cherche le plus court chemin
entre la case (0, 0) et la case (n - 1, n - 1) qui est de distance 2n.

- RechercheCaseCirculaire_c et RechercheCaseCirculaire_nn : On se place dans le pire des cas,
le robot est en case (0, 0) et la case qu'il recherche est en position (n-1, n-1).
Alors le robot vas recherche n*n case pour enfin trouver la case qu'il recherche,
ce qui donne une complexit?? de O(n??).
De plus on a une boucle While imbriqu??e dans une autre boucle While ce qui donne bien une
complexit?? de O(n??)

- algorithme_circulaire : Cette fonction fait appel a plusieurs autre fonction, voyons leur complexit??.
  - complexit?? de swap : O(1)
  - complexit?? de changement_case : O(1)
  - complexit?? de PlusCourtChemin : O(n)
  - complexit?? de Ajout_action : O(1)
  -complexit?? de RechercheCaseCirculaire_c / RechercheCaseCirculaire_nn : O(n??)
On fais appel a RechercheCaseCirculaire_c ou RechercheCaseCirculaire_nn (qui ne s'??xecute pas en m??me temps)
dans une boucle While.
Donc on a O(n??) * O(n??) qui donne finalement O(n???).

Pour conclure, la complexit?? de la m??thode circulaire est O(n??)
*/
