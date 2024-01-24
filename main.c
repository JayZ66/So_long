/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:28:45 by jeguerin          #+#    #+#             */
/*   Updated: 2024/01/24 18:33:49 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//This function will display a colored background.
// The problem with mlx_pixel_put is that it draws the pixel on the window
// But we want to wait for the whole background to be drawn, and then push
// it on the window. + This technique is slow.
void	display_background(t_game *game, int color)
{
	int	i;
	int	j;

	if (game->win == NULL)
		return ;
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			image_pix_put(game, j++, i, color);
		++i;
	}
}

// Shape_height & shape_width = Largeur et hauteur de la forme a afficher.
// x_rect = Coordonnee x (horizontal/colonne) > Part du coin sup. gauche.
// y_rect = Coordonnee y (vertical / ligne) > Part coin sup. gauche.
// x / y sont les coordonnees reelles de la forme.
// First, display_background in order to not overriden the others shapes.
int	render(t_game *game)
{
	if (game->win == NULL)
		return (MLX_ERROR);
	display_background(game, RED);
	game->shape_height = 50;
	game->shape_width = 50;
	game->x_rect = 100;
	game->y_rect = 100;
	display_rect(game);
	game->shape_height = 50;
	game->shape_width = 50;
	game->x_rect = 200;
	game->y_rect = 200;
	display_rect(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image, 0, 0);
	return (0);
}
// The two 0 (coordinates) in the mlx_put_image means that it's covering
// the whole window.

// If the window has been destroyed, we don't want to display pixel.
int	display_rect(t_game *game)
{
	int	i;
	int	j;

	if (game->win == NULL)
		return (1);
	i = game->y_rect;
	game->color = WHITE;
	while (i < game->y_rect + game->shape_height)
	{
		j = game->x_rect;
		while (j < game->x_rect + game->shape_width)
		{
			image_pix_put(game, j, i, game->color);
			j++;
		}
		i++;
	}
	return (0);
}

int	display_pixel(t_game *game)
{
	int	x;

	x = 0;
	if (game->win != NULL)
	{
		while (x != 1080)
		{
			mlx_pixel_put(game->mlx, game->win, x, 100, CYAN);
		// mlx_pixel_put(game->mlx, game->win, 102, 100, WHITE);
		// mlx_pixel_put(game->mlx, game->win, 103, 100, WHITE);
		// mlx_pixel_put(game->mlx, game->win, 104, 100, WHITE);
		// mlx_pixel_put(game->mlx, game->win, 105, 100, WHITE);
		// my_mlx_pixel_put(game, 11, 10, RED);
		// my_mlx_pixel_put(game, 12, 10, RED);
		// my_mlx_pixel_put(game, 13, 10, RED);
		// my_mlx_pixel_put(game, 14, 10, RED);
			x++;
		}
	}
	return (0);
}

// The aim of this function is to create and open a window.
// I'm giving my structure in parameters to get the win var. and set up
// the creation of the window.
// I'm giving a pointer in param. to modify the real value of the var.
// MLX_destroy_win = libération de toutes les ressources allouées pour la
// fenêtre lorsqu'elle n'est plus nécessaire.
// If some errors happen we know that we should return a NULL pointer.

void	create_window(t_game *game)
{
	game->mlx = mlx_init(); // This function creates a struct. all the stuff we'll need in the MLX. Return the address of his struct.
	if (game->mlx == NULL)
		return ;
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
		"So long - Jezabel Guerin");
	if (game->win == NULL)
	{
		free(game->mlx);
		return ;
	}
	create_image(game);
	game->image_add = get_image_add(game);
	// printf("map_height: %d, map_width: %d, y_rect: %d, x_rect: %d\n", game->map_height, game->map_width, game->y_rect, game->x_rect);
	mlx_loop_hook(game->mlx, &handle_no_event, game);
	mlx_loop_hook(game->mlx, &render, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, &manage_keypress, game);
    mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	// mlx_key_hook(game->win, &manage_keypress, game); ..
	mlx_loop(game->mlx); // Waiting for events like keyboard, etc.
	mlx_destroy_image(game->mlx, game->image);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}
// I'm not using a pointer because it's not necessary to work with the real
// value of the var., a copy is used here.

int	main()
{
	t_game	game;

	game.mlx = NULL;
	create_window(&game);
	return (0);
}

