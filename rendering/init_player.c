/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:40:23 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/17 13:13:52 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

int	key_press(int keycode, t_player *player)
{
	printf("%d\n", keycode);
	if (keycode == W)
		player->key_up = true;
	if (keycode == S)
		player->key_down = true;
	if (keycode == A)
		player->key_left = true;
	if (keycode == D)
		player->key_right = true;
	if (keycode == LEFT)
		player->left_rotate = true;
	if (keycode == RIGHT)
		player->right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

bool	set_x_y(t_y3d *data, int *x, int *y)
{
	int		i;
	int		j;

	i = -1;
	while (++i, i < data->height)
	{
		j = -1;
		while (++j, j < data->row_width[i])
		{
			if (data->map[i][j] == 'W' || data->map[i][j] == 'N'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'S')
			{
				*x = j * TILE_SIZE;
				*y = i * TILE_SIZE;
				return (true);
			}
		}
	}
	return (false);
}
void	init_player(t_player *player, t_y3d *data)
{
	int		x;
	int		y;
	char	locate;

	if (set_x_y(data, &x, &y))
	{
		player->x = x;
		player->y = y;
		locate = data->map[y / TILE_SIZE][x / TILE_SIZE];
		printf("loca%c\n", data->map[y / TILE_SIZE][x / TILE_SIZE]);
		if (locate == 'N')
			player->angle = PI / 2;
		else if (locate == 'S')
			player->angle = 3 * PI / 2;
		else if (locate == 'E')
            player->angle = 0;
		else if (locate == 'W')
			player->angle = PI;
		printf("Player starting direction: %f radians\n", player->angle);
	}
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

bool	can_move_to_position(t_y3d *data, float y, float x)
{
	int	new_x;
	int	new_y;

	new_x = (int)x;
	new_y = (int)y;
	if (new_y < 0 || new_y >= data->height || new_x < 0
		|| new_x >= data->row_width[new_y])
		return (false);
	if (data->map[new_y][new_x] == '1')
		return (false);
	return (true);
}

void	player_move(t_player *player, t_y3d *data, float y_offset,
		float x_offset)
{
	float	new_x;
	float	new_y;

	new_x = x_offset + player->x;
	new_y = y_offset + player->y;
	if (can_move_to_position(data, new_y, new_x))
	{
		player->y = new_y;
		player->x = new_x;
	}
}

bool	touch(float px, float py, t_y3d *data)
{
	int	x;
	int	y;

	x = (px + 0.1) / TILE_SIZE;
	y = (py + 0.1) / TILE_SIZE;
	if (x < 0 || y < 0 || y >= data->height || x >= data->row_width[y])
		return (true);
	if (data->map[y][x] == '1')
		return (true);
	return (false);
}

void	move_if_valid(float new_x, float new_y, t_player *player, t_y3d *data)
{
	if (!touch(new_x, new_y, data))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	move_player(t_player *player, t_y3d *data)
{
	int		speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	speed = 5;
	angle_speed = 0.05;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
	if (player->key_up)
		move_if_valid(player->x + cos_angle * speed, player->y + sin_angle
			* speed, player, data);
	if (player->key_down)
		move_if_valid(player->x - cos_angle * speed, player->y - sin_angle
			* speed, player, data);
	if (player->key_left)
		move_if_valid(player->x + sin_angle * speed, player->y - cos_angle
			* speed, player, data);
	if (player->key_right)
		move_if_valid(player->x - sin_angle * speed, player->y + cos_angle
			* speed, player, data);
}
