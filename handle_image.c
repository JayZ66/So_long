/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeza <jeza@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:42:25 by jeguerin          #+#    #+#             */
/*   Updated: 2024/01/26 17:13:55 by jeza             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Pix_add = Calculate the memory address to write the pixel to pix_add.
// Last line = Write the color to the calculated memory address.
// This function obtain the memory add. of the pixel in the image.
void	image_pix_put(t_game *game, int x, int y, int color)
{
	char	*pix_add;

	pix_add = game->image_add + (y * game->size_line + x *
		(game->bits_per_pixel / 8));
	*(int *)pix_add = color;
}

// Now that we have an image, how can we write pixels inside ?
// For that, we must obtain the memory adress, where we'll send the octet.
// bpp = Quantity of bytes in a pixel.
// size_line = Quantity of octets get by a line of our image.
// To get this adress :
char	*get_image_add(t_game *game)
{
	game->image_add = mlx_get_data_addr(game->image, &game->bits_per_pixel,
		&game->size_line, &game->endian);
	return (game->image_add);
}
// We do : &game->endian to get the adress of the value of this var. as is var.
// is a value & not a pointer.

// In order to display an image, we should use mlx_pixel_put
// to push each pixel, one by one, but we can't do it.
// So we'll put our pixels in an image in memory, & then push the image.
void	create_image(t_game *game)
{
	game->image = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (game->image == NULL)
    {
        mlx_destroy_window(game->mlx, game->win);
        free(game->mlx);
        return ;
    }
}
