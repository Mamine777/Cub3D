/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:30:59 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/31 18:54:57 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bbp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	init_game(t_game *game, t_y3d *data, t_textures *textrure, t_xpm *xpm)
{
	(void)xpm;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bbp, &game->size_line,
			&game->endian);
	data->game = game;
	data->texture = textrure;
	game->y3d = data;
	init_player(&game->player, data);
}

void	clear_screen(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y, y < HEIGHT)
	{
		x = -1;
		while (++x, x < WIDTH)
		{
			put_pixel(x, y, 0x000000, game);
		}
	}
}
