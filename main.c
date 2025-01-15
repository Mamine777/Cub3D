/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:48:26 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/15 16:30:16 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "y3d.h"

int	main(int ac, char **av)
{
	t_textures *texture;
	t_y3d *data;
	t_game game;

	if (ac != 2)
		return (1);
	texture = malloc(sizeof(t_textures));
	if (!texture)
		return (fprintf(stderr, "Failed to allocate memory for texture\n"), 1);

	data = malloc(sizeof(t_y3d));
	if (!data)
		return (error("Failed to allocate memory for data\n"),
			free(texture), 1);

	if (init_texture(texture, av) != 0)
		return (clean_texture(texture), 1);
	//	system("leaks cub3d");
	if (init_map(data, av[1]))
		return (clean_texture(texture), 1);
	if (validate_input(data))
		return (clean_texture(texture), couble_free(data->map), 1);
	if (check_map_spaces(data))
		return (clean_texture(texture), couble_free(data->map), 1);
	//

	init_game(&game, data, texture);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	//mlx_loop_hook(game.mlx, minimap, &game);
	mlx_loop(game.mlx);

	//
	// for (int i = 0; i < data.height; i++)
	// 	printf("%s\n", data.map[i]);
	couble_free(data->map);
	clean_texture(texture);
}