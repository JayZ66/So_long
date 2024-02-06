/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:19:36 by jeza              #+#    #+#             */
/*   Updated: 2024/02/05 20:20:35 by jeza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// strcmp allow us to compare the content of the map and not the add.
int map_shape_error(t_game *game)
{
    int i;
    int j;
    
    i = 0;
    while (game->map[i]) // Voir si correspond bien à y (coord.)
    {
        j = i + 1;
        while(game->map[j])
        {
            if (ft_strcmp(game->map[i], game->map[j]) != 0)
            {
                write(1, "Error\n", 6);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int map_wall_error(t_game *game)
{
    int i; // For lines, like y.
    int j; // For column, like x.

    i = 0;
    j = 0;
    // Compare the first_column, so you move on the rows.
    while(i < game->map_height) // Hauteur win != de hauteur map non ? Donc 2 var. ?
    {
        if (game->map[i][0] != 1)
        {
            write(1, "Error\n", 6);
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < game->map_height) // Compare the last columnn.
    {
        if (game->map[i][game->map_width] != 1) // Check if '1' ?
        {
            write(1, "Error\n", 6);
            return (1);
        }
        i++;
    }
    while (j < game->map_width) // Compare the first row.
    {
        if (game->map[0][j] != 1)
        {
            write(1, "Error\n", 6);
            return (1);
        }
        j++;
    }
    j = 0;
    while (j < game->map_width) // Compare the last row.
    {
        if (game->map[game->map_height][j] != 1)
        {
            write(1, "Error\n", 6);
            return(1);
        }
        j++;
    }
    return (0);
}

int read_map(const char *file, t_game *game)
{
    int     check_read;
    int     fd;
    char    *line;
    int     i;

    check_read = 0;
    i = 0;
    game->map_height = 0; // To get the nb of lines.
    game->map_width = 0; // To get the number of rows.
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
         write(1, "Error\n", 6);
        return (1);
    }
    while ((line = get_next_line(fd)))
    {
        if (game->map_height == 0) // Mise à jour de la largeur de la map si c'est la première ligne lue.
            game->map_width = ft_strlen(line);
        game->map[i] = ft_strdup(line); // Check if i s'incrémente après le 1er tour ?
        game->map_height++;
        free(line);
        i++;
    }
    close (fd);
    if (check_read == -1)
    {
         write(1, "Error\n", 6);
        return (1);
    }
    return (0);
}
// Je lis et j'incrémente en fonction de ce que je trouve : exit == 1,
// c > 0, P == 1, first & last line == 1, first & last column == 1. => Parsing.

// Will check the path taken by the player, and will put 'x' when the player has passed on it.
// With floodfill.
// int check_path(t_game *game)
// {
//     char    **temp_map;

//     temp_map = game->map;
// }