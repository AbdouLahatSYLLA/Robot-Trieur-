#ifndef __API_AFFGRILLE__
#  define __API_AFFGRILLE__

#  include <SDL/SDL.h>
#  include <stdlib.h>
#  include "Grille.h"

/* Structure necessaire aux fonctions d affichage*/
typedef struct
{

  Grille *G;

  int taille_pixel;             /* Taille de la grille a l ecran */

  int cas_aff;                  /* 1 s il y a trop de cases a afficher / 0 sinon */

  int taille_case;              /* Taille d une case a l ecran */

  int modulo;                   /* Saut d affichache en cas de nombre de cases important */

  Uint32 *T_coul;               /* Tableau de codage des couleurs */

} AffGrille;

/* Fonction d initialisation de AffGrille */
/* 
Entree:
   G: pointeur sur une grille allouee precedemment
   AG : adresse d'un pointeur sur affGrille
Sortie:
   AG: allocation et affectation des elements necessaires
       a l affichage d une grille de jeu */
void AffGrille_init (Grille * G, AffGrille * AG);

/* Fonction permettant l'ouverture de la fenetre graphique
   contenant une grille ainsi que l'affichage total de la grille*/
void AffGrille_ouvre_fenetre (AffGrille * AG);

/* Fonction permettant la fermeture de la fenetre graphique
   contenant une grille */
void AffGrille_ferme_fenetre ();

/* Fonction permettant le redessin d une case SANS l'afficher*/
void AffGrille_redessine_case (AffGrille * AG, Grille * G, int i, int j);

/* Fonction permettant d'afficher/reafficher la grille */
void AffGrille_reaffiche_Grille ();

/* Liberation memoire d une grille */
void AffGrille_free (AffGrille * AG);


#endif
