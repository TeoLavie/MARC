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

t_node *createNode(int val, int nb_sons, int depth);