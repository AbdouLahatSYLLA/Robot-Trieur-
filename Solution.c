#include "Solution.h"
#include<stdlib.h>
#include<stdio.h>
#include"entree_sortie.h"
#include<string.h>

void
Solution_init (Solution * S)
{

  S->prem = NULL;
  S->dern = NULL;
  S->cptr_pas = 0;
}

void
Ajout_action (Solution * S, char a)
{
  Cell_char *nouv = (Cell_char *) malloc (sizeof (Cell_char));
  nouv->a = a;
  nouv->suiv = NULL;
  if (S->prem == NULL)
  {                             // Si Liste vide
    S->prem = nouv;
    S->dern = nouv;
  }
  else
  {
    S->dern->suiv = nouv;
    S->dern = nouv;
  }
  if (a != 'S')
    S->cptr_pas++;
}


void
Affiche (Solution * S)
{
  Cell_char *cour = S->prem;
  printf ("Nombre de pas: %d\n", S->cptr_pas);
  printf ("Section jouee: ");
  while (cour != NULL)
  {
    printf ("%c ", cour->a);
    cour = cour->suiv;
  }
  printf ("\n");
}

void
Ecriture_Disque (int m, int n, int nbcoul, int graine, Solution * S)
{
  char filename[104];
  char inttochar[6];

  strcpy (filename, "Robot_");
  sprintf (inttochar, "%d", m);
  strcat (filename, inttochar);
  strcat (filename, "_");
  sprintf (inttochar, "%d", n);
  strcat (filename, inttochar);
  strcat (filename, "_");
  sprintf (inttochar, "%d", nbcoul);
  strcat (filename, inttochar);
  strcat (filename, "_");
  sprintf (inttochar, "%d", graine);
  strcat (filename, inttochar);
  strcat (filename, ".sol");

  FILE *f = fopen (filename, "w");
  fprintf (f, "%d %d %d %d\n", m, n, nbcoul, graine);

  Cell_char *cour = S->prem;
  while (cour != NULL)
  {
    fprintf (f, "%c ", cour->a);
    cour = cour->suiv;
  }
  fprintf (f, "0\n");

  fclose (f);
}

void
Lecture_Disque (char *filename, int *m, int *n, int *nbcoul, int *graine,
                Solution * S)
{
  char c;
  FILE *f = fopen (filename, "r");
  *m = GetEntier (f);
  *n = GetEntier (f);
  *nbcoul = GetEntier (f);
  *graine = GetEntier (f);

  c = ReadChar (f);
  while (c != '0')
  {
    Ajout_action (S, c);
    c = ReadChar (f);
  }

  fclose (f);
}
