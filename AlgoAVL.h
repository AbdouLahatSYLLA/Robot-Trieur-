// Ayman JARI | Reda RAMZI | Abdou LAHAT SYLLA | Groupe TP5

#ifndef __ALGOAVL__
#define __ALGOAVL__

#include "AVL.h"
#include "AlgoNaif.h"
#include "Grille.h"
#include "Solution.h"

void initialiserM(M * m, Grille * G);

void remplirM(M * m, Grille * G);

void libererM(M * m, Grille * G);

void algorithme_avl(Grille * G, Solution * S);

#endif
