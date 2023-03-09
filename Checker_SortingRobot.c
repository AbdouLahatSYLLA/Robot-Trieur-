#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"


int
main (int argc, char **argv)
{

  char *filename;
  Grille G;
  AffGrille AG;
  Solution S;
  int graine;
  int aff;

  int i, j, t;


  if (argc != 4)
  {
    printf
      ("usage: %s <fichier_solution> <Affichage_0/1> <temporisation>\n",
       argv[0]);
    return 1;
  }

  filename = strdup (argv[1]);
  aff = atoi (argv[2]);
  t = atoi (argv[3]);

  Solution_init (&S);
  Lecture_Disque (filename, &G.m, &G.n, &G.nbcoul, &graine, &S);
  Grille_allocation (&G);
  Gene_Grille (&G, graine);


  if (aff == 1)
  {                             /* Affichage de la grille */

    AffGrille_init (&G, &AG);

    AffGrille_ouvre_fenetre (&AG);

    for (i = 0; i < G.m; i++)
      for (j = 0; j < G.n; j++)
      {
        AffGrille_redessine_case (&AG, &G, i, j);
      }

    AffGrille_reaffiche_Grille ();
    for (i = 0; i < t; i++)
      for (j = 0; j < 10000000; j++)
      {
      }
  }

  Cell_char *cour = S.prem;
  int ok = 1;
  while ((cour != NULL) && (ok))
  {

    switch (cour->a)
    {                           /* Test du type d'événement */

    case 'R':
      if (G.jr <= G.n - 2)
      {
        changement_case (&G, G.ir, G.jr + 1);
        if (aff == 1)
        {
          AffGrille_redessine_case (&AG, &G, G.ir, G.jr - 1);
          AffGrille_redessine_case (&AG, &G, G.ir, G.jr);
        }
      }
      else
        ok = 0;
      break;
    case 'L':
      if (G.jr >= 1)
      {
        changement_case (&G, G.ir, G.jr - 1);
        if (aff == 1)
        {
          AffGrille_redessine_case (&AG, &G, G.ir, G.jr + 1);
          AffGrille_redessine_case (&AG, &G, G.ir, G.jr);
        }
      }
      else
        ok = 0;
      break;
    case 'U':
      if (G.ir >= 1)
      {
        changement_case (&G, G.ir - 1, G.jr);
        if (aff == 1)
        {
          AffGrille_redessine_case (&AG, &G, G.ir + 1, G.jr);
          AffGrille_redessine_case (&AG, &G, G.ir, G.jr);
        }
      }
      else
        ok = 0;
      break;
    case 'D':
      if (G.ir <= G.m - 2)
      {
        changement_case (&G, G.ir + 1, G.jr);
        if (aff == 1)
        {
          AffGrille_redessine_case (&AG, &G, G.ir - 1, G.jr);
          AffGrille_redessine_case (&AG, &G, G.ir, G.jr);
        }
      }
      else
        ok = 0;
      break;
    case 'S':
      swap_case (&G);
      if (aff == 1)
        AffGrille_redessine_case (&AG, &G, G.ir, G.jr);
      break;
    }

    if (aff == 1)
    {
      AffGrille_reaffiche_Grille ();
      for (i = 0; i < t; i++)
        for (j = 0; j < 10000000; j++)
        {
        }
    }
    cour = cour->suiv;
  }

  if (ok == 0)
    printf ("\nSequence non valide.\n\n");
  else if (G.cptr_noire == G.n * G.m)
    printf ("\nSolution valide en %d pas.\n\n", S.cptr_pas);

  if (aff == 1)
  {
    AffGrille_ferme_fenetre ();
    AffGrille_free (&AG);
  }

  return 0;
}
