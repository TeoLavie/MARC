//
// Created by flasque on 19/10/2024.
//

#include <stdlib.h>
#include "moves.h"
#include "map.h"
#include "tree.h"
/* prototypes of local functions */
/* local functions are used only in this file, as helper functions */

/**
 * @brief Function to rotate the robot according to a move and its actual orientation
 * @param ori : the actual orientation of the robot
 * @param move : the move to do
 * @return the new orientation of the robot
 */
t_orientation rotate(t_orientation, t_move );

/**
 * @brief function to translate the robot according to a move and its actual position
 * @param loc : the actual localisation of the robot
 * @param move : the move to do
 * @return the new localisation of the robot
 */
t_localisation translate(t_localisation , t_move);

/* definition of local functions */

t_orientation rotate(t_orientation ori, t_move move)
{
    int rst=0;
    switch (move)
    {
        case T_LEFT:
            rst=3;
            break;
        case T_RIGHT:
            rst=1;
            break;
        case U_TURN:
            rst=2;
            break;
        default: // should not happen
            rst=0;
            break;
    }
    return (ori+rst)%4;
}

t_localisation translate(t_localisation loc, t_move move)
{
    /** rules for coordinates:
     *  - x grows to the right with step of +1
     *  - y grows to the bottom with step of +1
     *  - the origin (x=0, y=0) is at the top left corner
     */
    t_position res=loc.pos;
    switch (move) {
        case F_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 1;
                    break;
                case EAST:
                    res.x = loc.pos.x + 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 1;
                    break;
                case WEST:
                    res.x = loc.pos.x - 1;
                    break;
                default:
                    break;
            }
            break;
        case F_20:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 2;
                    break;
                case EAST:
                    res.x = loc.pos.x + 2;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 2;
                    break;
                case WEST:
                    res.x = loc.pos.x - 2;
                    break;
                default:
                    break;
            }
            break;
        case F_30:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 3;
                    break;
                case EAST:
                    res.x = loc.pos.x + 3;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 3;
                    break;
                case WEST:
                    res.x = loc.pos.x - 3;
                    break;
                default:
                    break;
            }
            break;
        case B_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y + 1;
                    break;
                case EAST:
                    res.x = loc.pos.x - 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y - 1;
                    break;
                case WEST:
                    res.x = loc.pos.x + 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return loc_init(res.x, res.y, loc.ori);

}

/* definitions of exported functions */

char *getMoveAsString(t_move move)
{
    return _moves[move];
}

t_localisation move(t_localisation loc, t_move move)
{
    t_localisation new_loc=loc;
    if ((move >=T_LEFT) && (move <= U_TURN))
    {
        new_loc.ori = rotate(loc.ori, move);
    }
    else
    {
        new_loc = translate(loc, move);
    }

    return new_loc;
}

void updateLocalisation(t_localisation *p_loc, t_move m)
{
    *p_loc = move(*p_loc, m);
    return;
}

t_move *getRandomMoves(int N)
{
    int nbmoves[]={22,15,7,7,21,21,7};
    int total_moves=100;
    t_move *moves = (t_move *)malloc(N * sizeof(t_move));
    for (int i = 0; i < N; i++)
    {
        int r = rand() % total_moves;
        int type=0;
        while (r >= nbmoves[type])
        {
            r -= nbmoves[type];
            type++;
        }
        nbmoves[type]--;
        total_moves--;
        moves[i] = (t_move )type;
    }
    return moves;
}


int getValueInFront(t_localisation loc, t_map map) {
    t_position pos_in_front = loc.pos;

    if(loc.ori == NORTH){
        pos_in_front.y -= 1;
    }
    else if(loc.ori == EAST){
        pos_in_front.x += 1;
    }
    else if(loc.ori == SOUTH){
        pos_in_front.y += 1;
    }
    else if(loc.ori == WEST){
        pos_in_front.x -= 1;
    }
    else {
        return -1;
    }


    // regarde si hors d la map
    if (pos_in_front.x >= 0 && pos_in_front.x < map.x_max &&
        pos_in_front.y >= 0 && pos_in_front.y < map.y_max) {
        return map.costs[pos_in_front.y][pos_in_front.x];
    }

    // si hors -1
    return -1;
}



// Ajouter la valeur du nœud actuel à la somme
// Si c'est une feuille (pas d'enfants), vérifier si c'est optimal
//  change best_sum si mieux
//regarde les enfants du nœud courant

void explorePaths(t_node *node, int current_sum, int *best_sum) {

    if (node == NULL) {
        return;
    }

    current_sum += node->value;


    if (node->nbSons == 0) {
        if (current_sum < *best_sum) {
            *best_sum = current_sum;
        }
        return;
    }


    for (int i = 0; i < node->nbSons; i++) {
        explorePaths(node->sons[i], current_sum, best_sum);
    }
}



int findOptimalPath(t_tree *tree) {
    if (tree == NULL || tree->root == NULL) {
        return -1; // Si arbre vide
    }

    int best_sum = 100000;
    explorePaths(tree->root, 0, &best_sum);
    return best_sum;
}
