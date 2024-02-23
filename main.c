/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:28:45 by jeguerin          #+#    #+#             */
/*   Updated: 2024/02/21 17:28:17 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*

clear
make
./so_long map/fichier_qui_exite_pas.pasber > OK
./so_long map/empty_map.ber => OK
./so_long map/map_mult_player.ber => OK
./so_long map/map_no_collect.ber => OK
./so_long map/map_no_exit.ber => OK
./so_long map/map_no_player.ber => OK
./so_long map/map_not_closed.ber => OK
./so_long map/wrong_path.ber => OK
./so_long map/wrong_car.ber => OK

./so_long map/colums.ber
./so_long map/map.ber


valgrind ./so_long map/fichier_qui_exite_pas.pasber
valgrind ./so_long map/empty_map.ber
valgrind ./so_long map/map_mult_player.ber
valgrind ./so_long map/map_no_collect.ber
valgrind ./so_long map/map_no_exit.ber
valgrind ./so_long map/map_no_player.ber
valgrind ./so_long map/map_not_closed.ber
valgrind ./so_long map/wrong_path.ber
valgrind ./so_long map/wrong_car.ber

*/

int	map_implementation2(t_game *game)
{
	int	result;

	result = check_exit(game);
	if (result == 1)
		return (write(1, "Error exit\n", 11), 1);
	result = check_collect(game);
	if (result == 1)
		return (write(1, "Error collect\n", 14), 1);
	result = check_player(game);
	if (result == 1)
		return (write(1, "Error player\n", 13), 1);
	result = error_map(game);
	if (result == 1)
		return (write(1, "Error car. map\n", 15), 1);
	fill_path_map(game, &game->player, game->ber);
	return (0);
}

int	map_implementation(t_game *game)
{
	int	result;

	result = check_file_error(game);
	if (result == 1)
		return (write(1, "Error file\n", 11), 1);
	read_map(game->ber, game);
	alloc_map(game);
	fill_tab(game->ber, game);
	result = map_wall_error(game);
	if (result == 1)
		return (write(1, "Error wall\n", 11), 1);
	result = map_shape_error(game);
	if (result == 1)
		return (write(1, "Error shape\n", 12), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (write(1, "Error args\n", 11), 1);
	game.ber = ft_strdup(argv[1]);
	if (game.ber == NULL)
		return (1);
	game.mlx = mlx_init();
	mlx_loop(game.mlx);
	game.win = NULL;
	init_imgs(&game);
	if (map_implementation(&game) == 1 || map_implementation2(&game) == 1)
		free_everything(&game);
	create_window(&game);
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

// Pas bon car erreur wall qd no exit.
// qd pas les bons caractères
// quand wrong_path
// Map vide. (segfault)
