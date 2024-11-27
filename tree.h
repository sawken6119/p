//
// Created by arman on 20/11/2024.
//


#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H
#include "phase.h"
#include "map.h"

typedef struct s_node{
    int value;
    int NbSons;
    int prof;
    struct s_node **fils;
    t_move *reste;
    int *position;
    t_move *mouvement;
}t_node;

t_node* create_node(int value, int NbSons, int prof, t_move fils[]);
t_move* supprime_e_Tab(t_move Tab[], int indice, int longueur);
t_move supprimer_element(t_move* tableau, int taille, int indice);
void creer_fils(t_node *Node, t_localisation loc, t_map map);
t_node* cout_mini(t_node* node);
t_move* chemin(t_node *node, t_move* tirage);
void creerArbre(t_node* node, t_localisation loc, t_map map);
void printTree(t_node *node, int level);
void phase();

#endif //UNTITLED1_TREE_H
