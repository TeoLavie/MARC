//
// Created by waguet on 14/11/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#endif //UNTITLED1_TREE_H


typedef struct s_node{
    int value;
    int depth;
    struct s_node **sons;
    int nbSons
}t_node;

t_node *createNode(int val, int nb_sons)
{
    t_node *new node;
    new_node = (t_node *)malloc(sizeof(t_node));
    new_node->value = val;
    new_node->nbSons = nd_sons;
    new_node->sons = (t_node **)malloc(nb_sons*sizeof(t_node *));
    for (int i=0; i <nb_sons; i++)
    {
        new_node->sons[i]=NULL;
    }
    return new_node;
}