/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:36:03 by jeza              #+#    #+#             */
/*   Updated: 2024/02/16 15:09:54 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_window(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->floor, j
					* 32, i * 32);
			else if (game->map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->col, j * 32,
					i * 32);
			else if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall, j
					* 32, i * 32);
			else if (game->map[i][j] == 'P')
				mlx_put_image_to_window(game->mlx, game->win,
					game->player.player, j * 32, i * 32);
			else if (game->map[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit, j
					* 32, i * 32);
			j++;
		}
		i++;
	}
}

void	create_window(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return ;
	game->win = mlx_new_window(game->mlx, game->map_width * 32, game->map_height
			* 32, "So long - Jezabel Guerin");
	if (game->win == NULL)
	{
		free(game->mlx);
		return ;
	}
	game->step_count = 0;
	init_imgs(game);
	fill_window(game);
	mlx_hook(game->win, KeyPress, KeyPressMask, &manage_keypress, game);
	mlx_hook(game->win, 17, KeyPressMask, &free_everything, game);
	mlx_loop(game->mlx);
}
