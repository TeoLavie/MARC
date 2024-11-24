//
// Created by waguet on 14/11/2024.
//

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>


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

void addNode(t_node *pn){
    int i = 0;
    while( i < pn->nbSons){
        pn->sons[i] = createNode(10,pn->nbSons-1,pn->depth+1);
        i++;
    }
}

t_tree createTree(int val){
    t_tree t;
    t.root = createNode(val,9,0);
    return t;
}
void DisplayTree(t_tree t){
    DisplayNode(t.root);
}
void DisplayNode(t_node *pn){
    int i = 0;
    printf("[ %d ]");
    while(i < pn->nbSons){
        DisplayNode(pn->sons[i]);
        i++;
    }
}
/**
 void addNode(*Node_père,int node_wanted){
    si Node_père existe pas alors Root vide alors Node deviens root
    sinon Node=createNode(???,Node_père->nb_sons-1,Node_père->depth-1
    *(Node_père->sons+node_wanted) = &Node
 */
