//
// Created by flasque on 19/10/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "moves.h"

#define MAX_DEPTH 5
/* prototypes of local functions */
/* local functions are used only in this file, as helper functions */

/**
 * @brief Function to rotate the robot according to a move and its actual orientation
 * @param ori : the actual orientation of the robot
 * @param move : the move to do
 * @return the new orientation of the robot
 */
t_orientation rotate(t_orientation, t_move );

/**
 * @brief function to translate the robot according to a move and its actual position
 * @param loc : the actual localisation of the robot
 * @param move : the move to do
 * @return the new localisation of the robot
 */
t_localisation translate(t_localisation , t_move);

/* definition of local functions */

t_orientation rotate(t_orientation ori, t_move move)
{
    int rst;
    switch (move)
    {
        case T_LEFT:
            rst=3;
            break;
        case T_RIGHT:
            rst=1;
            break;
        case U_TURN:
            rst=2;
            break;
        default:
            break;
    }
    return (ori+rst)%4;
}

t_localisation translate(t_localisation loc, t_move move)
{
    /** rules for coordinates:
     *  - x grows to the right with step of +1
     *  - y grows to the bottom with step of +1
     *  - the origin (x=0, y=0) is at the top left corner
     */
    t_position res;
    switch (move) {
        case F_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 1;
                    break;
                case EAST:
                    res.x = loc.pos.x + 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 1;
                    break;
                case WEST:
                    res.x = loc.pos.x - 1;
                    break;
                default:
                    break;
            }
            break;
        case F_20:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 2;
                    break;
                case EAST:
                    res.x = loc.pos.x + 2;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 2;
                    break;
                case WEST:
                    res.x = loc.pos.x - 2;
                    break;
                default:
                    break;
            }
            break;
        case F_30:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 3;
                    break;
                case EAST:
                    res.x = loc.pos.x + 3;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 3;
                    break;
                case WEST:
                    res.x = loc.pos.x - 3;
                    break;
                default:
                    break;
            }
            break;
        case B_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y + 1;
                    break;
                case EAST:
                    res.x = loc.pos.x - 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y - 1;
                    break;
                case WEST:
                    res.x = loc.pos.x + 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
        return loc_init(res.x, res.y, loc.ori);

}

/* definitions of exported functions */

char *getMoveAsString(t_move move)
{
    return _moves[move];
}

t_localisation move(t_localisation loc, t_move move)
{
    t_localisation new_loc;
    new_loc.ori = rotate(loc.ori, move);
    new_loc = translate(loc, move);
    return new_loc;
}

void updateLocalisation(t_localisation *p_loc, t_move m)
{
    *p_loc = move(*p_loc, m);
    return;
}

TreeNode* create_node(int value, int move, TreeNode* parent) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->value = value;
    node->move = move;
    node->parent = parent;
    node->num_children = 0;
    node->children = NULL;
    return node;
}

// Fonction récursive pour construire l'arbre
void build_tree(TreeNode *node, int level, int moves[], int num_moves) {
    if (level >= MAX_DEPTH || node->value >= 9999) {
        return;
    }

    // Allocation des enfants pour ce nœud
    node->children = (TreeNode**)malloc(num_moves * sizeof(TreeNode*));
    node->num_children = num_moves;

    // Pour chaque mouvement possible
    for (int i = 0; i < num_moves; i++) {
        int new_value = node->value + moves[i];
        node->children[i] = create_node(new_value, moves[i], node);

        // Construire l'arbre pour le nœud enfant en excluant le mouvement actuel
        int next_moves[num_moves - 1];
        int index = 0;
        for (int j = 0; j < num_moves; j++) {
            if (j != i) {
                next_moves[index++] = moves[j];
            }
        }
        build_tree(node->children[i], level + 1, next_moves, num_moves - 1);
    }
}

// Fonction pour trouver la feuille avec le coût minimal et son chemin
void find_min_leaf(TreeNode* node, int *min_cost, TreeNode **min_leaf) {
    if (node->num_children == 0) { // Si c'est une feuille
        if (node->value < *min_cost) {
            *min_cost = node->value;
            *min_leaf = node;
        }
        return;
    }

    // Parcourir les enfants récursivement
    for (int i = 0; i < node->num_children; i++) {
        find_min_leaf(node->children[i], min_cost, min_leaf);
    }
}

// Fonction pour afficher le chemin optimal
void print_optimal_path(TreeNode *leaf) {
    if (leaf == NULL) return;

    int path[MAX_DEPTH];
    int depth = 0;
    TreeNode *current = leaf;

    // Remonter jusqu'à la racine pour construire le chemin
    while (current->parent != NULL) {
        path[depth++] = current->move;
        current = current->parent;
    }

    // Afficher le chemin en ordre inverse
    printf("Optimal path: ");
    for (int i = depth - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");
}
