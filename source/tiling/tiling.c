/*
** EPITECH PROJECT, 2021
** tiling.c
** File description:
** .
*/

#include "../../include/my_rpg.h"

int display_room()
{
    return 0;
}

sfSprite *sprite_tiled_area(int **area, sfTexture **tileset,
    sfRenderWindow *render, sfVector2f start_position)
{
    sfVector2f center = get_window_center(render);
    sfVector2i dimensions = get_area_dimensions(area);
    int tile_size = sfTexture_getSize(tileset[0]).x;
    sfVector2f position;
    int total_area = dimensions.x * dimensions.y;
    sfSprite **output = malloc(sizeof(sfSprite*) * (total_area + 1));
    int index = 0;
    output[total_area] = NULL;
    for (int y = 0; y < dimensions.y; y++) {
        for (int x = 0; x < dimensions.x; x++) {
            output[index] = sfSprite_create();
            sfSprite_setTexture(output[index], tileset[area[y][x]], sfTrue);
            position.x = center.x - ((dimensions.x / 2) *
            tile_size) + x * tile_size;
            position.y = center.y - ((dimensions.y / 2) *
            tile_size) + y * tile_size;
            sfSprite_setPosition(output[index], position);
            index++;
        }
    }
    return output;
}

void draw_tiles(room *rm, game *gm, sfRenderWindow *screen)
{
    sfVector2f starting_pos;

    if (!gm->tile_sprites) {
        starting_pos = get_start_pos(rm, gm, screen);
        gm->tile_sprites = sprite_tiled_area(rm->tiling,
        gm->tileset, gm->render, starting_pos);
    }
    for (int i = 0; gm->tile_sprites[i]; i++)
        sfRenderWindow_drawSprite(screen, gm->tile_sprites[i], NULL);
}