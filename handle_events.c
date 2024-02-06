/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:17:05 by jeguerin          #+#    #+#             */
/*   Updated: 2024/01/26 17:13:18 by jeza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//hook qui est déclenché lorsqu'il n'y a aucun événement traité.
// Il est particulièrement utile pour dessiner continuellement des choses à
// l'écran, même si nous n'en avions pas vraiment besoin dans notre exemple.
int	handle_no_event(void *game)
{
	(void)game; // Param. will not be used in this function.
	return (0);
}

// Called each time a keypress is pressed.
// When i'm calling mlx_destroy, i free ressources linked to the window but
// there is no garanty that the var. is null. And if i'm trying to access it,
// it'll create the error "BadDrawable"
int	manage_keypress(int key, t_game *game)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	printf("KeyPress: %d\n", key);
	return (0);
}

// In order to be able to read which key is released.
// Called each time a keypress is released.
int	handle_keyrelease(int keysym, void *game)
{
	(void)game;
	printf("KeyRelease: %d\n", keysym);
	return (0);
}
// This function will check which keyboard key is pressed and then
// will do what's appropriate. ==> So add the others.
