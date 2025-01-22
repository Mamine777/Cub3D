/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:27:04 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/19 19:03:50 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

int	set_rgb(char *line, int *color)
{
	char	**components;
	int		r;
	int		g;
	int		b;

	components = ft_split(line, ',');
	if (!components || !components[0] || !components[1] || !components[2]
		|| components[3])
		return (error("Invalid RGB format"), couble_free(components), 1);
	r = ft_atoi(components[0]);
	g = ft_atoi(components[1]);
	b = ft_atoi(components[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (error("RGB values out of range"), couble_free(components), 1);
	*color = (r << 16) | (g << 8) | b;
	couble_free(components);
	return (0);
}

int	parse_rgb(int fd, t_textures *texture)
{
	char	**path;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		path = ft_split(line, ' ');
		free(line);
		if (!ft_strncmp(path[0], "F", 2) || !ft_strncmp(path[0], "C", 2))
		{			
			if (!path || !path[0] || !path[1] || path[2])
			{
				error("Invalid RGB line format");
				return (couble_free(path), 1);
			}
			if (!ft_strncmp(path[0], "F", 2))
			{
				if (set_rgb(path[1], &texture->floor_color))
					return (couble_free(path), 1);
			}
			else if (!ft_strncmp(path[0], "C", 2))
			{
				if (set_rgb(path[1], &texture->ceiling_color))
					return (couble_free(path), 1);
			}
		}
		couble_free(path);
		line = get_next_line(fd);
	}
	return (0);
}

int	init_texture(t_textures *texture, char **av)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	if (set_texture(fd, texture))
		return (close(fd), 1);
	close(fd);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	if (parse_rgb(fd, texture))
		return (close(fd), 1);
	if (!texture->no || !texture->so || !texture->we || !texture->ea)
		return (error("Missing texture"), close(fd), 1);
	if (texture->floor_color == -1 || texture->ceiling_color == -1)
		return (error("Missing floor or ceiling color"), close(fd), 1);
	return (close(fd), 0);
}
