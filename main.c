/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:48:26 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/29 14:23:41 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "y3d.h"


void	init_extra(t_game *game, t_xpm *xpm, t_extra *extra)
{
	extra->game = game;
	extra->xpm = xpm;
	game->xpm = xpm;
}

int	main(int ac, char **av)
{
	t_textures *texture;
	t_y3d *data;
	t_game game;
	t_xpm	*xpm;
	t_extra	extra;

	if (ac != 2)
		return (1);
	texture = malloc(sizeof(t_textures));
	if (!texture)
		return (fprintf(stderr, "Failed to allocate memory for texture\n"), 1);

	data = malloc(sizeof(t_y3d));
	if (!data)
		return (error("Failed to allocate memory for data\n"),
			free(texture), 1);
	xpm = malloc(sizeof(t_xpm) * 4);
	if (!xpm)
		return (error("Failed to allocate memory for data\n"),
			free(texture), free(data),1);
	if (init_texture(texture, av) != 0)
		return (clean_texture(texture), 1);
	if (init_map(data, av[1]))
		return (clean_texture(texture), 1);
	if (validate_input(data))
		return (clean_texture(texture), couble_free(data->map), 1);
	if (check_map_spaces(data))
		return (clean_texture(texture), couble_free(data->map), 1);
	//
	init_game(&game, data, texture, xpm);
	if (init_xpm(texture, &game, xpm))
		return (clean_texture(texture), couble_free(data->map), 1);
	init_extra(&game, xpm, &extra);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);

	mlx_loop_hook(game.mlx, draw_loop, &extra);
	mlx_loop(game.mlx);
	//
	couble_free(data->map);
	clean_texture(texture);
}