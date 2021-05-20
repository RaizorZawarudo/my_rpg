/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** init struct scene + game
*/

#include "../../include/my_rpg.h"

void init_game_struc_bis(gameloop_t *game)
{
    game->questlog = init_quest_log(game->questlog);
    game->menu_state = statmenuclosed;
    game->quest_log_state = questlogclosed;
    game->clicktimer = sfClock_create();
    game->rm = malloc(sizeof(room));
    game->rm = create_room_struct(28, 16, NULL);
    game->mobfightindex = -1;
    game->items = init_itemslist("./assets/file/item_data.csv");
    game->player1->inventory[0] = game->items[2];
    game->player1->inventory[5] = game->items[19];
    game->player1->inventory[7] = game->items[13];
    game->victory = sfMusic_createFromFile("./assets/music/victory.ogg");
    game->part_fx = init_fx("./assets/file/particle_effects.csv");
}

gameloop_t *init_game_struct(void)
{
    gameloop_t *game = malloc(sizeof(gameloop_t));
    game->questlibrary = init_all_quests("./assets/file/quest_list.csv");
    game->mob = parse_monsters("./assets/file/mob_data.csv");
    game->npc = init_npcs("./assets/file/npc_data.csv");
    game->player1 = init_player();
    game->state = world;
    game->statmenu = init_statmenu(game->statmenu);
    init_game_struc_bis(game);
    return game;
}

screen_t *init_sceenes(screen_t *screen)
{
    screen->main = init_main(screen->main);
    screen->help = init_help(screen->help);
    screen->setting = init_setting(screen->setting);
    screen->fight = init_fight(screen->fight);
    screen->background = sfSprite_create();
    screen->bgt = sfTexture_createFromFile\
    ("./assets/sprites/background/dungeon.jpg", NULL);
    sfSprite_setTexture(screen->background, screen->bgt, sfTrue);
    return screen;
}

void prep_struc_helper(char *args, screen_t *screen)
{
    screen->game->gm = load_game(args, screen);
    screen->level = 0;
    screen->max_reached = 0;
    screen->pause = init_pause();
    screen->soundtrack =
    sfMusic_createFromFile("./assets/music/soundtrack.ogg");
    screen->death = sfMusic_createFromFile("./assets/music/death.ogg");
    sfMusic_setVolume(screen->death, screen->volume);
    sfMusic_setVolume(screen->soundtrack, screen->volume);
    sfMusic_setVolume(screen->game->victory, screen->volume);
}

screen_t *prep_struct(screen_t *screen)
{
     char *args = malloc(sizeof(char) * \
    (my_strlen("./assets/data/tile_paths") + 1));

    screen = malloc(sizeof(screen_t));
    screen->video = (sfVideoMode) {1280, 720, 32};
    screen->window = sfRenderWindow_create(screen->video, "my_rpg", \
    sfResize | sfClose, NULL);
    screen->volume = 50;
    screen->mode = 0;
    screen = init_sceenes(screen);
    screen->game = init_game_struct();
    args = my_strcpy(args, "./assets/data/tile_paths");
    prep_struc_helper(args, screen);
    return screen;
}