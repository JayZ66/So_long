/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:32:25 by jeza              #+#    #+#             */
/*   Updated: 2024/02/21 17:24:53 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] != 'E' && game->map[i][j] != 'C'
				&& game->map[i][j] != '1' && game->map[i][j] != '0'
				&& game->map[i][j] != 'P' && game->map[i][j] != '\0')
			{
				return (write(1, "Error nb characters\n", 20), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_exit(t_game *game)
{
	int		i;
	int		j;
	size_t	exit_count;

	i = 0;
	exit_count = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'E')
				exit_count++;
			j++;
		}
		i++;
	}
	if (exit_count != 1)
	{
		write(1, "Error nb exit\n", 14);
		return (1);
	}
	return (0);
}

int	check_collect(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->collect_count = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'C')
				game->collect_count++;
			j++;
		}
		i++;
	}
	if (game->collect_count < 1)
	{
		write(1, "Error nb collect\n", 17);
		return (1);
	}
	return (0);
}

int	check_player(t_game *game)
{
	int		i;
	int		j;
	size_t	player_count;

	i = 0;
	player_count = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'P')
			{
				game->player.p_pos.x = j;
				game->player.p_pos.y = i;
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (write(1, "Error nb player\n", 16), 1);
	return (0);
}
