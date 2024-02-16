/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:28:45 by jeguerin          #+#    #+#             */
/*   Updated: 2024/02/15 15:44:53 by jeza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_implementation2(t_game *game)
{
	int	result;

	result = map_wall_error(game);
	if (result == 1)
		return (write(1, "Error 4\n", 8), 1);
	result = check_exit(game);
	if (result == 1)
		return (write(1, "Error 3\n", 8), 1);
	result = check_collect(game);
	if (result == 1)
		return (write(1, "Error 2\n", 8), 1);
	result = check_player(game);
	if (result == 1)
		return (write(1, "Error 1\n", 8), 1);
	fill_path_map(game, &game->player, game->ber);
	return (0);
}

int	map_implementation(t_game *game)
{
	int	result;

	result = check_file_error(game);
	if (result == 1)
		return (write(1, "Error 7\n", 8), 1);
	read_map(game->ber, game);
	alloc_map(game);
	fill_tab(game->ber, game);
	result = error_map(game);
	if (result == 1)
		return (write(1, "Error 6\n", 8), 1);
	result = map_shape_error(game);
	if (result == 1)
		return (write(1, "Error 5\n", 8), 1);
	result = map_implementation2(game);
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
	game.ber = ft_strdup(argv[1]);
		// Pass the filename as a command-line argument
	if (game.ber == NULL)
		return (1);
	game.mlx = NULL;
	if (map_implementation(&game) == 0)
		create_window(&game);
	// free(game.ber);
	return (0);
}

/*
TO TEST :
- Map vide.
- Mauvaise map.
- Map avec mauvais nb.
- Map pas rectangle/carré.
- Map pas mur sur l'extérieur.
- Tous les types de fichier.
*/
