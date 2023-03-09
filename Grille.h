#ifndef __GRILLE__
#  define __GRILLE__
#  include "Solution.h"


// Type struct d une case d une grille
typedef struct
{

  int fond;                     // Entier couleur de 0 a nbcoul-1

  int piece;                    // Entier couleur de 0 a nbcoul-1 si piece presente
  // -1 si pas de piece

  int robot;                    // -2 si pas de robot sur cette case
  // -1 si robot present mais sans piece
  // Entier couleur de 0 a nbcoul-1 si robot present avec piece
} CCase;


// Type struct d une grille de jeu
typedef struct
{
  // Un couple (i,j) donne des coordonnees ieme ligne, jeme colonne

  int m;                        // Nb de lignes

  int n;                        // Nb de colonnes

  int nbcoul;                   // Nb de couleurs

  CCase **T;                    // Tableau a deux dimensions de la grille

  int ir, jr;                   // Coordonnee du robot sur une case (dite case courante)

  int cptr_noire;               // Compteur de cases noires

} Grille;


// Fonction realisant l'allocation d'une grille
// Les champs m,n  doivent deja etre remplis auparavant
void Grille_allocation (Grille * G);

// Fonction de generation d'une instance en fonction d une graine
// de generation aleatoire
void Gene_Grille (Grille * G, int graine);

// Fonction de changement de robot de la case courante
// a une case i,j
void changement_case (Grille * G, int i, int j);

// Fonction de prise, depot ou echange d une piece par le robot
// sur la case courante
void swap_case (Grille * G);

#endif
