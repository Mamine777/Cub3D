/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokariou <mokariou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:40:23 by mokariou          #+#    #+#             */
/*   Updated: 2025/01/30 17:15:31 by mokariou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../y3d.h"

int	key_press(int keycode, t_player *player)
{
	printf("%d\n", keycode);
	if (keycode == ESC_KEY)
		exit(0);
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
	int i;
	int j;

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->row_width[i])
		{
			if (data->map[i][j] == 'W' || data->map[i][j] == 'N'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'S')
			{
				*x = j;
				*y = i;
				return (true);
			}
		}
	}
	return (false);
}

void	init_player(t_player *player, t_y3d *data)
{
	int x, y;
	char locate;

	if (set_x_y(data, &x, &y))
	{
		player->x = (double)x + 0.5;
		player->y = (double)y + 0.5;

		locate = data->map[y][x];
		if (locate == 'E')
		{
			player->dirX = 1;
			player->dirY = 0;
			player->planeX = 0;
			player->planeY = 0.66;
		}
		else if (locate == 'W')
		{
			player->dirX = -1;
			player->dirY = 0;
			player->planeX = 0;
			player->planeY = -0.66;
		}
		else if (locate == 'S')
		{
			player->dirX = 0;
			player->dirY = 1;
			player->planeX = -0.66;
			player->planeY = 0;
		}
		else if (locate == 'N')
		{
			player->dirX = 0;
			player->dirY = -1;
			player->planeX = 0.66;
			player->planeY = 0;
		}
	}
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

bool can_move_to_position(t_y3d *data, float y, float x)
{
	int new_x;
	int new_y;

	new_x = (int)(x);
	new_y = (int)(y);

	if (new_y < 0 || new_y >= data->height || new_x < 0
		|| new_x >= data->row_width[new_y] || data->map[new_y][new_x] == '1')
		return (false);
	return (true);
}

void move_if_valid(float new_x, float new_y, t_player *player, t_y3d *data)
{
	if (can_move_to_position(data, new_y, new_x))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void move_player(t_player *player, t_y3d *data)
{
	double speed;
	double angle_speed;
	double oldDirX;
	double oldPlaneX;

	speed = 0.111;
	angle_speed = 0.1;
	if (player->left_rotate)
	{
		oldDirX = player->dirX;
		player->dirX = player->dirX * cos(-angle_speed) - player->dirY * sin(-angle_speed);
		player->dirY = oldDirX * sin(-angle_speed) + player->dirY * cos(-angle_speed);
		oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(-angle_speed) - player->planeY * sin(-angle_speed);
		player->planeY = oldPlaneX * sin(-angle_speed) + player->planeY * cos(-angle_speed);
	}
	if (player->right_rotate)
	{
		oldDirX = player->dirX;
		player->dirX = player->dirX * cos(angle_speed) - player->dirY * sin(angle_speed);
		player->dirY = oldDirX * sin(angle_speed) + player->dirY * cos(angle_speed);
		oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(angle_speed) - player->planeY * sin(angle_speed);
		player->planeY = oldPlaneX * sin(angle_speed) + player->planeY * cos(angle_speed);
	}

	if (player->key_up)
		move_if_valid(player->x + player->dirX * speed, player->y + player->dirY * speed, player, data);
	if (player->key_down)
		move_if_valid(player->x - player->dirX * speed, player->y - player->dirY * speed, player, data);
	if (player->key_left)
		move_if_valid(player->x - player->planeX * speed, player->y - player->planeY * speed, player, data);
	if (player->key_right)
		move_if_valid(player->x + player->planeX * speed, player->y + player->planeY * speed, player, data);
}
