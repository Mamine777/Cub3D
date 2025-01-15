/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:27:54 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/14 19:13:42 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

int	check_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	skip_config_lines(int fd, char **line)
{
	char	*buffer;

	buffer = get_next_line(fd);
	if (!buffer)
		return (1);
	while (buffer)
	{
		if (buffer[0] == '\n' || ft_strncmp(buffer, "NO", 2) == 0
			|| ft_strncmp(buffer, "SO", 2) == 0 || ft_strncmp(buffer, "WE",
				2) == 0 || ft_strncmp(buffer, "EA", 2) == 0
			|| ft_strncmp(buffer, "F", 1) == 0 || ft_strncmp(buffer, "C",
				1) == 0)
		{
			free(buffer);
			buffer = get_next_line(fd);
		}
		else
		{
			*line = buffer;
			return (0);
		}
	}
	free(buffer);
	return (1);
}

int	count_map_dimensions(int fd, t_y3d *data, char *first_line)
{
	char	*line;
	int		i;

	line = NULL;
	if (check_map_line(first_line))
		return (error("Invalid map content"), 1);
	if (first_line[ft_strlen(first_line) - 1] == '\n')
		data->row_width[0] = ft_strlen(first_line) - 1;
	else
		data->row_width[0] = ft_strlen(first_line);
	data->height = 1;
	line = get_next_line(fd);
	i = 1;
	if (first_line[ft_strlen(first_line) - 1] == '\n')
			data->biggest_width = ft_strlen(first_line) - 1;
		else
			data->row_width[i] = ft_strlen(first_line);
	while (line && line[0] != '\0' && line[0] != '\n')
	{
		if (line[ft_strlen(line) - 1] == '\n')
			data->row_width[i] = ft_strlen(line) - 1;
		else
			data->row_width[i] = ft_strlen(line);
		if (data->biggest_width < data->row_width[i])
			data->biggest_width = data->row_width[i];
		if (check_map_line(line))
			return (error("Invalid map content"), free(line),
				1);
		data->height++;
		i++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (0);
}

int	fill_map_data(int fd, t_y3d *data, char *first_line)
{
	char	*line;
	int		i;
	int		len;

	data->map = (char **)malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		return (error("Memory allocation failed for map!") ,
			1);
	len = ft_strlen(first_line);
	if (first_line[len - 1] == '\n')
		len--;
	data->map[0] = (char *)malloc(len + 1);
	if (!data->map[0])
		return (error("Memory allocation failed for map row!"),
			couble_free(data->map), 1);
	ft_strlcpy(data->map[0], first_line, len + 1);
	i = 1;
	line = get_next_line(fd);
	while (line && i < data->height)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			len--;
		data->map[i] = (char *)malloc(len + 1);
		if (!data->map[i])
			return (error("Memory allocation failed for map row!"),
				couble_free(data->map), free(line), 1);
		ft_strlcpy(data->map[i], line, len + 1);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (line)
		free(line);
	data->map[i] = NULL;
	return (0);
}

int	init_map(t_y3d *data, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error("Failed to open file"), 1);
	if (skip_config_lines(fd, &line) != 0)
		return (close(fd), free(line), 1);
	if (count_map_dimensions(fd, data, line) != 0)
		return (free(line), close(fd), 1);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error("Failed to reopen file"), 1);
	if (skip_config_lines(fd, &line) != 0)
		return (free(line), close(fd), 1);
	if (fill_map_data(fd, data, line) != 0)
		return (free(line), close(fd), 1);
	free(line);
	close(fd);
	return (0);
}
