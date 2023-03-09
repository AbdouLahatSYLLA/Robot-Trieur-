// Ayman JARI | Reda RAMZI | Abdou LAHAT SYLLA | Groupe TP5

#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>



/*commande pour créer AVL.o :
gcc -c -Wall -pedantic AVL.c
*/

/* Afficher les élments dans l'ordre infixe */
void print_inorder_AVL (AVL A) {
    if (A != NULL) {
        print_inorder_AVL(A->left);
        printf("[ %d , h(%d), e(%d) ] ",A->key,A->h,A->eq);
        print_inorder_AVL(A->right);
    }
}

/* Recherche de v dans l'arbre binaire de recherche A */
int search_AVL (AVL A, int v) {
   if (A == NULL) return 0;
   if (A->key == v) return 1;
   if (v < A->key) return search_AVL (A->left,v);
   else return search_AVL (A->right,v);
}

/* Recherche du minimum dans un arbre binaire de recherche */
int minimum_AVL (AVL A) {
  if (A == NULL) return -1;
  if (A->left == NULL) return A->key;
  return minimum_AVL(A->left);
}

/* Recherche du maximum */
int maximum_AVL (AVL A) {
  if (A == NULL) return -1;
  if (A->right == NULL) return A->key;
  return maximum_AVL(A->right);
}

/* Mesure de la hauteur de l'arbre A */
int height_AVL (AVL A)
{
  if (A == NULL) return -1;
  return A->h;
}

/* Effectue une rotation gauche de l'arbre A sur sa racine, attention au passage de A par reference */
void rot_G (AVL* A)
{
	AVL tmp;
	if (((*A) != NULL) && ((*A)->right != NULL)) {

		/* on modifie les pointeurs pour effectuer la rotation */
        tmp = (*A)->right;
        (*A)->right = tmp->left;
        tmp->left = (*A);
        (*A) = tmp;


        /* on recalcule l'equilibrage de (*A)->left, l'ancienne racine */
        if (height_AVL((*A)->left->left) > height_AVL((*A)->left->right)) {
           (*A)->left->h = 1 + height_AVL((*A)->left->left);
        }
        else {
           (*A)->left->h = 1 + height_AVL((*A)->left->right);
        }
        (*A)->left->eq = height_AVL((*A)->left->left) - height_AVL((*A)->left->right);

        /* on recalcule l'equilibrage de (*A), l'ancien fils droit */
        if (height_AVL((*A)->left) > height_AVL((*A)->right)) {
           (*A)->h = 1 + height_AVL((*A)->left);
        }
        else {
           (*A)->h = 1 + height_AVL((*A)->right);
        }
        (*A)->eq = height_AVL((*A)->left) - height_AVL((*A)->right);
    }
}

/* Effectue une rotation droite de l'arbre A sur sa racine, attention au passage de A par reference */
void rot_D (AVL* A)
{
	AVL tmp;
	if (((*A) != NULL) && ((*A)->left != NULL)) {

		/* on modifie
    les pointeurs pour effectuer la rotation */
        tmp = (*A)->left;
        (*A)->left = tmp->right;
        tmp->right = (*A);
        (*A) = tmp;

        /* on recalcule l'equilibrage de (*A)->right, l'ancienne racine */
        if (height_AVL((*A)->right->left) > height_AVL((*A)->right->right)) {
           (*A)->right->h = 1 + height_AVL((*A)->right->left);
        }
        else {
           (*A)->right->h = 1 + height_AVL((*A)->right->right);
        }
        (*A)->right->eq = height_AVL((*A)->right->left) - height_AVL((*A)->right->right);

        /* on recalcule l'equilibrage de (*A), l'ancien fils gauche */
        if (height_AVL((*A)->left) > height_AVL((*A)->right)) {
           (*A)->h = 1 + height_AVL((*A)->left);
        }
        else {
           (*A)->h = 1 + height_AVL((*A)->right);
        }
        (*A)->eq = height_AVL((*A)->left) - height_AVL((*A)->right);
    }
}



