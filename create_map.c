/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:40:12 by jeza              #+#    #+#             */
/*   Updated: 2024/02/15 14:34:39 by jeza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
3 steps : 
- First i'm going to read.
- Then i malloc the array (with the total nb of lines).
- Finally, i read again the file to initialize the map with each line, that is malloc with strdup.
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
        free(line);
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
void   alloc_map(t_game *game) // No need to alloc each lines, as i'll do it with strdup for each line i'll read.
{
    game->map = (char **)malloc((game->map_height + 1) * sizeof(char *)); // +1 to add the NULL character.
    if (game->map == NULL)
        return ;
    game->map[game->map_height] = NULL; // To initialize the end of the map (otherwise invalid read of size).
}

// If i malloc line in alloc_map and then strdup (below) each line that i read, it'll create a variable
// that is malloc in a function and then lost, because i malloc again each one with strdup (game->map[i]).
void    fill_tab(const char *file, t_game *game)
{
    int     fd;
    char    *line;
    int     i;

    i = 0;
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        write(1, "Error\n", 6);
        return ;
    }
    while ((line = get_next_line(fd)))
    {
        game->map[i] = ft_strdup(line); // Je malloc chaque ligne donc pas besoin de malloc avant.
        free(line);
        i++;
    }
    close (fd);
}
