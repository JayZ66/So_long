/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:17:05 by jeguerin          #+#    #+#             */
/*   Updated: 2024/02/16 13:45:15 by jeguerin         ###   ########.fr       */
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
		return (write(1, "Error\n", 6), NULL);
	map_temp[game->map_height] = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write(1, "Error\n", 6), NULL);
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
	i = 0;
	map_temp = fill_map_temp(game, file);
	while (map_temp[i])
	{
		free(map_temp[i]);
		i++;
	}
	free(map_temp);
}

// void	flood_fill(t_game *game, int x, int y)
// {
// 	map_temp[player->p_pos.y][player->p_pos.x] = 'X';
// 	if (x > 0 && map_temp[y][x - 1] == '0')
// 		flood_fill(game, x - 1, y);
// 	if (x <= game->map_width - 1 && map_temp[y][x + 1] == '0')
// 		flood_fill(game, x + 1, y);
// 	if (y > 0 && map_temp[y - 1][x] == '0')
// 		flood_fill(game, x, y - 1);
// 	if (y <= game->map_width - 1 && map_temp[y + 1][x] == '0')
// 		flood_fill(game, x, y + 1);
// }

// void	flood_fill(t_game *game, int x, int y)
// {
// 	char	*current;

// 	current = map_temp[y][x];
// 	if (x <= 0 || y <= 0 || x > game->map_width || y > game->map_height)
// 		return ;
// 	if (current == '1' || current == 'X')
// 		return ;
// 	map_temp[y][x] = 'X';
// 	if (current == 'C')
// 		game->collect_count--;
// 	// if (current == 'E')
// 	flood_fill(game, x - 1, y);
// 	flood_fill(game, x + 1, y);
// 	flood_fill(game, x, y - 1);
// 	flood_fill(game, x, y + 1);
// }
