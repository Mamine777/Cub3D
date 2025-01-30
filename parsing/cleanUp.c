/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanUp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:06:35 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/30 17:11:54 by mokariou         ###   ########.fr       */
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
	if (texture)
		free(texture);
	texture->east = NULL;
	texture->north = NULL;
	texture->south = NULL;
	texture->west = NULL;
}

void	clean_y3d(t_y3d *y3d)
{
	if (!y3d)
		return ;
	couble_free(y3d->map);
	free(y3d);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		if (game->img_mini)
			mlx_destroy_image(game->mlx, game->img_mini);
		mlx_destroy_display(game->mlx);
	}
	free(game);
	if (game->y3d)
		free(game->y3d);
	if (game->xpm)
		free(game->xpm);
	if (game->player.y3d)
		free(game->player.y3d);
	if (game->player.xpm)
		free(game->player.xpm);
}

void	free_xpm(t_xpm *xpm)
{
	int	i;

	if (!xpm)
		return ;
	i = 0;
	while (++i, i < 4)
	{
		if (xpm[i].colors != NULL)
        	free(xpm[i].colors);
    	if (xpm[i].data != NULL)
			free(xpm[i].data);
	}
	free(xpm);
}

void    cleanup_and_exit(t_y3d *y3d, t_xpm *xpm)
{
	clean_texture(y3d->texture);
	clean_y3d(y3d);
	free_game(y3d->game);
	free_xpm(xpm);
	exit(0);
}
