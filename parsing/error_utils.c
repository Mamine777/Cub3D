/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:26:03 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/12 16:32:23 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

void	error(const char *str)
{
	printf("%s\n", str);
}

void	couble_free(char **path)
{
	int i;

	i = 0;
	if (!path)
		return ;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

bool	validate_input(t_y3d *data)
{
	int	i;
	int	count;
	int	j;
	if (!data->map || !data->map[0])
		return (true);
	i = -1;
	count = 0;
	while (++i, i < data->height)
	{
		j = -1;
		while (++j, j < data->row_width[i])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'W' ||data->map[i][j] == 'S' || data->map[i][j] == 'E')
				count++;
		}
	}
	if (count != 1)
		return (error("one player is required"), true);
	return (0);
}