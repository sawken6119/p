#include "tree.h"
#include <time.h>

t_node* create_node(int value, int NbSons, int prof, t_move fils[]){
    t_node *Node = (t_node*)malloc(sizeof(t_node));
    Node->value = value;
    Node->NbSons = NbSons;
    Node->prof = prof;
    // On initialise les fils à NULL
    Node->fils = malloc(Node->NbSons*sizeof(t_node*));
    for (int i = 0; i<NbSons;i++){
        Node->fils[i] = NULL;
    }
    // On initialise la position (qui correspond aux indices dans la liste tirage des mouvements appliqués)
    Node->position = malloc(Node->prof*sizeof(int));

    Node->mouvement = malloc(Node->prof*sizeof(t_move*));

    // On met dans reste tout les mouvements tirés (car aucun n'ont été utilisés pour l'instant)
    Node->reste = malloc(Node->NbSons*sizeof(t_move));
    for (int j = 0; j<NbSons;j++){
        Node->reste[j] = fils[j];
    }
    return Node;
}

t_move* supprime_e_Tab(t_move Tab[], int indice, int longueur){
    t_move* New_Tab = malloc(longueur * sizeof(t_move));
    int j=0;
    for (int i=0;i<longueur;i++){
        if (i!=indice) {
            New_Tab[j] = Tab[i];
            j++;
        }
    }
    return New_Tab;
}

void creer_fils(t_node *Node, t_localisation loc, t_map map) {
    // Si la valeur du node est trop élevé
    // Cela signifie qu'il est mort ou sortie de la carte
    // Donc on ne fait pas de fils
    if(Node->value > 9999){
        Node->NbSons = 0;
        Node->fils = NULL;
        Node->reste = NULL;
    }
    else{
        // Pour tous les fils du node, on calcul sa position en fonction de son mouvement
        for (int i = 0; i < Node->NbSons; i++) {
            t_localisation nv_loc = move(loc, Node->reste[i]);

            // Et on supprime ce mouvement du tableau des mouvements restants
            // Si la nouvelle loc est dans la map, on créer un node dans la position
            if (isValidLocalisation(nv_loc.pos, 6, 7)){
                t_move* nv_reste = supprime_e_Tab(Node->reste, i, Node->NbSons);
                Node->fils[i] = create_node(map.costs[nv_loc.pos.y][nv_loc.pos.x], Node->NbSons - 1, Node->prof + 1, nv_reste);
                // Enfin, on ajoute les indices des déplacement
                // de tous les noeuds parents
                for (int j=0; j<Node->prof; j++){
                    Node->fils[i]->position[j]=Node->position[j];
                }
                // Avec a la fin le nouvel indice du déplacement
                Node->fils[i]->position[Node->fils[i]->prof-1]=i;

                for (int j=0; j<Node->prof; j++){
                    Node->fils[i]->mouvement[j]= Node->mouvement[j];
                }
                Node->fils[i]->mouvement[Node->prof]= Node->reste[i];

            }
            else{
                t_move* nv_reste = supprime_e_Tab(Node->reste, i, Node->NbSons);
                Node->fils[i] = create_node(9999999, Node->NbSons - 1, Node->prof + 1, nv_reste);
            }
        }
    }
}

void creerArbre(t_node* node, t_localisation loc, t_map map){
    // Si le nombre d'enfant est inférieur à 5, on arrête l'arbre
    if (node->NbSons < 😎
        return ;
    else{
        // On créer les fils du Node
        // Puis on créer un arbre récursivement à partir de chacun des fils
        creer_fils(node, loc, map);
        for (int i=0; i< node->NbSons;i++){
            t_localisation nv_loc = move(loc, node->reste[i]);
            creerArbre(node->fils[i], nv_loc, map);
        }
    }
}

