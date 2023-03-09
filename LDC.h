// Ayman JARI | Reda RAMZI | Abdou LAHAT SYLLA | Groupe TP5

#ifndef __LISTEDC_H__
#define __LISTEDC_H__

// Structure de liste doublement chainee
// contenant deux entiers i et j

typedef struct celluleLDC{
  int i,j; // Elements stockes dans la liste
  struct celluleLDC * prec; /* pointeur sur l'element precedent de la liste */
  struct celluleLDC * suiv; /* pointeur sur l'element suivant de la liste */
} CelluleLDC;

typedef struct {
  CelluleLDC * premier;  /* Pointeur sur element en tete */
  CelluleLDC * dernier;  /* Pointeur sur element en fin */
} LDC;



/* Alloue et retourne une cellule */
CelluleLDC * creerCellule(int i, int j);

void LDCInitialise(LDC * ldc);

/* Test si liste vide */
int LDCVide(LDC * ldc);

void LDCInsererEnFin(LDC * ldc, int i,int j);

void LDCenleverCellule(LDC * ldc, CelluleLDC * cel);

void LDCafficher(LDC * ldc);

void LDCdesalloue(LDC * ldc);

#endif
