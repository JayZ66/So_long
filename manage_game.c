/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:52:44 by jeza              #+#    #+#             */
/*   Updated: 2024/02/20 16:22:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_end_of_game(int x, int y, t_game *game)
{
	if (game->map[y][x] == 'E' && game->collect_count == 0)
		free_everything(game);
}

void	check_path(int x, int y, t_game *game, t_player *player)
{
	if (game->map[y][x] == 'C')
	{
		game->collect_count--;
		mlx_put_image_to_window(game->mlx, game->win, game->floor,
			player->p_pos.x * 32, player->p_pos.y * 32);
		game->map[y][x] = 0;
	}
	handle_end_of_game(x, y, game);
	if (game->map[y][x] != '1' && game->map[y][x] != 'E')
	{
		mlx_put_image_to_window(game->mlx, game->win, game->floor,
			player->p_pos.x * 32, player->p_pos.y * 32);
		player->p_pos.x = x;
		player->p_pos.y = y;
		mlx_put_image_to_window(game->mlx, game->win, player->player,
			player->p_pos.x * 32, player->p_pos.y * 32);
		game->step_count++;
	}
	display_steps(x, y, game);
	if (game->string)
	{
		free(game->string);
		game->string = NULL;
	}
}

void	display_steps(int x, int y, t_game *game)
{
	game->string = ft_itoa(game->step_count);
	if (game->map[y][x] != 'E')
	{
		mlx_put_image_to_window(game->mlx, game->win, game->wall, 95, 0);
		mlx_string_put(game->mlx, game->win, 10, 15, WHITE, "Nombre de pas: ");
		mlx_string_put(game->mlx, game->win, 100, 15, WHITE, game->string);
	}
}
