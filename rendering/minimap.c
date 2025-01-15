/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:26:03 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/15 16:30:56 by mokariou         ###   ########.fr       */
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