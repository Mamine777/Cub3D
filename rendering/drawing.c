/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:15:23 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/29 20:53:14 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"


/* float distance(float x, float y)
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

    ray_angle = game->player.angle - PI / 6 + (x * PI / 3) / (game->y3d->biggest_width * TILE_SIZE - 1);
    ray_dist = (TILE_SIZE * ((game->y3d->biggest_width * TILE_SIZE) / 2)) / wall_height;
    world_x = game->player.x + cos(ray_angle) * ray_dist;
    world_y = game->player.y + sin(ray_angle) * ray_dist;

    texture_x = ((int)(world_x + world_y) % TILE_SIZE) * xpm->width / TILE_SIZE;

    step = (float)xpm->height / wall_height;
    texture_pos = 0;

    for (y = start_y; y < end_y; y++)
    {
        texture_y = (int)texture_pos % xpm->height;
        color = xpm->colors[texture_y * xpm->width + texture_x];
        put_pixel(x, y, color, game);
        texture_pos += step;
    }

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
	draw_wall_column(game, i, start_y, end, &xpm[0], height);
	y = end;
	while (y < (data->height * TILE_SIZE))
	{
		put_pixel(i, y, game->y3d->texture->floor_color, game);
		y++;
	}
}
*/


void	calcul_ray(t_game *game, t_ray *draw, int x)
{
    draw->cameraX = 2 * x / (double)WIDTH - 1;
    draw->rayDirX = (game->player.dirX + game->player.planeX * draw->cameraX);
    draw->rayDirY = (game->player.dirY + game->player.planeY * draw->cameraX);
    draw->mapX = (int)game->player.x;
    draw->mapY = (int)game->player.y;
	printf("x : %d | y %d\n", draw->mapX, draw->mapY);
	draw->deltaDistX = fabs(1 / draw->rayDirX);
	draw->deltaDistY = fabs(1 / draw->rayDirY);
}


void	init_ray(t_game *game, t_ray *draw, int x)
{
	calcul_ray(game, draw, x);
	if (draw->rayDirX < 0)
	{
		draw->stepX = -1 ;
		draw->sideDistX = (game->player.x - draw->mapX) * draw->deltaDistX;
	}
	else
	{
		draw->stepX = 1;
		draw->sideDistX = (draw->mapX + 1.0
				- game->player.x) * draw->deltaDistX;
	}
	if (draw->rayDirY < 0)
	{
		draw->stepY = -1;
		draw->sideDistY = (game->player.y - draw->mapY) * draw->deltaDistY;
	}
	else
	{
		draw->stepY = 1;
		draw->sideDistY = (draw->mapY + 1.0
				- game->player.y) * draw->deltaDistY;
	}
}

void wall_hit(t_game *game, t_ray *draw)
{
    // Remove the while loop - it's already in wall_dist
    if (draw->sideDistX < draw->sideDistY)
    {
        draw->sideDistX += draw->deltaDistX;
        draw->mapX += draw->stepX;
        draw->side = 0;
    }
    else
    {
        draw->sideDistY += draw->deltaDistY;
        draw->mapY += draw->stepY;
        draw->side = 1;
    }

    if (game->y3d->map[draw->mapY][draw->mapX] == '1')
	{
		//printf("x : %d | y : %d\n",draw->mapX, draw->mapY);
        draw->hit = 1;
	}
}


void wall_dist(t_game *game, t_ray *draw, int x)
{
    init_ray(game, draw, x);
    draw->hit = 0;

    
    while (!draw->hit)
    {
        wall_hit(game, draw);
    }	
    
    if (draw->side == 0)
        draw->perpWallDist = (draw->sideDistX - draw->deltaDistX);
    else
        draw->perpWallDist = (draw->sideDistY - draw->deltaDistY);
    
    if (draw->perpWallDist <= 0)
        draw->perpWallDist = 0.01;
        
    draw->lineHeight = (int) (HEIGHT / draw->perpWallDist);
}

void	wall_size(t_game *game, t_ray *draw)
{
	draw->drawStart = -draw->lineHeight / 2 + (HEIGHT) / 2;
	if (draw->drawStart < 0)
		draw->drawStart = 0;
	draw->drawEnd = draw->lineHeight / 2 + (HEIGHT)  / 2;
	if (draw->drawEnd >= (HEIGHT))
		draw->drawEnd = (HEIGHT) - 1;
	if (draw->side == 0)
		draw->wallX = game->player.y + draw->perpWallDist * draw->rayDirY;
	else
		draw->wallX = game->player.x + draw->perpWallDist * draw->rayDirX;
	draw->wallX -= floor((draw->wallX));
	draw->tex_x = (int)(draw->wallX * (double)64);
	if (draw->side == 0 && draw->rayDirX > 0)
		draw->tex_x = 64 - draw->tex_x - 1;
	if (draw->side == 1 && draw->rayDirY < 0)
		draw->tex_x = 64 - draw->tex_x - 1;
	draw->step = 1.0 * 64 / draw->lineHeight;
	draw->texPos = (draw->drawStart - HEIGHT / 2
			+ draw->lineHeight / 2) * draw->step;
}

void	draw_game(t_game *game, t_ray *draw, int x)
{
	int	y;
	int	color;

	color = 0;
	y = 0;
	while (y < draw->drawStart)
	{
		put_pixel( x, y, game->y3d->texture->ceiling_color, game);
		y++;
	}
	// printf("=>%d", draw->drawEnd);
	// printf("Ray Position: (%d, %d)\n", draw->mapX, draw->mapY);
	// printf("StepX: %d, StepY: %d\n", draw->stepX, draw->stepY);
	// printf("SideDistX: %f, SideDistY: %f\n", draw->sideDistX, draw->sideDistY);
	// printf("DeltaDistX: %f, DeltaDistY: %f\n", draw->deltaDistX, draw->deltaDistY);
 
	while (y <= draw->drawEnd)
	{
		color = 255;
		put_pixel(x, y, color, game);
		y++;
	}
	while (y < HEIGHT)
	{
		put_pixel(x, y, game->y3d->texture->floor_color, game);
		y++;
	}
} 

int	draw_loop(t_extra *extra)
{
	int 	x;
	t_y3d 	*data;
    t_game  *game;
    t_ray	ray;

    game = extra->game;
	data = game->y3d;
	(void) data;
	clear_screen(game);
	x = 0;
	while (x < WIDTH)
	{
		//printf("---------------------------------%f %f %f\n", game->player.x, game->player.y, game->player.angle);
		wall_dist(game, &ray, x);
		wall_size(game, &ray);
		draw_game(game, &ray, x);
	//	draw_line(&game->player, game, start_x, i);
		x++;
	}
	move_player(&game->player, game->y3d);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}