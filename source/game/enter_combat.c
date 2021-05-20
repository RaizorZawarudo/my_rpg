/*
** EPITECH PROJECT, 2021
** possible_basic_structure
** File description:
** enter_combat
*/

#include "../../include/my_rpg.h"

void exp_increase(gameloop_t *game)
{
    static int exp_limit = 500;

    game->player1->exp += 100;
    while (game->player1->exp >= exp_limit) {
        game->player1->level += 1;
        game->player1->hpmax += game->player1->hpmax * 0.10;
        game->player1->hp = game->player1->hpmax;
        game->player1->def += game->player1->def * 0.10;
        game->player1->atk += game->player1->atk * 0.10;
        game->player1->magic += game->player1->magic * 0.10;
        game->player1->exp -= exp_limit;
        exp_limit += exp_limit * 0.20;
    }
    if (game->player1->exp < 0) {
        game->player1->exp = 0;
    }
}

void item_drop(gameloop_t *game)
{
    int b = 0;
    int random_nb = 0;
    sfTime elapsed_time = sfClock_getElapsedTime(game->player1->anim_clock);

    for (int i = 0; game->mob[game->mobfightindex].loot_table[i]; i++)
        b += 1;
    b -= 2;
    if ( b < 0)
        b = 0 - b;
    if (b == 0)
        b = 1;
    random_nb = elapsed_time.microseconds % b;
    for (int i = 0; i < 8; i++) {
        if (game->player1->inventory[i].item_index == -1) {
            game->player1->inventory[i] = \
            game->items[game->mob[game->mobfightindex].loot_table[random_nb]];
            break;
        }
    }
}

void player_dead(screen_t *screen)
{
     char *args = malloc(sizeof(char) * \
    (my_strlen("./assets/data/tile_paths") + 1));

    args = my_strcpy(args, "./assets/data/tile_paths");
    if (screen->init == 0) {
        screen->game = init_game_struct();
        screen->game->gm = load_game(args, screen);
        screen->level = 0;
        screen->max_reached = 0;
        screen->setting->prev_s = 0;
        screen->init = 1;
        screen->mode = 0;
    }
}

void start_combat(gameloop_t *game, screen_t *screen)
{
    int cond = 0;

    if (game->state == fight) {
        cond = fightsystem(game);
        if (cond != -1) {
            item_drop(game);
            exp_increase(game);
            game->mob[game->mobfightindex].is_alive = 0;
            game->mob[game->mobfightindex].position = (sfVector2f) {0, 90000};
        } else
            player_dead(screen);
        game->state = world;
    }
}

void enter_combat(gameloop_t *game, screen_t *screen)
{
    for (int i = 0; i < game->mob->unit_amount; i++) {
        if (game->mob[i].minspawnlevel == screen->level && check_in_move_radius
            (game->player1->position, game->mob[i].position, 48)) {;
            game->state = fight;
            game->mob[i].infight = 1;
            game->mobfightindex = i;
            break;
        }
    }
    start_combat(game, screen);
}