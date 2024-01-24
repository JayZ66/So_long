/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:17:05 by jeguerin          #+#    #+#             */
/*   Updated: 2024/01/24 14:44:11 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_no_event(void *game)
{
	(void)game; // Param. will not be used in this function.
	return (0);
}

int	manage_keypress(int key, t_game *game)
{
	if (key == XK_Escape)
		mlx_destroy_window(game->mlx, game->win);
	return (0);
}
