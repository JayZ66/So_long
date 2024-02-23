/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:19:36 by jeza              #+#    #+#             */
/*   Updated: 2024/02/21 18:02:18 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_shape_error(t_game *game)
{
	int		i;
	size_t	first_line_length;
	size_t	last_line;

	i = 1;
	last_line = 0;
	first_line_length = ft_strlen(game->map[0]);
	while (game->map[i + 1])
	{
		if (ft_strlen(game->map[i]) != first_line_length)
			return (write(1, "Error shape\n", 12), 1);
		i++;
	}
	if (first_line_length != ft_strlen(game->map[i]))
	{
		last_line = ft_strlen(game->map[i]) + 1;
		if (first_line_length != last_line)
			return (write(1, "Error shape\n", 12), 1);
	}
	return (0);
}

int	map_wall_error(t_game *game)
{
	int	theo;

	theo = -1;
	while (game->map[0][++theo])
		if (game->map[0][theo] != '1' && game->map[0][theo] != '\n')
			return (write(1, "Error wall\n", 11), 1);
	theo = -1;
	while (game->map[game->map_height - 1][++theo])
	{
		if (game->map[game->map_height - 1][theo] != '1'
			&& game->map[game->map_height - 1][theo] != '\n')
			return (write(1, "Error wall\n", 11), 1);
	}
	theo = -1;
	while (++theo < game->map_height - 1)
	{
		if (game->map[theo][0] != '1')
			return (write(1, "Error wall\n", 11), 1);
		if (game->map[theo][game->map_width - 1] != '1'
			&& game->map[theo][game->map_width - 1] != '\n'
				&& game->map[theo][game->map_width - 1] != '\0')
			return (write(1, "Error wall\n", 11), 1);
	}
	return (0);
}

int	check_file_error(t_game *game)
{
	int	size_string;
	int	size_ber;
	int	start_position;

	size_string = ft_strlen(game->ber);
	size_ber = ft_strlen(".ber");
	start_position = size_string - size_ber;
	game->map = NULL;
	if (start_position < 0 || ft_strcmp(game->ber + start_position,
			".ber") != 0)
	{
		write(1, "Error file\n", 11);
		return (1);
	}
	return (0);
}
