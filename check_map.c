/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:32:25 by jeza              #+#    #+#             */
/*   Updated: 2024/02/08 15:22:37 by jeza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int check_exit(t_game *game)
{
    int     i;
    int     j;
    size_t  exit_count;

    i = 0;
    exit_count = 0;
    while(i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            if (game->map[i][j] == 'E') // Check la position de mon exit.
                exit_count++;
            j++;
        }
        i++;
    }
    if (exit_count != 1)
    {
        write(1, "Error\n", 6);
        return (1);
    }
    return (0);
}

int check_collect(t_game *game)
{
    int     i;
    int     j;
    size_t  collect_count;

    i = 0;
    collect_count = 0;
    while (i < game->map_height)
    {
        j = 0;
        while(j < game->map_width)
        {
            if (game->map[i][j] == 'C')
                collect_count++;
            j++;
        }
        i++;
    }
    if (collect_count < 1)
    {
        write(1, "Error\n", 6);
        return (1);
    }
    return (0);
}

int check_player(t_game *game)
{
    int     i;
    int     j;
    size_t  player_count;

    i = 0;
    player_count = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            if (game->map[i][j] == 'P')
            {
                game->player.pos_x = j;
                game->player.pos_y = i;
                player_count++;
            }
            j++;
        }
        i++;
    }
    if (player_count != 1)
    {
        write(1, "Error\n", 6);
        return (1);
    }
    return (0);
}