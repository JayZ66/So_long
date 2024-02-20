/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:40:12 by jeza              #+#    #+#             */
/*   Updated: 2024/02/20 16:16:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
3 steps :
- First i'm going to read. Need to initialize a var. from the structure if it's not used.
- Then i malloc the array (with the total nb of lines).
- Finally, i read again the file to initialize the map with each line,
	that is malloc with strdup.
*/

void	check_empty_map(const char *file, t_game *game)
{
	int		fd;
	char	c;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		game->map = NULL;
		write(1, "Error fd\n", 9);
		free_everything(game);
	}
	if (read(fd, &c, 1) == 0)
	{
		game->map = NULL;
		write(1, "Error : empty file\n", 19);
		close(fd);
		free_everything(game);
	}
}

void	read_map(const char *file, t_game *game)
{
	int		fd;
	char	*line;

	game->map_height = 0;
	game->map_width = 0;
	check_empty_map(game->ber, game);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		game->map = NULL;
		write(1, "Error fd\n", 9);
		free_everything(game);
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
		write(1, "Error fd\n", 8); // To test.
		free_everything(game);
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
