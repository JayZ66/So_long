/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:19:36 by jeza              #+#    #+#             */
/*   Updated: 2024/02/16 11:07:00 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_shape_error(t_game *game)
{
	int		i;
	size_t	first_line_length;

	i = 0;
	first_line_length = ft_strlen(game->map[0]);
	while (game->map[i])
	{
		if (ft_strlen(game->map[i]) != first_line_length)
		{
			write(1, "Error\n", 6);
			return (1);
		}
		i++;
	}
	return (0);
}

int	map_wall_error(t_game *game)
{
	int	theo;

	theo = -1;
	while (game->map[0][++theo])
		if (game->map[0][theo] != '1')
			return (1);
	theo = -1;
	while (game->map[game->map_height - 1][++theo])
		if (game->map[game->map_height - 1][theo] != '1')
			return (1);
	theo = -1;
	while (game->map[++theo])
		if (game->map[theo][0] != '1'
			|| (game->map[theo][game->map_width] != '1'
				&& game->map[theo][game->map_width] != '\0'))
			return (1);
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
	if (start_position < 0 || ft_strcmp(game->ber + start_position,
			".ber") != 0)
	{
		write(1, "Error file\n", 11);
		return (1);
	}
	return (0);
}
