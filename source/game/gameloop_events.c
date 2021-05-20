/*
** EPITECH PROJECT, 2021
** gameloop_event.c
** File description:
** .
*/

#include "../../include/my_rpg.h"

void open_pause(screen_t *screen, gameloop_t *game)
{
    if (screen->pause->pasuestate == pauseclosed && \
    sfKeyboard_isKeyPressed(sfKeyP)) {
        screen->pause->pasuestate = pauseopen;
        screen->mode = 5;
        return;
    }
}

int menu_keyboard_opener_two(screen_t *screen,
gameloop_t *game, float elapsed_time)
{
    if (game->quest_log_state == questlogclosed &&
        sfKeyboard_isKeyPressed(sfKeyQ) && elapsed_time > 100) {
        game->quest_log_state = questlogopen;
        sfClock_restart(game->clicktimer);
        return (1);
    }
    if (game->quest_log_state == questlogopen &&
        sfKeyboard_isKeyPressed(sfKeyQ) && elapsed_time > 100) {
        game->quest_log_state = questlogclosed;
        sfClock_restart(game->clicktimer);
        return (1);
    }
    return (0);
}

void menu_keyboard_opener(screen_t *screen, gameloop_t *game)
{
    float elapsed_time = sfTime_asMilliseconds\
    (sfClock_getElapsedTime(game->clicktimer));

    if (game->menu_state == statmenuclosed && sfKeyboard_isKeyPressed(sfKeyI)
    && elapsed_time > 100) {
        game->menu_state = statmenuopen;
        sfClock_restart(game->clicktimer);
        return;
    }
    if (game->menu_state == statmenuopen && sfKeyboard_isKeyPressed(sfKeyI)
    && elapsed_time > 100) {
        game->menu_state = statmenuclosed;
        sfClock_restart(game->clicktimer);
        return;
    }
    if (menu_keyboard_opener_two(screen, game, elapsed_time) == 1)
        return;
    open_pause(screen, game);
}

void gameloop_events(screen_t *screen, gameloop_t *game)
{
    while (sfRenderWindow_pollEvent(screen->window, &game->event)) {
        if (game->event.type == sfEvtClosed) {
            sfRenderWindow_close(screen->window);
        }
        if (game->state != world)
            return;
        if (sfKeyboard_isKeyPressed(sfKeyW))
            move_player_up(game, screen);
        if (sfKeyboard_isKeyPressed(sfKeyS))
            move_player_down(game, screen);
        if (sfKeyboard_isKeyPressed(sfKeyA))
            move_player_left(game, screen);
        if (sfKeyboard_isKeyPressed(sfKeyD))
            move_player_right(game, screen);
        menu_keyboard_opener(screen, game);
    }
}