/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:19:36 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/31 18:54:46 by mokariou         ###   ########.fr       */
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

	i = -1;
	while (++i, i < data->row_width[0])
	{
		if (data->map[0][i] != ' ' && data->map[0][i] != '1')
			return (true);
	}
	i = -1;
	while (++i, i < data->row_width[data->height - 1])
	{
		if (data->map[data->height - 1][i] != ' ' && data->map[data->height
			- 1][i] != '1')
			return (true);
	}
	i = -1;
	while (i++, i < data->height)
	{
		if (data->row_width[i] > 0 && data->map[i][0] != ' '
			&& data->map[i][0] != '1')
			return (true);
		if (data->row_width[i] > 1 && data->map[i][data->row_width[i]
			- 1] != ' ' && data->map[i][data->row_width[i] - 1] != '1')
			return (true);
	}
	return (false);
}

char	**copy(t_y3d *y3d)
{
	int		i;
	char	**copied;

	copied = malloc(sizeof(char *) * (y3d->height + 1));
	if (!copied)
		return (NULL);
	i = -1;
	while (++i < y3d->height)
	{
		copied[i] = ft_strdup(y3d->map[i]);
		if (!copied[i])
		{
			couble_free(copied, i);
			return (NULL);
		}
	}
	copied[i] = NULL;
	return (copied);
}

bool	flood_fill_backtrack(t_y3d *data, int x, int y, char **visited)
{
	if (x < 0 || x >= data->height || y < 0 || y >= data->row_width[x])
		return (true);
	if (data->map[x][y] == '1' || visited[x][y] == '1')
		return (false);
	visited[x][y] = '1';
	return (flood_fill_backtrack(data, x + 1, y, visited)
		|| flood_fill_backtrack(data, x - 1, y, visited)
		|| flood_fill_backtrack(data, x, y + 1, visited)
		|| flood_fill_backtrack(data, x, y - 1, visited));
}

bool	check_map_spaces(t_y3d *data)
{
	char	**visited;

	int i, j;
	if (!data->map || !data->map[0])
		return (true);
	visited = copy(data);
	if (!visited)
		return (true);
	i = -1;
	if (check_angles(data))
		return (error("not the right structure for the map!"),
			couble_free(visited, data->height), true);
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->row_width[i])
		{
			if ((data->map[i][j] == ' ' && !is_valid_space(data, i, j))
				|| flood_fill_backtrack(data, i, j, visited))
				return (error("not the right structure for the map!"),
					couble_free(visited, data->height), true);
		}
	}
	couble_free(visited, data->height);
	return (false);
}
