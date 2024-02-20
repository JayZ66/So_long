/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:19:36 by jeza              #+#    #+#             */
/*   Updated: 2024/02/20 16:30:17 by marvin           ###   ########.fr       */
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
			return(write(1, "Error shape\n", 12), 1);
		i++;
	}
	if (first_line_length != ft_strlen(game->map[i]))
	{
		last_line = ft_strlen(game->map[i]) + 1;
		if (first_line_length != last_line)
			return(write(1, "Error shape\n", 12), 1);
	}
	return (0);
}

int	map_wall_error(t_game *game) // ASK CYRIL !!!! + Check si met bien /0 quand lis ?? Pq /n et /0 alors que strdup mais des /0 ??
{
	int	theo;

	theo = -1;
	while (game->map[0][++theo])
	{
		if (game->map[0][theo] != '1' && game->map[0][theo] != '\n')
			return (write(1, "Error wall\n", 11), 1);
	}
	theo = -1;
	while (game->map[game->map_height - 1][++theo])
	{
		if (game->map[game->map_height - 1][theo] != '1')
			return (write(1, "Error wall\n", 11), 1);
	}
	theo = -1;
	while (++theo < game->map_height - 1)
	{
		if (game->map[theo][0] != '1' && (game->map[theo][game->map_width] != '1' 
			&& game->map[theo][game->map_width] != '\n'))
			return (write(1, "Error wall\n", 11), 1);
	}
	return (0);
}

// int	map_wall_error(t_game *game) // ASK CYRIL !!!! + Check si met bien /0 quand lis ?? Pq /n et /0 alors que strdup mais des /0 ??
// {
// 	int	theo;

// 	theo = -1;
// 	while (game->map[0][++theo])
// 	{
// 		if (game->map[0][theo] != '1' && game->map[0][theo] != 13)
// 			return (write(1, "Error wall\n", 11), 1);
// 	}
// 	theo = -1;
// 	while (game->map[game->map_height - 1][++theo])
// 	{
// 		if (game->map[game->map_height - 1][theo] != '1' 
// 			&& game->map[game->map_height - 1][theo] != '\0')
// 			return (write(1, "Error wall\n", 11), 1);
// 	}
// 	theo = -1;
// 	while (++theo < game->map_height - 1)
// 	{
// 		if (game->map[theo][0] != '1' && game->map[theo][0] != 13)
// 			return (write(1, "Error wall\n", 11), 1);
// 	}
// 	theo = -1;
// 	while (++theo < game->map_height - 1)
// 	{
// 		if (game->map[theo][game->map_width] != '1' && game->map[theo][game->map_width] != '\0' 
// 			&& game->map[theo][game->map_width] != '\n')
// 			return (write(1, "Error wall\n", 11), 1);
// 	}
// 	return (0);
// }


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
