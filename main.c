/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:48:26 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/31 12:06:22 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "y3d.h"


void	init_extra(t_game *game, t_xpm *xpm, t_extra *extra)
{
	extra->game = game;
	extra->xpm = xpm;
	game->xpm = xpm;
}

void cleanup(t_textures *texture, t_y3d *data)
{
    if (texture)
        clean_texture(texture);
    if (data)
        free(data);
}

bool init_and_validate(t_textures *texture, t_y3d *data, t_xpm *xpm, char **map_file)
{
	(void) xpm;
    if (init_texture(texture, map_file) != 0)
        return (false);
    if (init_map(data, map_file[1]))
        return (false);
    if (validate_input(data))
        return (false);
    if (check_map_spaces(data))
        return (false);
    return (true);
}

bool cub3d(t_textures *texture, t_y3d *data, t_game *game, t_xpm *xpm)
{
    t_extra extra;

    init_game(game, data, texture, xpm);
    if (init_xpm(texture, game, xpm))
        return (false);
    init_extra(game, xpm, &extra);

    mlx_hook(game->win, 2, 1L << 0, key_press, &game->player);
    mlx_hook(game->win, 3, 1L << 1, key_release, &game->player);
    mlx_hook(game->win, 17, 0, esc, game);
    mlx_loop_hook(game->mlx, draw_loop, &extra);
    mlx_loop(game->mlx);

    return (true);
}

int	main(int ac, char **av)
{
	t_textures *texture;
	t_y3d *data;
	t_game game;
	t_xpm	xpm[4];
	t_extra	extra;

	if (ac != 2)
		return (1);
	texture = malloc(sizeof(t_textures));
	data = malloc(sizeof(t_y3d));
	(void)extra;
	if (!texture || !data)
        return (error("Failed to allocate memory"),
            cleanup(texture, data), 1);
//
    if (!init_and_validate(texture, data, xpm, av))
    {
        cleanup(texture, data);
        return (1);
    }
    if (!cub3d(texture, data, &game, xpm))
		esc(&game);

    // Cleanup after the game loop ends
    //cleanup(texture, data, xpm);
    return (0);
}
