/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:30:59 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/17 14:35:33 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= game->y3d->biggest_width * TILE_SIZE || y >= game->y3d->height
		* TILE_SIZE || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bbp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, game);
}
void	init_game(t_game *game, t_y3d *data, t_textures *textrure)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, data->biggest_width * TILE_SIZE,
			data->height * TILE_SIZE, "cub3D");
	game->img = mlx_new_image(game->mlx, data->biggest_width * TILE_SIZE,
			data->height * TILE_SIZE);
	game->data = mlx_get_data_addr(game->img, &game->bbp, &game->size_line,
			&game->endian);
	data->game = game;
	data->texture = textrure;
	game->y3d = data;
	init_player(&game->player, data);
}

void	clear_screen(t_game *game)
{
	for (int y = 0; y < game->y3d->height * TILE_SIZE; y++)
	{
		for (int x = 0; x < game->y3d->biggest_width * TILE_SIZE; x++)
		{
			put_pixel(x, y, 0x000000, game);
		}
	}
}

void	draw_map(t_game *game)
{
	int	color;

	color = 0x0000FF;
	for (int y = 0; game->y3d->map[y]; y++)
		for (int x = 0; game->y3d->map[y][x]; x++)
			if (game->y3d->map[y][x] == '1')
				draw_square(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, color,
					game);
}

