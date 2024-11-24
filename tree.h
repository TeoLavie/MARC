//
// Created by waguet on 14/11/2024.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#endif //UNTITLED1_TREE_H

/* définition du type noeud*/
typedef struct s_node{
    int value;
    int depth;
    struct s_node **sons;
    int nbSons
}t_node;

/* définition du type arbre*/
typedef struct s_tree
{
    t_node *root ;
} t_tree ;

t_node *createNode(int, int, int );
t_tree createTree(int );
void DisplayTree(t_tree);
void DisplayNode(t_node *);