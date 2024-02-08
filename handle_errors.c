/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:19:36 by jeza              #+#    #+#             */
/*   Updated: 2024/02/08 14:31:52 by jeza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int map_shape_error(t_game *game)
{
    int i;
    size_t  first_line_length;
    
    i = 0;
    first_line_length = ft_strlen(game->map[0]);
    while (game->map[i]) // Voir si correspond bien à y (coord.)
    {
        if (ft_strlen(game->map[i]) != first_line_length)
        {
            write(1, "Error\n", 6);
            return (1);
        }
        i++;
    }
    return (0);
}

int map_wall_error(t_game *game)
{
    int theo;

    theo = -1;
    while (game->map[0][++theo])
        if (game->map[0][theo] != '1')
            return (1);
    theo = -1;
    while (game->map[game->map_height - 1][++theo])
        if (game->map[game->map_height - 1][theo] != '1')
            return (1);
    theo = -1;
    while (game->map[++theo])
        if (game->map[theo][0] != '1' || (game->map[theo][game->map_width] != '1' && game->map[theo][game->map_width] != '\0'))
            return (1);
    return (0);
}

// int read_map(const char *file, t_game *game)
// {
//     int     fd;
//     char    *line;
//     int     i;

//     i = 0;
//     game->map_height = 0; // To get the nb of lines.
//     game->map_width = 0; // To get the number of rows.
//     fd = open(file, O_RDONLY);
//     if (fd == -1)
//     {
//         write(1, "Error\n", 6);
//         return (1);
//     }
//     while ((line = get_next_line(fd)))
//     {
//         if (game->map_height == 0) // Mise à jour de la largeur de la map si c'est la première ligne lue.
//             game->map_width = ft_strlen(line) + 1;
//         game->map[i] = ft_strdup(line); // Check if i s'incrémente après le 1er tour ?
//         game->map_height++;
//         free(line);
//         i++;
//     }
//     close (fd);
//     return (0);
// }


// Will check the path taken by the player, and will put 'x' when the player has passed on it.
// With floodfill.
// int check_path(t_game *game)
// {
//     char    **temp_map;

//     temp_map = game->map;
// }

/*
3 étapes : 
- D'abord je lis.
- Je malloc mon tab. puis chaque ligne.
- Je relis pour ensuite mettre dans mon double tab. qui est malloc.
*/

void    read_map(const char *file, t_game *game)
{
    int     fd;
    char    *line;

    game->map_height = 0;
    game->map_width = 0;
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        write(1, "Error\n", 6);
        return ;
    }
    while ((line = get_next_line(fd)))
    {
        if (game->map_height == 0)
            game->map_width = ft_strlen(line) - 1;
        game->map_height++;
    }
    close (fd);
}

/*
La première allocation est faite pour l'ensemble du tableau (les pointeurs de ligne), 
et ensuite, dans la boucle, chaque ligne individuelle est allouée. 
Cela crée un tableau de tableaux.

Voici une explication plus détaillée :

game->map : C'est un pointeur de pointeur (char **). 
Il pointe vers le début du tableau de pointeurs.

game->map[i] : C'est un pointeur (char *). Chaque élément game->map[i] pointe vers 
le début de la ligne i du tableau bidimensionnel.

Donc, lorsque vous allouez de la mémoire pour les "pointeurs de ligne" avec 
game->map = (char **)malloc(map_height * sizeof(char *)), cela crée un tableau de 
map_height pointeurs, où chaque pointeur peut pointer vers le début de sa ligne respective.
*/
void   alloc_map(t_game *game)
{
    int i;
    int j;

    j = 0;
    i = 0;
    game->map = (char **)malloc(game->map_height * sizeof(char *));
    if (game->map == NULL)
        return ;
    while (i < game->map_height)
    {
        game->map[i] = (char *)malloc((game->map_width + 1) * sizeof(char));
        if (game->map[i] == NULL)
        {
            while (j < i)
            {
                free(game->map[j]);
                j++;
            }
            free(game->map);
            return ;
        }
        i++;
    }
}

void    fill_tab(const char *file, t_game *game)
{
    int     fd;
    char    *line;
    int     i;

    i = 0;
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return ;
    while ((line = get_next_line(fd)))
    {
        game->map[i] = ft_strdup(line);
        free(line);
        i++;
    }
    close (fd);
}
