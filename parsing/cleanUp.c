/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanUp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:06:35 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/09 12:03:52 by mokariou         ###   ########.fr       */
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
	texture->east = NULL;
	texture->north = NULL;
	texture->south = NULL;
	texture->west = NULL;
}

void    cleanup_and_exit(t_textures *texture, char **path, char *line, const char *msg)
{
        if (path)
                couble_free(path);
        if (line)
                free(line);
        clean_texture(texture);
        error(msg);
        exit(1);
}