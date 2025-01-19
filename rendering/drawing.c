/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:15:23 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/18 18:45:05 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"


float distance(float x, float y)
{
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - game->player.angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}
void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;
	t_y3d	*data;
	float	dist;
	float	height;
	int		start_y;
	int		end;
	int		y;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->x;
	ray_y = player->y;
	data = game->y3d;
	while (!touch(ray_x, ray_y, data))
	{
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	height = (TILE_SIZE / dist) * ((data->biggest_width * TILE_SIZE) / 2);
	start_y = ((data->height * TILE_SIZE) - height) / 2;
	end = start_y + height;
	y = -1;
	while (++y, y < start_y)
	{
		put_pixel(i, y, game->y3d->texture->ceiling_color, game);
	}
	while (start_y < end)
	{
		put_pixel(i, start_y, 0xFFFFFF, game);
		start_y++;
	}
	y = end;
	while (y < (data->height * TILE_SIZE))
	{
		put_pixel(i, y, game->y3d->texture->floor_color, game);
		y++;
	}
}

int	draw_loop(t_game *game)
{
	float fraction;
	float start_x;
	int i;
	t_y3d *data;

	data = game->y3d;
	(void) data;
	clear_screen(game);
	move_player(&game->player, game->y3d);
	fraction = PI / 3 / (game->y3d->biggest_width * TILE_SIZE);
	start_x = game->player.angle - PI / 6;
	i = 0;
	while (i < (game->y3d->biggest_width * TILE_SIZE))
	{
		draw_line(&game->player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}