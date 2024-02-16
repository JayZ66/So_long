/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:19:52 by jeza              #+#    #+#             */
/*   Updated: 2024/02/15 14:44:34 by jeza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i]
		&& ((unsigned char)s1[i] == (unsigned char)s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	free_everything(t_game *game)
{
	int i;

	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	free(game->ber);
	if (game->floor)                              
		// Each time check if the var. is activated.
		mlx_destroy_image(game->mlx, game->floor);
			// Use this function to free each image.
	if (game->col)
		mlx_destroy_image(game->mlx, game->col);
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->player.player)
		mlx_destroy_image(game->mlx, game->player.player);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->end)
		mlx_destroy_image(game->mlx, game->end);
	if (game->win != NULL)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx != NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit(0);
	}
	return (0);
}