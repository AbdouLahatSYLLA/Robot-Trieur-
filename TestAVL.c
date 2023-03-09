// Ayman JARI | Reda RAMZI | Abdou LAHAT SYLLA | Groupe TP5

#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>

int main ()
{
  AVL B = NULL;
  insert_AVL(&B, 1);
  insert_AVL(&B, 0);



  printf("\nLe j le plus proche est %d.\n",AVLPlusProcheCase(B, 2, 3) );

  return 1;
}
