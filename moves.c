//
// Created by flasque on 19/10/2024.
//

#include <stdlib.h>
#include "moves.h"
#include "map.h"
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
    t_position pos_in_front = loc.pos; // Utilisation du membre `pos` pour accéder aux coordonnées

    // Determine the position in front based on the rover's orientation
    switch (loc.ori) {
        case NORTH:
            pos_in_front.y -= 1; // Déplacement vers le nord (y décroît)
            break;
        case EAST:
            pos_in_front.x += 1; // Déplacement vers l'est (x croît)
            break;
        case SOUTH:
            pos_in_front.y += 1; // Déplacement vers le sud (y croît)
            break;
        case WEST:
            pos_in_front.x -= 1; // Déplacement vers l'ouest (x décroît)
            break;
        default:
            return -1; // Orientation invalide
    }

    // Check if the position in front is within the bounds of the map
    if (pos_in_front.x >= 0 && pos_in_front.x < map.x_max &&
        pos_in_front.y >= 0 && pos_in_front.y < map.y_max) {
        return map.soils[pos_in_front.y][pos_in_front.x];
    }

    // Return -1 if the position is out of bounds
    return -1;
}