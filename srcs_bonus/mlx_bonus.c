/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 22:03:22 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/01 22:04:08 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	array_to_screan(char **map, t_conf *conf)
{
	void	*img_ptr;
	size_t	y;
	size_t	x;
	size_t	scroll_y;
	size_t	scroll_x;

	scroll_y = (conf->player.pos_y / SCREAN_SIZE) * SCREAN_SIZE;
	scroll_x = (conf->player.pos_x / SCREAN_SIZE) * SCREAN_SIZE;
	y = 0;
	while (map[y + scroll_y])
	{
		x = 0;
		while (map[y + scroll_y][x + scroll_x])
		{
			img_ptr = chr_to_imgptr(map[y + scroll_y][x + scroll_x], conf);
			mlx_put_image_to_window(conf->mlx, conf->win, img_ptr,
				CHIP_SIZE * x, CHIP_SIZE * y);
			x++;
		}
		y++;
	}
}

int	key_hook(int keycode, t_conf *conf)
{
	if (keycode == W_KEY || keycode == A_KEY
		|| keycode == S_KEY || keycode == D_KEY)
		player_move(keycode, conf);
	if (keycode == ESC_KEY)
		free_all_exit(conf);
	player_pos_check(conf->map.map, conf);
	if (!(conf->player.pos_y % SCREAN_SIZE) || !(conf->player.pos_x % SCREAN_SIZE))
		mlx_clear_window(conf->mlx, conf->win);
	array_to_screan(conf->map.map, conf);
	return (0);
}

void	desplay_mlx(t_conf *conf)
{
	conf->mlx = mlx_init();
	if (!conf->mlx)
		error_mlx(conf);
	chip_set(conf);
	conf->win = mlx_new_window(conf->mlx, SCREAN_SIZE * CHIP_SIZE,
			SCREAN_SIZE * CHIP_SIZE, "so_long");
	if (!conf->mlx)
		error_mlx(conf);
	array_to_screan(conf->map.map, conf);
}

void	hook_loop_mlx(t_conf *conf)
{
	mlx_hook(conf->win, 2, 1L << 0, key_hook, conf);
	mlx_hook(conf->win, 33, 1L << 17, free_all_exit, conf);
	mlx_loop(conf->mlx);
}
