/*
** EPITECH PROJECT, 2021
** init_statmenu3.c
** File description:
** init_statmenu3
*/

#include "../../include/my_rpg.h"

void init_stat_helper(statmenu_t *statmenu)
{
    stats_menu_shapes(statmenu);
    stats_menu_level(statmenu);
    stats_menu_attack(statmenu);
    stats_menu_defense(statmenu);
    stats_menu_speed(statmenu);
    stats_menu_magic(statmenu);
    stats_menu_hp(statmenu);
    stats_menu_maxhp(statmenu);
    stats_menu_exp(statmenu);
    stats_menu_inventory(statmenu);
}