/***************** fonction rotation (AVL *) qui contient les rotations faites lors de l'insertion et suppression ******/
void rotation (AVL * A)
{
	if ((*A) != NULL)
     {
       if (height_AVL((*A)->left) > height_AVL((*A)->right)) {
         (*A)->h = 1 + height_AVL((*A)->left);
       }
       else {
        (*A)->h = 1 + height_AVL((*A)->right);
       }
       (*A)->eq = height_AVL((*A)->left) - height_AVL((*A)->right);

       if ((*A)->eq == 2) /* l'arbre est trop haut a gauche */
       {
         if (height_AVL((*A)->left->right) > height_AVL((*A)->left->left)) /* l'arbre "du milieu" est le plus gros -> double rotation */
         {
            rot_G(&((*A)->left));
         }
         /* dans tous les cas on finit par une rotation a droite */
         rot_D(A);
       }
       else
       {
         if ((*A)->eq == -2) /* l'arbre est trop haut a droite */
         {
           if (height_AVL((*A)->right->left) > height_AVL((*A)->right->right))
           {
               rot_D(&((*A)->right));
           }
           rot_G(A);
         }
       }
     }
}



/************************************************************************************/

/* Insertion de v dans l'arbre A  */
void insert_AVL (AVL* A, int v) {
  if ((*A) == NULL)
  {
	(*A) = malloc(sizeof(struct _node));
	(*A)->key = v;
	(*A)->left = NULL;
	(*A)->right = NULL;
	(*A)->h = 0;
	(*A)->eq = 0;
  }
  else
  {
	 /* On insÃ¨re Ã  la position definie par la propriÃ©tÃ© d'ABR */
     if (v < (*A)->key) insert_AVL(&((*A)->left),v);
     else insert_AVL(&((*A)->right),v);

     /* on met Ã  jour l'hauteur et l'Ã©qulibrage */

     rotation(A);
   }
}


/* Suppression de v dans l'arbre A */
void delete_AVL (AVL* A, int v)
{
   if ((*A) != NULL)
   {
	 AVL T;
	 /* on supprime l'Ã©lÃ©ment v comme dans les arbres ABR */
     if ((*A)->key == v)
     {
	    if ((*A)->left == NULL)
	    {
		   T = (*A);
		   (*A) = (*A)->right;
		   free(T);
	    }
	    else if ((*A)->right == NULL)
	         {
		       T = (*A);
		       (*A) = (*A)->left;
		       free(T);
	         }
	         else
	         {
	           int maxgauche = maximum_AVL((*A)->left);
	           (*A)->key = maxgauche;
	           delete_AVL(&((*A)->left),maxgauche);
             }
     }
     else
     {
      if (v < (*A)->key) delete_AVL(&((*A)->left),v);
      else delete_AVL(&((*A)->right),v);
     }

     /* on met Ã  jour l'hauteur et l'Ã©qulibrage */

      rotation(A);

   }
}


/* Liberation complete de la memoire occupee par un arbre */
void free_tree_AVL (AVL A) {
    if (A != NULL) {
        free_tree_AVL(A->left);
        free_tree_AVL(A->right);
        free(A);
    }
}

int Chemin(int i, int j, int k, int l){
  int ligne = k - i;
  int colonne = l - j;
  if(ligne < 0){
      ligne = - ligne;
  }
  if(colonne < 0){
      colonne = - colonne;
  }
  return ligne + colonne;
}

/*question 4:4*/
int AVLPlusProcheCase(AVL A,int k, int l){
  if(A != NULL){
    if(A->left == NULL && A->right == NULL){
      return A->key;
    }
    if(A->left!=NULL) {
      if(fabs(l-A->left->key) <= fabs(l-A->key)){
        return AVLPlusProcheCase(A->left,k,l);
      }
    }else{
      if(A->right == NULL){
        return A->key;
      }
      if(fabs(l-A->right->key) < fabs(l-A->key)){
        return AVLPlusProcheCase(A->right,k,l);
      }
    }
    return A->key;
  }
}
