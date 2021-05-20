/*
** EPITECH PROJECT, 2021
** animate_fx_helper.c
** File description:
** .
*/

#include "../../include/my_rpg.h"

void launch_npcdisapearparticles(gameloop_t *game, sfVector2f npcpos)
{
    game->part_fx[3].active = 1;
    sfSprite_setPosition(game->part_fx[3].psprite, npcpos);
    sfClock_restart(game->part_fx[3].anim_clock);
    sfClock_restart(game->part_fx[3].life_clock);
}