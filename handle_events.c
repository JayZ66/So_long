/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:17:05 by jeguerin          #+#    #+#             */
/*   Updated: 2024/02/15 19:56:22 by jeza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// hook qui est déclenché lorsqu'il n'y a aucun événement traité.
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
	else if (key == KEY_A) // Left.(Q)
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

// Floodfill :
// Param : Map + position perso du debut.

char	**fill_map_temp(t_game *game, const char *file)
{
	char	**map_temp;
	char	*line;
	int		i;
	int		fd;

	i = 0;
	map_temp = (char **)malloc((game->map_height + 1) * sizeof(char *));
	if (map_temp == NULL)
		return (write(1, "Error\n", 6), NULL);
	map_temp[game->map_height] = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write(1, "Error\n", 6), NULL);
	while ((line = get_next_line(fd)))
	{
		map_temp[i] = ft_strdup(line);
			// Je malloc chaque ligne donc pas besoin de malloc avant.
		free(line);
		i++;
	}
	close(fd);
	return (map_temp);
}

void	fill_path_map(t_game *game, t_player *player, const char *file)
{
	char	**map_temp;
	int		i;

	(void)player;
	i = 0;
	map_temp = fill_map_temp(game, file);
	while (map_temp[i])
	{
		free(map_temp[i]);
		i++;
	}
	free(map_temp);
}

/*
- First, réaliser la vérification en haut :
1. Tu initialises la "new" position (y - 1)
2. Check si sup./égal à 0, si
- Vérification en bas
- Vérification à gauche
- Vérification à droite
*/
void	flood_fill(t_game *game, int x, int y)
{
	map_temp[player->p_pos.y][player->p_pos.x] = 'X';
	// gauche
	if (x > 0 && map_temp[y][x - 1] == '0')
		flood_fill(game, x - 1, y);
	// droite
	if (x <= game->map_width - 1 && map_temp[y][x + 1] == '0')
		flood_fill(game, x + 1, y);
	// monter
	if (y > 0 && map_temp[y - 1][x] == '0')
		flood_fill(game, x, y - 1);
	// Descendre
	if (y <= game->map_width - 1 && map_temp[y + 1][x] == '0')
		flood_fill(game, x, y + 1);
}

void	flood_fill(t_game *game, int x, int y)
{
	char *current;

	current = map_temp[y][x];
	if (x <= 0 || y <= 0 || x > game->map_width || y > game->map_height)
		return ;
	if (current == '1' || current = 'X')
		return ;
	map_temp[y][x] = 'X';
	if (current == 'C')
		game->collect_count--;
	// Mettre du coup X aussi non ?
	if (current == 'E')
		// gauche
		flood_fill(game, x - 1, y);
	// droite
	flood_fill(game, x + 1, y);
	// monter
	flood_fill(game, x, y - 1);
	// Descendre
	flood_fill(game, x, y + 1);
}