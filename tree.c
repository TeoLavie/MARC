//
// Created by waguet on 14/11/2024.
//

#include "tree.h"
#include <stdlib.h>

t_node *createNode(int val, int nb_sons, int depth)
{
    t_node *new_node;
    new_node = (t_node *)malloc(sizeof(t_node));
    new_node->value = val;
    new_node->nbSons = nb_sons;
    new_node->depth = depth;
    new_node->sons = (t_node **)malloc(nb_sons*sizeof(t_node *));
    for (int i=0; i <nb_sons; i++)
    {
        new_node->sons[i]=NULL;
    }
    return new_node;
}

/**
 void addNode(*Node_père,int node_wanted){
    si Node_père existe pas alors Root vide alors Node deviens root
    sinon Node=createNode(???,Node_père->nb_sons-1,Node_père->depth-1
    *(Node_père->sons+node_wanted) = &Node
 */
