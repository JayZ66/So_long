/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:08:30 by jeguerin          #+#    #+#             */
/*   Updated: 2024/02/16 19:21:56 by jeza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_down(t_player *player, t_game *game)
{
	int	pos_x_temp;
	int	pos_y_temp;

	pos_x_temp = player->p_pos.x;
	pos_y_temp = player->p_pos.y;
	pos_y_temp++;
	 // pas mur tu incrémentes. + string à déplacer vers la gauche
	if (pos_x_temp >= 0 && pos_x_temp < game->map_width && pos_y_temp >= 0
		&& pos_y_temp < game->map_height)
	{
		if (game->map[pos_y_temp][pos_x_temp] != 1)
			game->step_count++;
		check_path(pos_x_temp, pos_y_temp, game, player);
	}
}

void	move_up(t_player *player, t_game *game)
{
	int	pos_x_temp;
	int	pos_y_temp;

	pos_x_temp = player->p_pos.x;
	pos_y_temp = player->p_pos.y;
	pos_y_temp--;
	if (pos_x_temp >= 0 && pos_x_temp < game->map_width && pos_y_temp >= 0
		&& pos_y_temp < game->map_height)
	{
		if (game->map[pos_y_temp][pos_x_temp] != 1)
			game->step_count++;
		check_path(pos_x_temp, pos_y_temp, game, player);
	}
}

void	move_to_left(t_player *player, t_game *game)
{
	int	pos_x_temp;
	int	pos_y_temp;

	pos_x_temp = player->p_pos.x;
	pos_y_temp = player->p_pos.y;
	pos_x_temp--;
	if (pos_x_temp >= 0 && pos_x_temp < game->map_width && pos_y_temp >= 0
		&& pos_y_temp < game->map_height)
	{
		if (game->map[pos_y_temp][pos_x_temp] != 1)
			game->step_count++;
		check_path(pos_x_temp, pos_y_temp, game, player);
	}
}

void	move_to_right(t_player *player, t_game *game)
{
	int	pos_x_temp;
	int	pos_y_temp;

	pos_x_temp = player->p_pos.x;
	pos_y_temp = player->p_pos.y;
	pos_x_temp++;
	if (pos_x_temp >= 0 && pos_x_temp < game->map_width && pos_y_temp >= 0
		&& pos_y_temp < game->map_height)
	{
		if (game->map[pos_y_temp][pos_x_temp] != 1)
			game->step_count++;
		check_path(pos_x_temp, pos_y_temp, game, player);
	}
}
