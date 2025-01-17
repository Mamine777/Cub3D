/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:37:26 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/16 16:48:23 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Y3D_H
# define Y3D_H

# include "/usr/local/include/mlx.h"
# include "inc/gnl/get_next_line.h"
# include "inc/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TILE_SIZE 48

# define ESC_KEY 53
# define A 0
# define D 2
# define W 13
# define S 1
# define LEFT 123
# define RIGHT 124

# define PI 3.14159265359
typedef struct s_textures
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	bool			no;
	bool			so;
	bool			we;
	bool			ea;
	// colors
	int				floor_color;
	int				ceiling_color;
}					t_textures;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			left_rotate;
	bool			right_rotate;

}					t_player;
typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*img_mini;
	char			*data;
	int				bbp;
	int				size_line;
	int				endian;
	struct s_player	player;
	struct s_y3d	*y3d;
}					t_game;
typedef struct s_y3d
{
	char			**map;
	int				height;
	int				row_width[4024];
	int				biggest_width;
	struct s_game	*game;
	t_textures		*texture;
}					t_y3d;

// utils
void				error(const char *str);
void				couble_free(char **path);
void				init_bool(t_textures *texture);
bool				validate_input(t_y3d *data);

// parsing
int					set_texture(int fd, t_textures *texture);
int					init_texture(t_textures *texture, char **av);
int					parse_rgb(int fd, t_textures *texture);
int					set_rgb(char *line, int *color);
void				cleanup_and_exit(t_textures *texture, char **path,
						char *line, const char *msg);
bool				check_map_spaces(t_y3d *data);
bool				is_valid_space(t_y3d *data, int x, int y);
// clean
void				clean_texture(t_textures *texture);
void				clear_screen(t_game *game);
// init
int					init_map(t_y3d *data, char *file);
int					fill_map_data(int fd, t_y3d *data, char *first_line);
int					count_map_dimensions(int fd, t_y3d *data, char *first_line);
int					skip_config_lines(int fd, char **line);
int					check_map_line(char *line);
int					init_map(t_y3d *data, char *file);
void				init_game(t_game *game, t_y3d *data, t_textures *textrure);
void				init_player(t_player *player, t_y3d *data);
// rendering
void				draw_square(int x, int y, int size, int color,
						t_game *game);
int					key_release(int keycode, t_player *player);
int					key_press(int keycode, t_player *player);
void				move_player(t_player *player, t_y3d *data);
int					draw_loop(t_game *game);
void				put_pixel(int x, int y, int color, t_game *game);
bool				touch(float px, float py, t_y3d *data);
float 				distance(float x, float y);
void				draw_line(t_player *player, t_game *game, float start_x, int i);
float 				fixed_dist(float x1, float y1, float x2, float y2, t_game *game);

//BONUS

int	minimap(t_game *game);
#endif