/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:35:22 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/19 17:42:40 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"



bool	set_xpm(t_textures *textures, t_game *game, char *old_path, t_xpm *xpm)
{
	int		x;
	int		y;
	char	*path;
	size_t	len;

	len = ft_strlen(old_path);
    if (old_path[len - 1] == '\n')
		len--;
	path = malloc(len + 1);
	if (!path)
		return (true);
	ft_strlcpy(path, old_path, len + 1);
	(void) textures;
	(void) game;
	if (access(path, R_OK) == -1)
        return (error("Error: File not accessible"), true);
	xpm->img_ptr = mlx_xpm_file_to_image(game->mlx, path, &xpm->width, &xpm->height);
	if (!xpm->img_ptr)
		return (error("failed xpm"),true);
	xpm->data = (int *)mlx_get_data_addr(xpm->img_ptr, &xpm->bbp, &xpm->size_line, &xpm->endian);
	xpm->colors = (int *)malloc(xpm->width * xpm->height * sizeof(int));
	if (!xpm->colors)
		return (mlx_destroy_image(game->mlx ,xpm->img_ptr), true);
	y = -1;
	while (++y, y < xpm->height)
	{
		x = -1;
		while (++x, x < xpm->width)
			xpm->colors[y * xpm->width + x] = xpm->data[y * xpm->width + x];
	}
	mlx_destroy_image(game->mlx, xpm->img_ptr);
	return (false);
}

bool	init_xpm(t_textures *texture, t_game *game, t_xpm *xpm)
{
	(void) xpm;
	(void) texture;
	if (set_xpm(texture, game, texture->north, xpm))
		return (true);
	return(false);
}

