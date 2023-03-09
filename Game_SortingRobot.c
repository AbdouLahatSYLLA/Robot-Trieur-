#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Solution.h"
#include "API_AffGrille.h"


int
main (int argc, char **argv)
{

  Grille G;
  AffGrille AG;
  Solution S;
  int graine;
  int i, j;

  if (argc != 5)
  {
    printf ("usage: %s <nb_lignes nb_colonnes nb_couleur graine>\n", argv[0]);
    return 1;
  }

  G.m = atoi (argv[1]);
  G.n = atoi (argv[2]);

  if (G.m > G.n)
  {
    printf ("Il doit y avoir plus de colonnes que de lignes.\n");
    exit (1);
  }
  G.nbcoul = atoi (argv[3]);
  if (G.nbcoul > G.m * G.n)
  {
    printf ("Il ne doit pas y avoir plus de couleurs que de cases.\n");
    exit (1);
  }

  graine = atoi (argv[4]);

  /* Generation de l'instance */

  Grille_allocation (&G);

  Gene_Grille (&G, graine);

  Solution_init (&S);

  /* Affichage de la grille */

  AffGrille_init (&G, &AG);

  AffGrille_ouvre_fenetre (&AG);

  for (i = 0; i < G.m; i++)
    for (j = 0; j < G.n; j++)
    {
      AffGrille_redessine_case (&AG, &G, i, j);
    }

  AffGrille_reaffiche_Grille ();

  /* Boucle generale de gestion des evements clavier */

  SDL_EnableKeyRepeat (1000, 1000);
  SDL_Event event;
  int continuer = 1;

  while ((continuer) && (G.cptr_noire != G.n * G.m))
  {

    //   printf("(%d,%d)",G.ir,G.jr); //affiche position robot

    SDL_WaitEvent (&event);     /* Récupération de l'événement dans event */

    switch (event.type)
    {                           /* Test du type d'événement */

    case SDL_QUIT:             /* Si c'est un événement de type "Quitter" */
      continuer = 0;
      break;

    case SDL_KEYDOWN:          /* Si appui sur une touche */

      switch (event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        continuer = 0;
        break;
      case SDLK_RIGHT:
        if (G.jr <= G.n - 2)
        {
          Ajout_action (&S, 'R');
          changement_case (&G, G.ir, G.jr + 1);
          AffGrille_redessine_case (&AG, &G, G.ir, G.jr - 1);
          AffGrille_redessine_case (&AG, &G, G.ir, G.jr);
        }
        break;
      case SDLK_LEFT:
        if (G.jr >= 1)
        {
          Ajout_action (&S, 'L');
          changement_case (&G, G.ir, G.jr - 1);
          AffGrille_redessine_case (&AG, &G, G.ir, G.jr + 1);
          AffGrille_redessine_case (&AG, &G, G.ir, G.jr);
        }
        break;
      case SDLK_UP:
        if (G.ir >= 1)
        {
          Ajout_action (&S, 'U');
          changement_case (&G, G.ir - 1, G.jr);
          AffGrille_redessine_case (&AG, &G, G.ir + 1, G.jr);
          AffGrille_redessine_case (&AG, &G, G.ir, G.jr);
        }
        break;
      case SDLK_DOWN:
        if (G.ir <= G.m - 2)
        {
          Ajout_action (&S, 'D');
          changement_case (&G, G.ir + 1, G.jr);
          AffGrille_redessine_case (&AG, &G, G.ir - 1, G.jr);
          AffGrille_redessine_case (&AG, &G, G.ir, G.jr);

        }
        break;
      case SDLK_SPACE:
        Ajout_action (&S, 'S');
        swap_case (&G);
        AffGrille_redessine_case (&AG, &G, G.ir, G.jr);
        break;
      default:
        break;
      }
      break;


    }
    system ("clear\n");
    Affiche (&S);
    AffGrille_reaffiche_Grille ();
  }

  if (G.cptr_noire == G.n * G.m)
  {
    printf ("\nVous avez gagne en %d pas\n", S.cptr_pas);
    printf ("\nEcriture de la solution sur disque\n\n");
    Ecriture_Disque (G.m, G.n, G.nbcoul, graine, &S);
  }

  AffGrille_ferme_fenetre ();

  AffGrille_free (&AG);

  return 0;
}
