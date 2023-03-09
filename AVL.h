// Ayman JARI | Reda RAMZI | Abdou LAHAT SYLLA | Groupe TP5

#ifndef __AVL_H__
#define __AVL_H__

#include <math.h>
struct _node {
    int key;                /* valeur du noeud */
    struct _node * left;    /* fils gauche du noeud */
    struct _node * right;   /* fils droit noeud */
    int h;                  /* hauteur du noeud */
    int eq;                 /* equilibrage = hauteur(fils gauche) - hauteur(fils droit) */
};



/*  AVL.h */
typedef struct _node * AVL;

/* structure de tableau M a double indice telle que M[c][i] correspond a un AVL*/

typedef struct {
  AVL ** tab;  /* tableau a 2D  M[c][i] correspond a un AVL contenant les key j  */
}M;

/* Afficher les élments dans l'ordre infixe */
void print_inorder_AVL (AVL A);

/* Recherche de v dans l'arbre binaire de recherche A */
int search_AVL (AVL A, int v);

/* Recherche du minimum dans un arbre binaire de recherche */
int minimum_AVL (AVL A);

/* Recherche du maximum */
int maximum_AVL (AVL A);

/* Mesure de la hauteur de l'arbre A */
int height_AVL (AVL A);

/* Effectue une rotation gauche de l'arbre A sur sa racine, attention au passage de A par reference */
void rot_G (AVL * A);

/* Effectue une rotation droite de l'arbre A sur sa racine, attention au passage de A par reference */
void rot_D (AVL * A);

/***************** fonction rotation (AVL *) qui contient les rotations faites lors de l'insertion et suppression ******/
void rotation (AVL * A);


/* Insertion de v dans l'arbre A */
void insert_AVL (AVL* A, int v);

/* Suppression de v dans l'arbre A */
void delete_AVL (AVL* A, int v);

/* Liberation complete de la memoire occupee par un arbre */
void free_tree_AVL (AVL A);

int Chemin(int i, int j, int k, int l);

int AVLPlusProcheCase(AVL A,int k, int l);

#endif
