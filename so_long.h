/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:48:48 by jeguerin          #+#    #+#             */
/*   Updated: 2024/02/16 14:56:47 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define MLX_ERROR 1
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define SZ 32
# define ON_DESTROY 17

# define BLACK 0xFF000000
# define RED 0xFFFF0000
# define GREEN 0xFF00FF00
# define BLUE 0xFF0000FF
# define WHITE 0xFFFFFFFF

typedef struct s_axe
{
	int			x;
	int			y;
}				t_axe;

typedef struct s_player
{
	void		*player;
	t_axe		p_pos;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	void		*exit;
	char		*string;
	int			x_rect;
	int			y_rect;
	void		*image;
	int			color;
	int			map_height;
	int			map_width;
	char		*ber;
	void		*floor;
	void		*col;
	void		*wall;
	void		*end;
	size_t		collect_count;
	size_t		step_count;
	t_player	player;
}				t_game;

// Creation map.
int				alloc_tab(t_game *game);
int				map_implementation(t_game *game);
int				map_implementation2(t_game *game);
void			read_map(const char *file, t_game *game);
void			alloc_map(t_game *game);
void			fill_tab(const char *file, t_game *game);

// Create images & win.
void			create_window(t_game *game);
void			init_imgs(t_game *game);

// Manage events.
int				handle_no_event(void *game);
int				manage_keypress(int key, t_game *game);

// Check map.
int				check_exit(t_game *game);
int				check_collect(t_game *game);
int				check_player(t_game *game);
int				map_shape_error(t_game *game);
int				map_wall_error(t_game *game);
int				error_map(t_game *game);
char			**fill_map_temp(t_game *game, const char *file);
void			fill_path_map(t_game *game, t_player *player, const char *file);

// Manage moves & player.
void			move_to_left(t_player *player, t_game *game);
void			move_to_right(t_player *player, t_game *game);
void			move_up(t_player *player, t_game *game);
void			move_down(t_player *player, t_game *game);
void			check_path(int x, int y, t_game *game, t_player *player);
void			handle_end_of_game(int x, int y, t_game *game);
void			display_steps(int x, int y, t_game *game);

// Utils.
int				ft_strcmp(const char *s1, const char *s2);
int				free_everything(t_game *game);
int				check_file_error(t_game *game);
void			free_image(t_game *game);

#endif
