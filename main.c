/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:28:45 by jeguerin          #+#    #+#             */
/*   Updated: 2024/02/13 09:06:31 by jeza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


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
			else if (game->map[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit, j * 32, i * 32);
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
	game->step_count = 0;
	init_imgs(game);
	fill_window(game);
	mlx_loop_hook(game->mlx, &handle_no_event, game); // Needed to properly close the win. + To manage ennemies mooves.
	mlx_hook(game->win, KeyPress, KeyPressMask, &manage_keypress, game); // Use it just once to manage all keypress.
	mlx_hook(game->win, 17, KeyPressMask, &free_everything, game);
	mlx_loop(game->mlx); // Waiting for events like keyboard, etc.
    // mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	// mlx_key_hook(game->win, &manage_keypress, game);
	// mlx_destroy_image(game->mlx, game->image);
	// mlx_destroy_window(game->mlx, game->win);
	// game->win = NULL;
	// mlx_destroy_display(game->mlx);
	if (game->mlx != NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}


int	map_implementation(t_game *game)
{
	int	result;

	read_map(game->ber, game);
	alloc_map(game);
	fill_tab(game->ber, game);
	result = error_map(game);
	if (result == 1)
	{
		write(1, "Error 6\n", 8);
		return (1);
	}
	result = map_shape_error(game);
	if (result == 1)
	{
		write(1, "Error 5\n", 8);
		return (1);
	}
	result = map_wall_error(game);
	if (result == 1)
	{
		write(1, "Error 4\n", 8);
		return (1);
	}
	result = check_exit(game);
	if (result == 1)
	{
		write(1, "Error 3\n", 8);
		return (1);
	}
	result = check_collect(game);
	if (result == 1)
	{
		write(1, "Error 2\n", 8);
		return (1);
	}
	result = check_player(game);
	if (result == 1)
	{
		write(1, "Error 1\n", 8);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	// if (game == NULL)
	// 	return (1);
	if (argc != 2)
	{
		 write(1, "Error\n", 6);
		 return (1);
	}
	game.ber = ft_strdup(argv[1]);  // Pass the filename as a command-line argument
	if (game.ber == NULL)
    	return (1);
	game.mlx = NULL;
	if (map_implementation(&game) == 0)
		create_window(&game);
	// final_free_mlx(&game); // POURQUOI lorsque je free tout dans everything j'ai segfault alors que c'est via echap ?
	// // PQ je dois free display et mlx en dehors (donc dans mon main) ??
	free(game.ber);
	return (0);
}

