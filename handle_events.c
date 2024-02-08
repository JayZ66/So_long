/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:17:05 by jeguerin          #+#    #+#             */
/*   Updated: 2024/02/07 15:25:18 by jeza             ###   ########.fr       */
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
		free_everything(game);
	// else if (key == KEY_A)
	// else if (key == KEY_D)
	// else if (key == KEY_DOWN)
	// else if (key == KEY_LEFT)
	// else if (key == KEY_RIGHT)
	// else if (key == KEY_S)
	// else if (key == KEY_UP)
	// else if (key == KEY_W)
	return (0);
}

int	free_everything(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
    {
    	free(game->map[i]);
        i++;
    }
    free(game->map);
	// free(game->floor);
	// free(game->col);
	// free(game->wall);
	mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	return (0);
}

// In order to be able to read which key is released.
// Called each time a keypress is released.
// int	handle_keyrelease(int keysym, void *game)
// {
// 	(void)game;
// 	printf("KeyRelease: %d\n", keysym);
// 	return (0);
// }
// This function will check which keyboard key is pressed and then
// will do what's appropriate. ==> So add the others.
