/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanUp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:06:35 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/30 21:15:49 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

void	clean_texture(t_textures *texture)
{
	if (!texture)
		return ;
	if (texture->east)
		free(texture->east);
	if (texture->north)
		free(texture->north);
	if (texture->south)
		free(texture->south);
	if (texture->west)
		free(texture->west);
	free(texture);
}

void	clean_y3d(t_y3d *y3d)
{
	if (!y3d)
		return ;
	couble_free(y3d->map);
	free(y3d);
}

void free_game(t_game *game)
{
    if (!game)
        return ;

    if (game->mlx)
    {
        if (game->win)
            mlx_destroy_window(game->mlx, game->win);
        if (game->img)
            mlx_destroy_image(game->mlx, game->img);
        mlx_destroy_display(game->mlx);
    }

	//free(game);
}

void	free_xpm(t_xpm *xpm)
{
	int	i;

	if (!xpm)
		return ;
	i = -1;
	while (++i, i < 4)
	{
		printf("i : %d\n", i);
		if (&xpm[i] && xpm[i].colors)
            free(xpm[i].colors);
	}
	free(xpm);
}

void cleanup_and_exit(t_y3d *y3d, t_xpm *xpm)
{
    t_game *game = NULL;
    (void) xpm;
    if (y3d)
    {
        game = y3d->game;
        clean_texture(y3d->texture);
        clean_y3d(y3d);
    }
    if (game)
        free_game(game);
     if (xpm)
        free_xpm(xpm);
        
    exit(0);
}

int	esc(t_game *game)
{
	cleanup_and_exit(game->y3d, game->xpm);
	return (0);
}
