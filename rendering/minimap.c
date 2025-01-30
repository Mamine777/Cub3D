/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:26:03 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/29 13:13:43 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

// void draw_map(t_game *game)
// {
//     int color = 0x0000FF;
//     for(int y = 0; game->y3d->map[y]; y++)
//         for(int x = 0; game->y3d->map[y][x]; x++)
//             if(game->y3d->map[y][x] == '1')
//                 draw_square(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, color, game);
// }

// void mini_draw(t_player *player, t_game *game, float start_x)
// {
//     float cos_angle = cos(start_x);
//     float sin_angle = sin(start_x);
//     float ray_x = player->x;
//     float ray_y = player->y;
// 	t_y3d	*data;

// 	data = game->y3d;
//         while(!touch(ray_x, ray_y, data))
//         {
//            put_pixel(ray_x, ray_y, 0xFF0000, game);
//            ray_x += cos_angle;
//         ray_y += sin_angle;
//         }
// }

// int	minimap(t_game *game)
// {
// 	float	fraction;
// 	float	start_x;;
// 	int		i;
// 	t_y3d	*data;

// 	data = game->y3d;
// 	clear_screen(game);
// 	move_player(&game->player, game->y3d);
// 	draw_square(game->player.x, game->player.y, 10, 0x00FF00, game);
// 	draw_map(game);
// 	fraction = PI / 3 / TILE_SIZE;
// 	start_x = game->player.angle - PI / 6;
// 	i = 0;
//     while(i < TILE_SIZE)
//     {
//         mini_draw(&game->player, game, start_x);
//         start_x += fraction;
//         i++;
//     }
// 	mlx_put_image_to_window(game->mlx, game->win, game->img_mini, 0, 0);
// 	return (0);
// }





/* void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * img->line_length + x * img->bits_per_pixel / 8;
	img->addr[index] = color & 0xFF;
	img->addr[index + 1] = (color >> 8) & 0xFF;
	img->addr[index + 2] = (color >> 16) & 0xFF;
}

t_wall	*wall_side(t_game *game, t_draw *draw)
{
	t_wall	*wall;

	if (draw->side == 1)
	{
		if (draw->stepY == -1)
			wall = &game->wall_south;
		else
			wall = &game->wall_north;
	}
	else
	{
		if (draw->stepX == -1)
			wall = &game->wall_east;
		else
			wall = &game->wall_west;
	}
	return (wall);
}

int	get_color(t_game *game, t_draw *draw, int color)
{
	int		tex_y;
	int		k;
	t_wall	*wall;

	tex_y = (int)draw->texPos & (64 - 1);
	k = 0;
	draw->texPos += draw->step;
	color = 0;
	wall = wall_side(game, draw);
	while (k < wall->info)
	{
		if (wall->wall[tex_y][draw->tex_x] == wall->col[k].c)
		{
			color = wall->col[k].id;
			break ;
		}
		k++;
	}
	return (color);
}

void	draw_game(t_game *game, t_draw *draw, int x)
{
	int	y;
	int	color;

	y = -1;
	color = 0;
	while (++y < draw->drawStart)
		// if (!(y > HEIGHT || x > WIDTH || x < 0 || y < 0))
		my_mlx_pixel_put(&game->img, x, y, game->ceiling);
	y--;
	while (y++ <= draw->drawEnd)
	{
		color = get_color(game, draw, color);
		// if (!(y > HEIGHT || x > WIDTH || x < 0 || y < 0))
		my_mlx_pixel_put(&game->img, x, y, color);
	}
	y--;
	while (y++ < HEIGHT)
		//if (!(y > HEIGHT || x > WIDTH || x < 0 || y < 0))
		my_mlx_pixel_put(&game->img, x, y, game->floor);
}   
void	calcul_ray(t_game *game, t_draw *draw, int x)
{
	draw->cameraX = 2 * x / (double)WIDTH - 1;
	draw->rayDirX = game->p1.dirx + game->p1.planex * draw->cameraX;
	draw->rayDirY = game->p1.diry + game->p1.planey * draw->cameraX;
	draw->mapX = (int) game->p1.posx;
	draw->mapY = (int) game->p1.posy;
	draw->deltaDistX = fabs(1 / draw->rayDirX);
	draw->deltaDistY = fabs(1 / draw->rayDirY);
}

void	init_ray(t_game *game, t_draw *draw, int x)
{
	calcul_ray(game, draw, x);
	if (draw->rayDirX < 0)
	{
		draw->stepX = -1;
		draw->sideDistX = (game->p1.posx - draw->mapX) * draw->deltaDistX;
	}
	else
	{
		draw->stepX = 1;
		draw->sideDistX = (draw->mapX + 1.0
				- game->p1.posx) * draw->deltaDistX;
	}
	if (draw->rayDirY < 0)
	{
		draw->stepY = -1;
		draw->sideDistY = (game->p1.posy - draw->mapY) * draw->deltaDistY;
	}
	else
	{
		draw->stepY = 1;
		draw->sideDistY = (draw->mapY + 1.0
				- game->p1.posy) * draw->deltaDistY;
	}
}

void	wall_hit(t_game *game, t_draw *draw)
{
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
	if (draw->mapX < 0)
		draw->mapX = 0;
	if (game->map.map[draw->mapY][draw->mapX] == '1')
		draw->hit = 1;
}

void	wall_dist(t_game *game, t_draw *draw, int x)
{
	init_ray(game, draw, x);
	draw->hit = 0;
	while (!draw->hit)
		wall_hit(game, draw);
	if (draw->side == 0)
		draw->perpWallDist = (draw->sideDistX - draw->deltaDistX);
	else
		draw->perpWallDist = (draw->sideDistY - draw->deltaDistY);
	draw->lineHeight = (int)(HEIGHT / draw->perpWallDist);
}
void	wall_size(t_game *game, t_draw *draw)
{
	draw->drawStart = -draw->lineHeight / 2 + HEIGHT / 2;
	if (draw->drawStart < 0)
		draw->drawStart = 0;
	draw->drawEnd = draw->lineHeight / 2 + HEIGHT / 2;
	if (draw->drawEnd >= HEIGHT)
		draw->drawEnd = HEIGHT - 1;
	if (draw->side == 0)
		draw->wallX = game->p1.posy + draw->perpWallDist * draw->rayDirY;
	else
		draw->wallX = game->p1.posx + draw->perpWallDist * draw->rayDirX;
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

int	peutetre(t_game *game)
{
	int			x;
	t_draw		draw;

	x = -1;
	clear_image(game);
	while (++x < WIDTH)
	{
		wall_dist(game, &draw, x);
		wall_size(game, &draw);
		draw_game(game, &draw, x);
	}
	printf("dsl\n");
	move_player(&game->p1);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	// draw_map(game);
	// mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 0, 0);
	return (0);
} */