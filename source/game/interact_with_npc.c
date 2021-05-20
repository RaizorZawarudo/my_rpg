/*
** EPITECH PROJECT, 2021
** B-MUL-200-BER-2-1-myrpg-gylian.karsch
** File description:
** interact_with_npc
*/

#include "../../include/my_rpg.h"

void accept_quest(gameloop_t *game, int questindex)
{
    for (int i = 0; i < 8; i++) {
        if (game->player1->questlist[i].quest_index == -1) {
            game->player1->questlist[i] = \
            game->questlibrary[questindex];
            break;
        }
    }
}

void npc_particle(gameloop_t *game, screen_t *screen)
{
    if (game->state == npctalk) {
        game->npc[game->npcinteractindex].position = game->npc[
        game->npcinteractindex].prev_pos;
        game->npc[game->npcinteractindex].aggro = 0;
        display_text_npc(game, screen);
        accept_quest(game, game->npc[game->npcinteractindex].questnumber);
        if (game->npc[game->npcinteractindex].hasspawned == 0)
            launch_npcdisapearparticles(game,
            game->npc[game->npcinteractindex].position);
        game->npc[game->npcinteractindex].position = (sfVector2f) {2000, 0};
        game->npc[game->npcinteractindex].hasspawned = 1;
    }
}

void display_text_npc(gameloop_t *game, screen_t *screen)
{
    sfRectangleShape *tmp_background = sfRectangleShape_create();
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile("source/fightsystem/fonts/font.otf");
    char **str = NULL;
    int check = 0;

    str = my_str_to_word_array(game->questlibrary[game->npc[
    game->npcinteractindex].questnumber].quest_text, '.');
    sfRectangleShape_setSize(tmp_background, (sfVector2f) {1024, 572});
    sfRectangleShape_setPosition(tmp_background, (sfVector2f) {128, 74});
    sfRectangleShape_setFillColor(tmp_background, (sfColor) {255, 0, 0, 150});
    sfText_setCharacterSize(text, 40);
    sfText_setColor(text, sfWhite);
    sfText_setFont(text, font);
    sfRenderWindow_drawRectangleShape(screen->window, tmp_background, NULL);
    sfText_setString(text, game->questlibrary
    [game->npc[game->npcinteractindex].questnumber].quest_name);
    sfText_setPosition(text, (sfVector2f) {640 - my_strlen(game->questlibrary[
    game->npc[game->npcinteractindex].questnumber].quest_name) / 2 * 20, 120});
    sfRenderWindow_drawText(screen->window, text, NULL);
    sfText_setCharacterSize(text, 20);
    for (int i = 0; str[i] != NULL; i++) {
        sfText_setPosition(text, (sfVector2f) {640 -
        my_strlen(str[i]) / 2 * 10, 200 + (i * 20)});
        sfText_setString(text, str[i]);
        sfRenderWindow_drawText(screen->window, text, NULL);
    }
    sfText_setString(text, "Press Enter to continue");
    sfText_setPosition(text, (sfVector2f) {640 - my_strlen(
    "Press Enter to continue") / 2 * 10, 550});
    sfRenderWindow_drawText(screen->window, text, NULL);
    sfRenderWindow_display(screen->window);
    while (1) {
        if (sfKeyboard_isKeyPressed(sfKeyReturn)) {
            break;
        }
    }
}

void interact_with_npc(gameloop_t *game, screen_t *screen)
{
    for (int i = 0; i < game->npc->unit_amount; i++) {
        if (game->npc[i].minspawnlevel == screen->level) {
            if (check_in_move_radius(game->player1->position,
            game->npc[i].position, 48) && game->state == world) {
                game->npc[i].prev_pos = game->npc[i].position;
                game->state = npctalk;
                game->npc[i].intalk = 1;
                game->npcinteractindex = i;
                break;
            }
        }
    }
    npc_particle(game, screen);
    game->state = world;
}