//
// Created by arman on 20/11/2024.
//
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

t_node* cout_mini(t_node* node){
    // Si le node n'existe pas ou possède une valeur trop élevé, on ne fait rien
    if (node == NULL || node->value >= 9999) {
        return NULL;
    }
    t_node* mini = node;
    // On attribue récursivement new_mini à chaque fils de node
    // S'il est plus petit que mini, alors mini = new_mini
    for (int i = 0; i < node->NbSons; i++) {
        t_node* new_mini = cout_mini(node->fils[i]);
        if (new_mini && new_mini->value < mini->value) {
            mini = new_mini;
        }
    }
    return mini;
}

t_move* chemin(t_node* node, t_move* tirage){

    t_move* chemin = malloc(node->prof*sizeof(t_move));
    // Pour chaque indice de position, on récupère le mouvement associé dans tirage,
    // puis on le retire
    for (int i=0; i<node->prof; i++){
        chemin[i]= tirage[node->position[i]];
        tirage = supprime_e_Tab(tirage, node->position[i], 9-i);
    }
    return chemin;
}


void printTree(t_node *node, int profondeur) {
    if (node == NULL) return;
    // On fait un décalage à chaque profondeur pour une meilleur visibilité
    for (int i = 0; i < profondeur; i++) {
        printf("   ");
    }
    // On affiche la valeur, son nombre de fils, et sa profondeur
    printf("Node Value: %d, NbSons: %d, Profondeur: %d\n", node->value, node->NbSons, node->prof);
    // On recommence récursivement pout tous les fils
    for (int i = 0; i < node->NbSons; i++) {
        printTree(node->fils[i], profondeur + 1);
    }

    
void creerArbre(t_node* node, t_localisation loc, t_map map){
    // Si le nombre d'enfant est inférieur à 5, on arrête l'arbre
    if (node->NbSons < 8)
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

    void phase(){
    srand(time(NULL));
    t_map map = createMapFromFile("..\\maps\\example1.map");
    t_node* node;
    t_localisation loca = loc_init(4,5,NORTH);
    int nb_phase = 1;

    while (map.costs[loca.pos.y][loca.pos.x] !=0 ){

        t_move *tirage = getRandomMoves(9);
        printf("Voici le tirage de la phase %d\n", nb_phase);
        for (int i=0; i<9; i++){
            afficher_move(tirage[i]);
        }
        printf("\n");

        node = create_node(map.costs[loca.pos.y-1][loca.pos.x-1], 9, 0, tirage);
        creerArbre(node, loca, map);
        t_node *mini = cout_mini(node);
        t_move *trajet = chemin(mini, tirage);
        for (int i=0; i<mini->prof; i++){
            loca = move(loca, trajet[i]);
        }
        nb_phase++;

    }
}
}



