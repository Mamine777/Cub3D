/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:20:58 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/17 16:33:51 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

void	init_bool(t_textures *texture)
{
	texture->no = false;
	texture->so = false;
	texture->we = false;
	texture->ea = false;
	texture->north = NULL;
	texture->south = NULL;
	texture->west = NULL;
	texture->east = NULL;
	texture->ceiling_color = -1;
	texture->floor_color = -1;
}

static void	set_east(t_textures *texture, char *line, bool *flag)
{
	if (*flag == true)
	{
		error("testure duplication");
		exit(1);
	}
	if (texture->ea)
		free(texture->east);
	texture->ea = true;
	texture->east = ft_strdup(line);
}

static void	set_west(t_textures *texture, char *line, bool *flag)
{
	if (*flag == true)
	{
		error("testure duplication");
		exit(1);
	}
	if (texture->west)
		free(texture->west);
	texture->we = true;
	texture->west = ft_strdup(line);
}

static void	set_south(t_textures *texture, char *line, bool *flag)
{
	if (*flag == true)
	{
		error("testure duplication");
		exit(1);
	}
	if (texture->south)
		free(texture->south);
	texture->so = true;
	texture->south = ft_strdup(line);
}

static void	set_north(t_textures *texture, char *line, bool *flag)
{
	if (*flag == true)
	{
		error("testure duplication");
		exit(1);
	}
	if (texture->north)
		free(texture->north);
	texture->no = true;
	texture->north = ft_strdup(line);
}

int validate_textures(t_textures *texture)
{
    if (!texture->no || !texture->so || !texture->we || !texture->ea)
    {
        error("Missing required textures (NO, SO, WE, EA)");
        return (1);
    }
    return (0);
}

int set_texture(int fd, t_textures *texture)
{
    char    *line;
    char    **path;

    line = get_next_line(fd);
    if (!line)
        return (error("gnl failed"), 1);
    init_bool(texture);
    while (line)
    {
        path = ft_split(line, ' ');
        free(line);
		if (!ft_strncmp(path[0], "NO", 3) || !ft_strncmp(path[0], "SO", 3) || !ft_strncmp(path[0], "WE", 3) || !ft_strncmp(path[0], "EA", 3))
		{
	        if (!path || !path[0] || !path[1] || path[2])
	        {
	            couble_free(path);
	            return (error("Invalid texture format"), 1);
	        }
	        if (!ft_strncmp(path[0], "NO", 3))
			{
	            set_north(texture, path[1], &texture->no);
			}
	        else if (!ft_strncmp(path[0], "SO", 3))
	            set_south(texture, path[1], &texture->so);
	        else if (!ft_strncmp(path[0], "WE", 3))
	            set_west(texture, path[1], &texture->we);
	        else if (!ft_strncmp(path[0], "EA", 3))
	            set_east(texture, path[1], &texture->ea);
		}
        couble_free(path);
        line = get_next_line(fd);
    }
    return (validate_textures(texture), 0);
}
