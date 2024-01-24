/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:48:48 by jeguerin          #+#    #+#             */
/*   Updated: 2024/01/24 18:30:41 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <limits.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "get_next_line/get_next_line.h"
# include "minilibx/mlx.h"

# define MLX_ERROR 1
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# define BLACK 0 << 16 | 0 << 8 | 0
# define RED 255 << 16 | 0 << 8 | 0
# define GREEN 0 << 16 | 255 << 8 | 0
# define WHITE 255 << 16 | 255 << 8 | 255
# define BLUE 0 << 16 | 0 << 8 | 255
# define YELLOW 255 << 16 | 255 << 8 | 0
# define MAGENTA 255 << 16 | 0 << 8 | 255
# define CYAN 0 << 16 | 255 << 8 | 255
// # define BLACK 0xFF000000
// # define RED 0xFFFF0000
// # define GREEN 0xFF00FF00
// # define BLUE 0xFF0000FF
// # define WHITE 0xFFFFFFFF

// typedef struct	s_img {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_img;
// Revoir le code (a adapter) pour creer cette sous-structure.

typedef struct s_game
{
	void	*mlx; // Pointeur vers l'instance MLX.
	void	*win; // Pointeur vers la fenetre.
	int		shape_width; // Largeur de la forme a afficher.
	int		shape_height; // Hauteur de la map.
	char	**map; // Tableau bidimensionnel representant la map.
	int		player_pos_x; // Position X du joueur sur la carte.
	int		player_pos_y; // Position Y du joueur sur la carte.
	void	*player;
	void	*exit;
	void	*collectable;
	int		x_event;
	int		x_mask;
	char	*string; // Text to write on the window.
	char	*title_win; // Le titre de la fenetre.
	int		x_rect;
	int		y_rect;
	void	*image; // Un pointeur vers l'image dont on veut obtenir l'add. mem.
	char	*relative_path; // Pour verifier le fichier xpm.
	char	*image_add;
	int		bits_per_pixel; // Un pointeur vers un entier qui sera rempli par
//la fonction avec le nb de bits necessaires pour representer un pixel dans
// l'image. Cela indique le nb de bits used to stocker la color de chq pixel.
	int		size_line; // Un pointeur vers un entier qui sera rempli par la
// fonction avec la taille d'une ligne de l'image en octets. Indique cb d'octets
// sont necessaires pour stoker une ligne complete de pixels. Elle differe de
// largeur reelle de la fenetre.
	int		endian; // Un pointeur vers un entier qui sera rempli par la
// fonction avec l'endian de la machine (0 ou 1). Indique comment les octets
// sont stockes dans la memoire.
	int		color;
}	t_game;


int	main();
void	create_window(t_game *game);
void	create_image(t_game *game);
char	*get_image_add(t_game *game);
void	image_pix_put(t_game *game, int x, int y, int color);
int		display_pixel(t_game *game);
int		manage_keypress(int key, t_game *game);
int		display_rect(t_game *game);
// int	render(t_game *game);
int		render(t_game *game);
void	display_background(t_game *game, int color);
int		handle_no_event(void *game);
int		handle_keyrelease(int key, void *data);

#endif

/*
L'endianness, ou "endianisme" en français, est l'ordre dans lequel les octets
individuels d'un mot binaire sont stockés en mémoire.
Il y en a 2 types :
- Big-endian (0) : octets de poids fort (bits les + significatifs) sont stockes
a l'add memoire la plus basse.
- Little-endian (1) : octets de poids faible (bits les - significatifs), sont
stockes a des add. memoire plus elevees.
*/
