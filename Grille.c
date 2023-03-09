#include "Grille.h"
#include <stdlib.h>
#include <stdio.h>


void
Grille_allocation (Grille * G)
{
  int i;

  G->T = (CCase **) malloc (sizeof (CCase *) * G->m);
  for (i = 0; i < G->m; i++)
  {
    G->T[i] = (CCase *) malloc (sizeof (CCase) * G->n);
  }
}



void
Gene_Grille (Grille * G, int graine)
{
  int i, j, k, ip, jp, tmp, l, r, rr, alpha;

  srand (graine);

  // Affecte au moins 1 case par couleur
  k = 0;
  i = 0;
  j = 0;
  while (k < G->nbcoul)
  {
    G->T[i][j].fond = k;        // remplit le fond et la piece de meme couleur
    G->T[i][j].piece = k;
    j++;
    if (j == G->n)
    {
      i++;
      j = 0;
    }
    k++;
  }

  // Complete le reste de la grille avec des couleurs en quantite
  // aleatoire (mais selon un principe algorithmique)
  alpha = (G->m * G->n) / (G->nbcoul * 1.0);
  l = 0;
  while (k < G->m * G->n)
  {

    r = 1 + rand () % (2 * alpha);
    rr = 0;
    while ((k < G->m * G->n) && (rr < r))
    {
      G->T[i][j].fond = l;
      G->T[i][j].piece = l;
      j++;
      if (j == G->n)
      {
        i++;
        j = 0;
      }
      k++;
      rr++;
    }

    l++;
    if (l == G->nbcoul)
      l = 0;
  }


  // Permute aleatoirement les pieces sur la grille
  for (i = 0; i < G->m; i++)
    for (j = 0; j < G->n; j++)
    {
      ip = rand () % G->m;
      jp = rand () % G->n;
      tmp = G->T[i][j].piece;
      G->T[i][j].piece = G->T[ip][jp].piece;
      G->T[ip][jp].piece = tmp;
    }


  // Comptabilise combien de piece sont sur une case de meme couleur
  // au depart
  G->cptr_noire = 0;
  for (i = 0; i < G->m; i++)
    for (j = 0; j < G->n; j++)
      if (G->T[i][j].piece == G->T[i][j].fond)
        G->cptr_noire++;

  // Place le robot en case 0,0
  for (i = 0; i < G->m; i++)
    for (j = 0; j < G->n; j++)
      G->T[i][j].robot = -2;
  G->T[0][0].robot = -1;

  G->ir = 0;
  G->jr = 0;


}



void
changement_case (Grille * G, int i, int j)
{
  int tmp = G->T[G->ir][G->jr].robot;
  G->T[G->ir][G->jr].robot = -2;
  G->ir = i;
  G->jr = j;
  G->T[G->ir][G->jr].robot = tmp;
}


void
swap_case (Grille * G)
{

  if (G->T[G->ir][G->jr].fond != G->T[G->ir][G->jr].piece)
  {
    int tmp = G->T[G->ir][G->jr].robot;
    G->T[G->ir][G->jr].robot = G->T[G->ir][G->jr].piece;
    G->T[G->ir][G->jr].piece = tmp;
    if (G->T[G->ir][G->jr].fond == G->T[G->ir][G->jr].piece)
      G->cptr_noire++;
  }

}
