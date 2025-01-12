/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:48:26 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/12 16:45:56 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "y3d.h"

int main (int ac, char **av)
{
	t_textures	texture;
	t_y3d		data;
	t_game		game;

	if (ac != 2)
		return (1);
	if (init_texture(&texture, av) != 0)
		return (clean_texture(&texture), 1);
	//	system("leaks cub3d");
	if (init_map(&data, av[1]))
		return (clean_texture(&texture), 1);
	 if (validate_input(&data))
	 	return (clean_texture(&texture) ,couble_free(data.map), 1);
	if (check_map_spaces(&data))
		return (clean_texture(&texture),couble_free(data.map),1);
	init_game(&game, &data, &texture);
	mlx_loop(game.mlx);
	for (int i = 0; i < data.height; i++)
		printf("%s\n", data.map[i]);
	couble_free(data.map);
	clean_texture(&texture);
}