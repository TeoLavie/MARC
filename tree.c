//
// Created by waguet on 14/11/2024.
//

#include "tree.h"
#include "moves.h"
#include "loc.h"
#include <stdlib.h>
#include <stdio.h>




t_node *createNode(int val, int nb_sons, int depth,t_localisation loc)
{
    ///Créer un noeud
    t_node *new_node;
    new_node = (t_node *)malloc(sizeof(t_node));
    new_node->value = val;
    new_node->nbSons = nb_sons;
    new_node->depth = depth;
    new_node->sons = (t_node **)malloc(nb_sons*sizeof(t_node *));
    new_node->loc = loc;
    for (int i=0; i <nb_sons; i++)
    {
        new_node->sons[i]=NULL;
    }
    return new_node;
}


void addNode(t_node *pn,t_map map){
    //Fonction Add Node, créer un Noeud pour tous les fils du noeud en entrée
    int i = 0;
    t_move *m = getRandomMoves(pn->nbSons);
    while( i < pn->nbSons){
            t_localisation new_loc;
            new_loc = translate(pn->loc,m[i]);
            if (isValidLocalisation(new_loc.pos,map.x_max,map.y_max)) {
                int val = map.costs[new_loc.pos.y][new_loc.pos.x];
                pn->sons[i] = createNode(val, pn->nbSons - 1, pn->depth + 1, new_loc);
            }
            else{
                pn->sons[i] = createNode(1000000, pn->nbSons - 1, pn->depth + 1, new_loc);
            }
            i++;
    }
}

t_tree createTree(int pos_x,int pos_y,t_orientation ori,t_map map){
    //Creer la racine de l'arbre et l'initialise avec la bon noeud
    t_tree t;
    int val = map.costs[pos_x][pos_y];
    t.root = createNode(val,9,0, loc_init(pos_x,pos_y,ori));
    return t;
}
void displayTree(t_tree t){
    //Fonction de test faisant un affichage très sommaire de l'arbre
    displayNode(t.root);
}
void displayNode(t_node *pn){
    //Affiche tout les noeud enfant d'un noeud entré
    int i = 0;
    printf("[ %d ]",pn->value);
    while(i < pn->nbSons){
        if(pn->sons[i]!= NULL) {
            displayNode(pn->sons[i]);
        }
        else{ printf("[]");}
        i = i + 1;
    }
}

void fillNodes(t_node *pn,t_map map){
    ///rempli tous les noeuds enfants
    if(pn->nbSons !=0){
        addNode(pn,map);
        for(int i = 0;i < pn->nbSons ;i++){
            fillNodes(pn->sons[i],map);
        }
    }
}


