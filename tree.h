//
// Created by waguet on 14/11/2024.
//
#include "moves.h"
#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#endif //UNTITLED1_TREE_H

/* définition du type noeud*/
typedef struct s_node{
    int value;
    int depth;
    struct s_node **sons;
    int nbSons;
    t_localisation loc;

}t_node;

/* définition du type arbre*/
typedef struct s_tree
{
    t_node *root ;
} t_tree ;

t_node *createNode(int, int, int,t_localisation );
void addNode(t_node *,t_map);
t_tree createTree(int,int,t_orientation,t_map);
void displayTree(t_tree);
void displayNode(t_node *);
void fillNodes(t_node*,t_map);