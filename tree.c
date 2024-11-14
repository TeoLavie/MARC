//
// Created by waguet on 14/11/2024.
//

#include "tree.h"
typedef struct s_node{
    int value;
    int depth;
    struct s_node **sons;
    int nbSons
}t_node;