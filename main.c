#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "moves.h"
#define INT_MAX 2147483647

int main() {
    t_map map = createMapFromFile("..\\maps\\example2.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);

    // Afficher les sols et les coûts (optionnel)
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }

    // Affichage des coûts
    for (int i = 0; i < map.y_max; i++) {
        for (int j = 0; j < map.x_max; j++) {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }

    displayMap(map);

    int initial_value = 9;  // La valeur initiale de la case de départ
    int moves[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};  // Les coûts des mouvements possibles
    int num_moves = sizeof(moves) / sizeof(moves[0]);  // Calcul du nombre de mouvements

    // Créez la racine de l'arbre avec la valeur de départ
    TreeNode *root = create_node(initial_value, 0, NULL);

    // Construit l'arbre de mouvements jusqu'à la profondeur maximale définie
    build_tree(root, 2, moves, num_moves);

    // Trouve la feuille avec le coût minimal dans l'arbre
    int min_cost = 24000;
    TreeNode *min_leaf = NULL;
    find_min_leaf(root, &min_cost, &min_leaf);

    // Affiche le coût minimal et le chemin optimal
    printf("Minimum cost: %d\n", min_cost);
    print_optimal_path(min_leaf);

    // Libère la mémoire de l'arbre
    //free_tree(root);

    return 0;
}