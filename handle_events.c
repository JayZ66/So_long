/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:17:05 by jeguerin          #+#    #+#             */
/*   Updated: 2024/02/13 09:10:26 by jeza             ###   ########.fr       */
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
	else if (key == KEY_A) //Left.(Q)
		move_to_left(&game->player, game);
	else if (key == KEY_D) // Right (D)
		move_to_right(&game->player, game);
	else if (key == KEY_DOWN)
		move_down(&game->player, game);
	else if (key == KEY_LEFT)
		move_to_left(&game->player, game);
	else if (key == KEY_RIGHT)
		move_to_right(&game->player, game);
	else if (key == KEY_UP)
		move_up(&game->player, game);
	else if (key == KEY_S) // Back (S)
		move_down(&game->player, game);
	else if (key == KEY_W) // Acancer (Z)
		move_up(&game->player, game);
	return (0);
}
