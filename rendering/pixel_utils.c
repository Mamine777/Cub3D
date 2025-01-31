/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:34:10 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/31 18:55:09 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

t_xpm	*wall_side(t_game *game, t_ray *ray)
{
	t_xpm	*texture;

	if (ray->side > 0)
	{
		if (ray->stepY == -1)
			texture = &game->xpm[1];
		else
			texture = &game->xpm[0];
	}
	else
	{
		if (ray->stepX == -1)
			texture = &game->xpm[2];
		else
			texture = &game->xpm[3];
	}
	return (texture);
}

int	get_color(t_game *game, t_ray *ray, t_xpm *wall)
{
	int	color;

	color = 0;
	(void)game;
	if (ray->tex_x >= 0 && ray->tex_x < wall->width && (int)ray->texPos >= 0
		&& (int)ray->texPos < wall->height)
	{
		color = wall->colors[(int)ray->texPos * wall->width + ray->tex_x];
	}
	return (color);
}

void	calculate_texture_position(t_game *game, t_ray *ray, t_draw_info *info)
{
	double wallX;

	wallX = 0;
	wallX -= floor(wallX);
	(void)game;
	info->texX = (int)(wallX * info->current_texture->width);
	if ((ray->side == 0 && ray->rayDirX > 0) || (ray->side == 1
			&& ray->rayDirY < 0))
		info->texX = info->current_texture->width - info->texX - 1;
	info->step = (double)info->current_texture->height / (ray->drawEnd
			- ray->drawStart);
	info->texPos = 0;
}