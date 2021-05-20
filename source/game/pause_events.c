/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** pause events
*/

#include "../../include/my_rpg.h"

int button_is_clicked_pause_two(pause_t *pause, sfVector2f pos_mouse)
{
    if (pause->button[2]->pos.x <= pos_mouse.x && \
        pos_mouse.x <= pause->button[2]->pos.x + 200 && \
        pause->button[2]->pos.y <= pos_mouse.y && \
        pos_mouse.y <= pause->button[2]->pos.y + 50) {
            return 3;
    }
    if (pause->button[3]->pos.x <= pos_mouse.x && \
        pos_mouse.x <= pause->button[3]->pos.x + 200 && \
        pause->button[3]->pos.y <= pos_mouse.y && \
        pos_mouse.y <= pause->button[3]->pos.y + 50) {
            return 4;
    }
    if (pause->button[4]->pos.x <= pos_mouse.x && \
        pos_mouse.x <= pause->button[4]->pos.x + 200 && \
        pause->button[4]->pos.y <= pos_mouse.y && \
        pos_mouse.y <= pause->button[4]->pos.y + 50) {
            return 5;
    }
    return 0;
}

int button_is_clicked_pause(pause_t *pause, sfVector2f pos_mouse)
{
    if (pause->button[0]->pos.x <= pos_mouse.x && \
        pos_mouse.x <= pause->button[0]->pos.x + 200 && \
        pause->button[0]->pos.y <= pos_mouse.y && \
        pos_mouse.y <= pause->button[0]->pos.y + 50)
        return 1;
    if (pause->button[1]->pos.x <= pos_mouse.x && \
        pos_mouse.x <= pause->button[1]->pos.x + 200 && \
        pause->button[1]->pos.y <= pos_mouse.y && \
        pos_mouse.y <= pause->button[1]->pos.y + 50) {
        return 2;
    }
    return button_is_clicked_pause_two(pause, pos_mouse);
}

void switch_pause_two(int ret, screen_t *screen, char *args)
{
    if (ret == 3) {
        screen->pause->pasuestate = pauseclosed;
        screen->setting->prev_s = 5;
        screen->mode = 3;
    }
    if (ret == 4) {
        if (screen->init == 0) {
            screen->pause->pasuestate = pauseclosed;
            screen->game = init_game_struct();
            screen->game->gm = load_game(args, screen);
            screen->level = 0;
            screen->max_reached = 0;
            screen->setting->prev_s = 0;
            screen->init = 1;
            screen->mode = 0;
        }
    }
    if (ret == 5)
        sfRenderWindow_close(screen->window);
}

void switch_pause(int ret, screen_t *screen)
{
    char *args = malloc(sizeof(char) * \
    (my_strlen("./assets/data/tile_paths") + 1));
    
    args = "./assets/data/tile_paths";
    if (ret == 1) {
        screen->pause->pasuestate = pauseclosed;
        screen->mode = 1;
    }
    if (ret == 2) {
        if (screen->init == 0) {
            screen->pause->pasuestate = pauseclosed;
            screen->game = init_game_struct();
            screen->game->gm = load_game(args, screen);
            screen->level = 0;
            screen->max_reached = 0;
            screen->init = 1;
            screen->mode = 1;
        }
    }
    switch_pause_two(ret, screen, args);
}

void analyse_events_pause(screen_t *screen,
pause_t *pause , sfVector2f pos_mouse)
{
    int ret = 0;
    while (sfRenderWindow_pollEvent(screen->window, &pause->event)) {
        if (pause->event.type == sfEvtClosed) {
            sfRenderWindow_close(screen->window);
        }
        if (pause->pasuestate == pauseopen &&
            sfKeyboard_isKeyPressed(sfKeyP)) {
            pause->pasuestate = pauseclosed;
            screen->mode = 1;
        }
        if (pause->event.type == sfEvtMouseButtonPressed) {
            ret = button_is_clicked_pause(pause, pos_mouse);
        }
        switch_pause(ret, screen);
    }
}