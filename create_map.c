/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:40:12 by jeza              #+#    #+#             */
/*   Updated: 2024/02/16 13:14:38 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
3 steps :
- First i'm going to read.
- Then i malloc the array (with the total nb of lines).
- Finally, i read again the file to initialize the map with each line,
	that is malloc with strdup.
*/

void	read_map(const char *file, t_game *game)
{
	int		fd;
	char	*line;

	game->map_height = 0;
	game->map_width = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(1, "Error\n", 6);
		return ;
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (game->map_height == 0)
			game->map_width = ft_strlen(line) - 1;
		game->map_height++;
		free(line);
	}
	close(fd);
}

void	alloc_map(t_game *game)
{
	game->map = (char **)malloc((game->map_height + 1) * sizeof(char *));
	if (game->map == NULL)
		return ;
	game->map[game->map_height] = NULL;
}

void	fill_tab(const char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(1, "Error\n", 6);
		return ;
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		game->map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	close(fd);
}
