/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:19:36 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/11 18:56:53 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

bool	is_valid_space(t_y3d *data, int x, int y)
{
	static int	dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	static int	dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int			i;
	int			nx;
	int			ny;

	i = -1;
	while (++i, i < 8)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx >= 0 && nx < data->height && ny >= 0 && ny < data->row_width[nx])
		{
			if (data->map[nx][ny] != '1' && data->map[nx][ny] != ' ')
				return (false);
		}
	}
	return (true);
}

bool	check_angles(t_y3d *data)
{
	int	i;

	for (i = 0; i < data->row_width[0]; i++)
	{
		if (data->map[0][i] != ' ' && data->map[0][i] != '1')
			return (true);
	}
	for (i = 0; i < data->row_width[data->height - 1]; i++)
	{
		if (data->map[data->height - 1][i] != ' ' && data->map[data->height - 1][i] != '1')
			return (true);
	}
	for (i = 0; i < data->height; i++)
	{
		if (data->row_width[i] > 0 && data->map[i][0] != ' ' && data->map[i][0] != '1')
			return (true);
		if (data->row_width[i] > 1 && data->map[i][data->row_width[i] - 1] != ' ' && data->map[i][data->row_width[i] - 1] != '1')
			return (true);
	}

	return (false);
}
bool	check_map_spaces(t_y3d *data)
{
	int	i;
	int	j;

	if (!data->map || !data->map[0])
		return (1);
	i = -1;
	if (check_angles(data))
		return (error("not the right structure for the map!"), true);
	while (++i, i < data->height)
	{
		j = -1;
		while (++j, j < data->row_width[i])
		{
			if (data->map[i][j] == ' ' && !is_valid_space(data, i, j))
				return (error("not the right structure for the map!"), true);
		}
	}
	return (false);
}
