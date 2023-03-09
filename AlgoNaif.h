// Ayman JARI | Reda RAMZI | Abdou LAHAT SYLLA | Groupe TP5


#ifndef __NAIF__
#  define __NAIF__

#include "Grille.h"
#include "Solution.h"

//Question 1.2

void PlusCourtChemin(Solution * S, int i, int j, int k, int l);

//Question 1.4

int TailleChemin(int i, int j, int k, int l);

void RechercheCaseNaif_c(Grille * G, int c, int i, int j, int * k, int * l);

void RechercheCaseNaif_nn(Grille * G, int i, int j, int * k, int * l);

//Question 1.5

void algorithme_naif(Grille *G, Solution *S);

#endif
