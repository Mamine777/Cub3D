/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:35:22 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/30 18:48:05 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

bool	set_xpm(t_game *game, char *old_path, t_xpm *xpm, int i)
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
	(void) game;
	if (access(path, R_OK) == -1)
        return (error("Error: File not accessible"), true);
	xpm[i].img_ptr = mlx_xpm_file_to_image(game->mlx, path, &xpm[i].width, &xpm[i].height);
	if (!xpm[i].img_ptr)
		return (error("failed xpm"),true);
	xpm[i].data = (int *)mlx_get_data_addr(xpm[i].img_ptr, &xpm[i].bbp, &xpm[i].size_line, &xpm[i].endian);
	if (!xpm[i].data)
		return (true);
	xpm[i].colors = (int *)malloc(xpm[i].width * xpm[i].height * sizeof(int));
	if (!xpm[i].colors)
		return (mlx_destroy_image(game->mlx ,xpm[i].img_ptr), true);
	y = -1;
	while (++y, y < xpm[i].height)
	{
		x = -1;
		while (++x, x < xpm[i].width)
			xpm[i].colors[y * xpm[i].width + x] = xpm[i].data[y * xpm[i].width + x];
	}
	mlx_destroy_image(game->mlx, xpm[i].img_ptr);
	return (false);
}

bool	init_xpm(t_textures *texture, t_game *game, t_xpm *xpm)
{
	(void) xpm;
	(void) texture;
	if (set_xpm(game, texture->north, xpm, 0) || set_xpm(game, texture->south, xpm, 1) ||
		set_xpm(game, texture->west, xpm, 2) || set_xpm(game, texture->east, xpm, 3))
		return (true);
	return(false);
}

