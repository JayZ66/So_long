/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:17:05 by jeguerin          #+#    #+#             */
/*   Updated: 2024/02/16 18:12:28 by jeza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_no_event(void *game)
{
	(void)game;
	return (0);
}

int	manage_keypress(int key, t_game *game)
{
	if (key == KEY_ESC)
		free_everything(game);
	else if (key == KEY_A)
		move_to_left(&game->player, game);
	else if (key == KEY_D)
		move_to_right(&game->player, game);
	else if (key == KEY_DOWN)
		move_down(&game->player, game);
	else if (key == KEY_LEFT)
		move_to_left(&game->player, game);
	else if (key == KEY_RIGHT)
		move_to_right(&game->player, game);
	else if (key == KEY_UP)
		move_up(&game->player, game);
	else if (key == KEY_S)
		move_down(&game->player, game);
	else if (key == KEY_W)
		move_up(&game->player, game);
	return (0);
}

char	**fill_map_temp(t_game *game, const char *file)
{
	char	**map_temp;
	char	*line;
	int		i;
	int		fd;

	i = 0;
	line = NULL;
	map_temp = (char **)malloc((game->map_height + 1) * sizeof(char *));
	if (map_temp == NULL)
		return (write(1, "Error 9\n", 8), NULL);
	map_temp[game->map_height] = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write(1, "Error 10\n", 9), NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		map_temp[i] = ft_strdup(line);
		free(line);
		i++;
	}
	close(fd);
	return (map_temp);
}

void	fill_path_map(t_game *game, t_player *player, const char *file)
{
	char	**map_temp;
	int		i;

	(void)player;
	i = -1;
	game->check_collect = 0;
	game->check_exit = 0;
	map_temp = fill_map_temp(game, file);
	flood_fill(game, map_temp, player->p_pos.x, player->p_pos.y);
	if (game->check_collect != game->collect_count || game->check_exit == 0)
	{
		write(1, "Error 12\n", 9);
		while (map_temp[++i])
			free(map_temp[i]);
		free(map_temp);
		free_everything(game);
		exit (0);
	}
	while (map_temp[++i])
		free(map_temp[i]);
	free(map_temp);
}

void	flood_fill(t_game *game, char **map, int x, int y)
{
	if (x <= 0 || y <= 0 || x > game->map_width || y > game->map_height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == 'E'
	|| map[y][x] == 'V')
	{
		if (map[y][x] == 'E')
		{
			game->check_exit = 1;
			map[y][x] = 'V';
		}
		return ;
	}
	if (map[y][x] == 'C')
		game->check_collect++;
	if (map[y][x] != 'V')
		map[y][x] = 'X';
	flood_fill(game, map, x - 1, y);
	flood_fill(game, map, x + 1, y);
	flood_fill(game, map, x, y - 1);
	flood_fill(game, map, x, y + 1);
}
