/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:37:26 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/12 17:29:44 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Y3D_H
# define Y3D_H

# include "/usr/local/include/mlx.h"
# include "inc/gnl/get_next_line.h"
# include "inc/libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

#define WIN_HEIGHT 1280
#define WIN_WIDTH 720

typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	bool		no;
	bool		so;
	bool		we;
	bool		ea;
	// colors
	int			floor_color;
	int			ceiling_color;
}				t_textures;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bbp;
	int			size_line;
	int			endian;
}				t_game;
typedef struct s_y3d
{
	char		**map;
	int			height;
	int			row_width[4024];
	t_game		*game;
	t_textures	*texture;
}				t_y3d;

// utils
void			error(const char *str);
void			couble_free(char **path);
void			init_bool(t_textures *texture);
bool			validate_input(t_y3d *data);

// parsing
int				set_texture(int fd, t_textures *texture);
int				init_texture(t_textures *texture, char **av);
int				parse_rgb(int fd, t_textures *texture);
int				set_rgb(char *line, int *color);
void			cleanup_and_exit(t_textures *texture, char **path, char *line,
					const char *msg);
bool			check_map_spaces(t_y3d *data);
bool			is_valid_space(t_y3d *data, int x, int y);
// clean
void			clean_texture(t_textures *texture);
// init
int				init_map(t_y3d *data, char *file);
int				fill_map_data(int fd, t_y3d *data, char *first_line);
int				count_map_dimensions(int fd, t_y3d *data, char *first_line);
int				skip_config_lines(int fd, char **line);
int				check_map_line(char *line);
int				init_map(t_y3d *data, char *file);
void	init_game(t_game *game, t_y3d *data, t_textures *textrure);
#endif