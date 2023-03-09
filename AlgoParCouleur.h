// Ayman JARI | Reda RAMZI | Abdou LAHAT SYLLA | Groupe TP5

#ifndef __PARCOULEUR__
#define __PARCOULEUR__

#include "LDC.h"
#include "AlgoNaif.h"
#include "Grille.h"
#include "Solution.h"

//Question 3.2

CelluleLDC * LDCrechercherPlusProcheCase(LDC * ldc, int i, int j);

//Question 3.3

void algorithme_parcouleur(Grille * G, Solution * S);

#endif
