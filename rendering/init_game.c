/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:30:59 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/12 17:07:10 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

void	init_game(t_game *game, t_y3d *data, t_textures *textrure)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1280, 720, "cub3D");
	game->img = mlx_new_image(game->mlx, 1280, 720);
	data->game = game;
	data->texture = textrure;
	
}