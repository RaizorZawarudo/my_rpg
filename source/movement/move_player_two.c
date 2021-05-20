/*
** EPITECH PROJECT, 2021
** possible_basic_structure
** File description:
** move_player
*/

#include "../../include/my_rpg.h"

int check_hitbox_wall_helper(gameloop_t *game, \
sfVector2f player, screen_t *screen, sfVector2f curr)
{
    if ((curr.x <= player.x || curr.x <= player.x + 47/2) &&
        (curr.x + 47 >= player.x ||
        curr.x + 47 >= player.x + 47/2) &&
        (curr.y <= player.y || curr.y <= player.y + 47) &&
        (curr.y + 47 >= player.y ||
        curr.y + 47 >= player.y + 47)) {
            return 1;
    }
    return 0;
}