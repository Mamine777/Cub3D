/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:15:23 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/22 19:20:33 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

void draw_wall_column(t_game *game, int x, int start_y, int end_y, t_xpm *xpm, float wall_height)
{
    int     y;
    int     texture_x;
    int     texture_y;
    int     color;
    float   step;
    float   texture_pos;
    float   ray_angle;
    float   ray_dist;
    float   world_x, world_y;

    ray_angle = game->player.angle - PI / 6 + (x * PI / 3) / (game->y3d->biggest_width * TILE_SIZE);
    ray_dist = (TILE_SIZE * ((game->y3d->biggest_width * TILE_SIZE) / 2)) / wall_height;
    world_x = game->player.x + cos(ray_angle) * ray_dist;
    world_y = game->player.y + sin(ray_angle) * ray_dist;

    texture_x = ((int)(world_x + world_y) % TILE_SIZE) * xpm->width / TILE_SIZE;

    step = (float)xpm->height / wall_height;
    texture_pos = 0;

    for (y = 0; y < start_y; y++)
        put_pixel(x, y, game->y3d->texture->ceiling_color, game);

    for (y = start_y; y < end_y; y++)
    {
        texture_y = (int)texture_pos % xpm->height;
        color = xpm->colors[texture_y * xpm->width + texture_x];
        put_pixel(x, y, color, game);
        texture_pos += step;
    }
	
    for (y = end_y; y < game->y3d->height * TILE_SIZE; y++)
        put_pixel(x, y, game->y3d->texture->floor_color, game);
}


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
	t_xpm	*xpm;

	xpm = game->xpm;
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
	draw_wall_column(game, i, start_y, end, xpm, height);
	y = end;
	while (y < (data->height * TILE_SIZE))
	{
		put_pixel(i, y, game->y3d->texture->floor_color, game);
		y++;
	}
}

int	draw_loop(t_game *game)
{
	float	 fraction;
	float	 start_x;
	int 	i;
	t_y3d 	*data;

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
