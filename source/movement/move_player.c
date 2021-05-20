/*
** EPITECH PROJECT, 2021
** possible_basic_structure
** File description:
** move_player
*/

#include "../../include/my_rpg.h"

int check_hitbox_wall(gameloop_t *game, sfVector2f player, screen_t *screen)
{
    sfVector2f backdoor;
    sfVector2f frontdoor;

    frontdoor.x = 1250;
    frontdoor.y = 7 * 47;
    backdoor.x = 0;
    backdoor.y = 7 * 47;
    if (check_hitbox_wall_helper(game, player, screen, \
    game->rm->active_door) == 1) {
            return 1;
    } else if (check_hitbox_wall_helper(game, player, screen, \
    backdoor) == 1) {
            return 1;
    } else if (check_hitbox_wall_helper(game, player, screen, \
    frontdoor) == 1) {
            if (screen->max_reached > screen->level)
                return 1;
            else
                return 0;
    }
    return 0;
}

void move_player_up(gameloop_t *game, screen_t *screen)
{
    sfVector2f temp;
    temp.x = game->player1->position.x;
    temp.y = game->player1->position.y;
    temp.y -= game->player1->movespeed;

    if (temp.y <= 47 && check_hitbox_wall(game, temp, screen) == 0)
        return;
    game->player1->position.y -= game->player1->movespeed;
    game->player1->prev_pos.y = temp.y;
    game->player1->move_dir = MOVE_UP;
    game->player1->prev_dir = MOVE_UP;
}

void move_player_down(gameloop_t *game, screen_t *screen)
{
    sfVector2f temp;

    temp.x = game->player1->position.x;
    temp.y = game->player1->position.y;
    temp.y += game->player1->movespeed;
    if (temp.y >= 672 && check_hitbox_wall(game, temp, screen) == 0)
        return;
    game->player1->position.y += game->player1->movespeed;
    game->player1->prev_pos.y = temp.y;
    game->player1->move_dir = MOVE_DOWN;
    game->player1->prev_dir = MOVE_DOWN;
}

void move_player_left(gameloop_t *game, screen_t *screen)
{
    sfVector2f temp;

    temp.x = game->player1->position.x;
    temp.y = game->player1->position.y;
    temp.x -= game->player1->movespeed;
    if (temp.x <= 40 && check_hitbox_wall(game, temp, screen) == 0)
        return;
    game->player1->position.x -= game->player1->movespeed;
    game->player1->prev_pos.x = temp.x;
    game->player1->move_dir = MOVE_LEFT;
    game->player1->prev_dir = MOVE_LEFT;
}

void move_player_right(gameloop_t *game, screen_t *screen)
{
    sfVector2f temp;

    temp.x = game->player1->position.x;
    temp.y = game->player1->position.y;
    temp.x += game->player1->movespeed;
    if (temp.x >= 1233 && check_hitbox_wall(game, temp, screen) == 0)
        return;
    game->player1->position.x += game->player1->movespeed;
    game->player1->prev_pos.x = temp.x;
    game->player1->move_dir = MOVE_RIGHT;
    game->player1->prev_dir = MOVE_RIGHT;
}