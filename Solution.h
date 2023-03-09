#ifndef __SOLUTION__
#  define __SOLUTION__

typedef struct cell_char
{
  char a;
  struct cell_char *suiv;
} Cell_char;


// Liste simplement chainee
// avec insertion en fin de liste en O(1)
typedef struct
{

  int cptr_pas;                 // Compteur des cases parcourues

  Cell_char *prem;              // Liste des actions
  Cell_char *dern;              // Pointeur sur dernier element

} Solution;

// Initialisation
void Solution_init (Solution * S);

// Ajout d'un char en fin de liste en O(1)
void Ajout_action (Solution * S, char a);

// Affichage de la liste
void Affiche (Solution * S);

// Ecriture de la solution dans un fichier
void Ecriture_Disque (int m, int n, int nbcoul, int graine, Solution * S);

// Lecture d'une solution a partir d'un fichier
// La solution doit avoir ete initialisee auparavant
void Lecture_Disque (char *filename, int *m, int *n, int *nbcoul, int *graine,
                     Solution * S);

#endif
