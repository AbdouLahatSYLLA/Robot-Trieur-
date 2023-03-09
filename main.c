// Ayman JARI | Reda RAMZI | Abdou LAHAT SYLLA | Groupe TP5

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Grille.h"
#include "Solution.h"
#include "AlgoNaif.h"
#include "AlgoCirculaire.h"
#include "AlgoParCouleur.h"
#include "AlgoAVL.h"

int main(int argc, char **argv){
  Grille G;
  Solution S;
  int graine;

  if (argc != 6)
  {
    printf ("usage: %s <nb_lignes nb_colonnes nb_couleur graine num_methode>\n", argv[0]);
    return 0;
  }
  G.m = atoi (argv[1]);
  G.n = atoi (argv[2]);

  if (G.m > G.n)
  {
    printf ("Il doit y avoir plus de colonnes que de lignes.\n");
    return 0;
  }
  G.nbcoul = atoi (argv[3]);
  if (G.nbcoul > G.m * G.n)
  {
    printf ("Il ne doit pas y avoir plus de couleurs que de cases.\n");
    return 0;
  }

  int i = atoi(argv[5]);
  if(i != 1 && i != 2 && i != 3 && i != 4){
    printf("Le numéro de la méthode doit être compris entre 1 et 4.\n");
    return 0;
  }

  graine = atoi (argv[4]);
  Grille_allocation (&G);
  Gene_Grille (&G, graine);
  Solution_init (&S);

  clock_t debut = clock();

  /*Exercice 1*/
  if(i == 1){
    algorithme_naif(&G, &S);
  }
  /*Exercice 2*/
  if(i == 2){
    algorithme_circulaire(&G, &S);
  }
  /*Exercice 3*/
  if(i == 3){
    algorithme_parcouleur(&G, &S);
  }
  /*Exercice 4*/
  if(i == 4){
    algorithme_avl(&G, &S);
  }

  clock_t fin = clock();

  printf ("La solution utilisant la méthode %d est :\n\n", i);
  Affiche(&S);
  printf ("\nEcriture de la solution sur disque\n\n");
  Ecriture_Disque (G.m, G.n, G.nbcoul, graine, &S);

  double temps = (double) (fin - debut) / CLOCKS_PER_SEC;
  printf("Le temps d'exécution de l'algorithme est de %f de secondes.\n", temps);

  return 1;
}
