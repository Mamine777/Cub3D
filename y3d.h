/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:37:26 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/30 17:07:39 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Y3D_H
# define Y3D_H

# include "minilibx-linux/mlx.h"
# include "inc/gnl/get_next_line.h"
# include "inc/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1080
#define EPSILON 0.0001
#define MIN_WALL_DIST 0.1

# define ESC_KEY 65307
# define A 97
# define D 100
# define W 119
# define S 115
# define LEFT 65361
# define RIGHT 65363

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


typedef struct t_xpm
{
	int		width;
	int		height;
	int		*colors;
	void	*img_ptr;
	int		*data;
	int		bbp;
	int		size_line;
	int		endian;
	
}	t_xpm;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	float 			dirX;
	float 			dirY;
	float 			planeX;
    float 			planeY;
	bool			key_up;
	bool			key_down;
	bool			key_left;
	bool			key_right;
	bool			left_rotate;
	bool			right_rotate;
	struct s_y3d	*y3d;
	struct t_xpm	*xpm;

}					t_player;
typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*img_mini;
	void			*no_img;
	char			*data;
	int				bbp;
	int				size_line;
	int				endian;
	struct s_player	player;
	struct s_y3d	*y3d;
	struct t_xpm	*xpm;
}					t_game;

typedef struct t_extra
{
	struct s_game 	*game;
	struct t_xpm	*xpm;
}	t_extra;

typedef struct s_draw_info
{
	t_xpm	*current_texture;
	int		texX;
	double	step;
	double	texPos;
}	t_draw_info;
typedef struct s_ray
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	double	wallX;
	int		tex_x;
	double	step;
	double	texPos;
}				t_ray;


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
void				calculate_texture_position(t_game *game, t_ray *ray, t_draw_info *info);
int 				get_color(t_game *game, t_ray *ray, t_xpm *wall);
t_xpm				*wall_side(t_game *game, t_ray *ray);
void				cleanup_and_exit(t_y3d *y3d, t_xpm *xpm);

// parsing
int					set_texture(int fd, t_textures *texture);
int					init_texture(t_textures *texture, char **av);
int					parse_rgb(int fd, t_textures *texture);
int					set_rgb(char *line, int *color);
bool				check_map_spaces(t_y3d *data);
bool				is_valid_space(t_y3d *data, int x, int y);
bool	init_xpm(t_textures *texture, t_game *game, t_xpm *xpm);
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
void				init_game(t_game *game, t_y3d *data, t_textures *textrure, t_xpm *xpm);
void				init_player(t_player *player, t_y3d *data);
// rendering
void				draw_square(int x, int y, int size, int color,
						t_game *game);
int					key_release(int keycode, t_player *player);
int					key_press(int keycode, t_player *player);
void				move_player(t_player *player, t_y3d *data);
void	draw_game(t_game *game, t_ray *draw, int x);
void	wall_size(t_game *game, t_ray *draw);
int					draw_loop(t_extra *extra);
void				put_pixel(int x, int y, int color, t_game *game);
void 				move_player(t_player *player, t_y3d *data);
void				wall_dist(t_game *game, t_ray *draw, int x);
void 				wall_hit(t_game *game, t_ray *draw);
void				init_ray(t_game *game, t_ray *draw, int x);
void				calcul_ray(t_game *game, t_ray *draw, int x);
void 				move_if_valid(float new_x, float new_y, t_player *player, t_y3d *data);
bool 				can_move_to_position(t_y3d *data, float y, float x);
bool				set_x_y(t_y3d *data, int *x, int *y);


//BONUS

int	minimap(t_game *game);
#endif
