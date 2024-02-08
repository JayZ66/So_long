/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:28:45 by jeguerin          #+#    #+#             */
/*   Updated: 2024/02/08 14:31:41 by jeza             ###   ########.fr       */
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

void	init_imgs(t_game *game)
{
	int	size;

	size = 32;
	game->floor = mlx_xpm_file_to_image(game->mlx, "sprites/Floor3.xpm", &size, &size);
	game->col = mlx_xpm_file_to_image(game->mlx, "sprites/gay_bag.xpm", &size, &size);
	game->wall = mlx_xpm_file_to_image(game->mlx, "sprites/Wall.xpm", &size, &size);
	game->player.player = mlx_xpm_file_to_image(game->mlx, "sprites/Player1.xpm", &size, &size);
	// game->exit
}

void	fill_window(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(game->map[i])
	{
		j = 0;
		while(game->map[i][j])
		{
			if (game->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->floor, j * 32, i * 32);
			else if (game->map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->col, j * 32, i * 32);
			else if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall, j * 32, i * 32);
			else if (game->map[i][j] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->player.player, j * 32, i * 32);
			j++;
		}
		i++;
	}
}

void	create_window(t_game *game)
{
	game->mlx = mlx_init(); // This function creates a struct. all the stuff we'll need in the MLX. Return the address of his struct.
	if (game->mlx == NULL)
		return ;
	game->win = mlx_new_window(game->mlx, game->map_width * 32, game->map_height * 32,
		"So long - Jezabel Guerin");
	if (game->win == NULL)
	{
		free(game->mlx);
		return ;
	}
	init_imgs(game);
	fill_window(game);
	//game->image_add = get_image_add(game);
	// mlx_loop_hook(game->mlx, &render, game);
	mlx_loop_hook(game->mlx, &handle_no_event, game); // Needed to properly close the win. + To manage ennemies mooves.
	mlx_hook(game->win, KeyPress, KeyPressMask, &manage_keypress, game); // Use it just once to manage all keypress.
	mlx_hook(game->win, 17, KeyPressMask, &free_everything, game);
    // mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	// mlx_key_hook(game->win, &manage_keypress, game);
	mlx_loop(game->mlx); // Waiting for events like keyboard, etc.
	// mlx_destroy_image(game->mlx, game->image);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}


int	map_implementation(t_game *game)
{
	int	result;

	read_map(game->ber, game);
	alloc_map(game);
	fill_tab(game->ber, game);
	result = map_shape_error(game);
	if (result == 1)
	{
		write(1, "Error map shape\n", 16);
		return (1);
	}
	result = map_wall_error(game);
	if (result == 1)
	{
		write(1, "Error wall\n", 11);
		return (1);
	}
	result = check_exit(game);
	if (result == 1)
	{
		write(1, "Error exit\n", 11);
		return (1);
	}
	result = check_collect(game);
	if (result == 1)
	{
		write(1, "Error collect\n", 14);
		return (1);
	}
	result = check_player(game);
	if (result == 1)
	{
		write(1, "Error player\n", 13);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		 write(1, "Error\n", 6);
		 return (1);
	}
	game.ber = (char *)malloc((ft_strlen(argv[1])) * sizeof(char));
	if (game.ber == NULL) // Malloc with the size of av[1].
		return (1);
	game.ber = ft_strdup(argv[1]);  // Pass the filename as a command-line argument
	game.mlx = NULL;
	if (map_implementation(&game) == 0)
		create_window(&game);
	free(game.ber);
	return (0);
}