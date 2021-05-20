/*
** EPITECH PROJECT, 2021
** load_game.c
** File description:
** .
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "../../include/my_rpg.h"

sfTexture **load_tileset(char *args)
{
    char *path = malloc(sizeof(char) * (my_strlen(args) + 1));
    char *buffer = NULL;

    path = my_strcpy(path, args);
    buffer = read_file_rpg(path);

    if (!buffer) {
        my_putstr("unable to create a buffer");
        return (84);
    }
    char **tile_paths = my_str_to_word_array(buffer, '\n');
    int n_tiles;
    sfTexture **output = NULL;
    for (n_tiles = 0; tile_paths[n_tiles]; n_tiles++);
    output = malloc(sizeof(sfTexture *) * n_tiles);
    for (int i = 0; tile_paths[i]; i++)
        output[i] = sfTexture_createFromFile(tile_paths[i], NULL);
    return output;
}

game *load_game(char *args, screen_t *screen)
{
    game *output = malloc(sizeof(game));

    output->render = screen->window;

    output->tileset = load_tileset(args);
    output->tile_sprites = NULL;

    if (!output->render) {
        my_putstr("render not created\n");
        return (84);
    }
        if (!output->tileset) {
        my_putstr("tileset not created\n");
        return (84);
    }

    return output;
}