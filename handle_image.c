/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:42:25 by jeguerin          #+#    #+#             */
/*   Updated: 2024/02/15 14:35:03 by jeza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// The aim of this function is to create and open a window.
// I'm giving my structure in parameters to get the win var. and set up
// the creation of the window.
// I'm giving a pointer in param. to modify the real value of the var.
// MLX_destroy_win = libération de toutes les ressources allouées pour la
// fenêtre lorsqu'elle n'est plus nécessaire.
// If some errors happen we know that we should return a NULL pointer.

void	init_imgs(t_game *game)
{
	int	size;
	int	size_end;

	size = 32;
	size_end = 100;
	game->floor = mlx_xpm_file_to_image(game->mlx, "sprites/Floor3.xpm", &size,
			&size);
	game->col = mlx_xpm_file_to_image(game->mlx, "sprites/gay_bag.xpm", &size,
			&size);
	game->wall = mlx_xpm_file_to_image(game->mlx, "sprites/Wall.xpm", &size,
			&size);
	game->player.player = mlx_xpm_file_to_image(game->mlx,
			"sprites/Player1.xpm", &size, &size);
	game->exit = mlx_xpm_file_to_image(game->mlx, "sprites/Floor1.xpm", &size,
			&size);
	game->end = mlx_xpm_file_to_image(game->mlx, "sprites/Winner_win",
			&size_end, &size_end);
}
