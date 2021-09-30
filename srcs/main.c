/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:10:18 by yshimazu          #+#    #+#             */
/*   Updated: 2021/09/30 16:10:19 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* void    destructor_leaks(void)__attribute__((destructor));

void    destructor_leaks(void)
{
    system("leaks so_long | grep 'leaks for'");
} */

void	map_check(char **map, t_conf *conf)
{
	rectangular_check(map, conf);
	wall_check(map, conf);
	array_loop(map, conf, invalid_char_check);
	array_loop(map, conf, inmap_char_count);
	n_char_check(map, conf);
}

char	**map_set(char *mapfile, t_conf *conf)
{
	int		fd;
	t_list	*buf;
	char	**map;

	buf = NULL;
	fd = ft_open_readfile(mapfile);
	conf->map.height = file_to_lst(fd, &buf);
	map = lst_to_array(buf, conf->map.height, conf->map.map);
	return (map);
}

void	player_pos_check(char **map, t_conf *conf)
{
	int		y;
	int		x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'P')
			{
				conf->player.pos_y = y;
				conf->player.pos_x = x;
			}
		}
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
	array_to_screan(conf->map.map, conf);
	return (0);
}

void	desplay_mlx(t_conf *conf)
{
	conf->mlx = mlx_init();
	if (!conf->mlx)
		free_all_exit(conf);
	chip_set(conf);
	conf->win = mlx_new_window(conf->mlx, SCREAN_SIZE * CHIP_SIZE,
			SCREAN_SIZE * CHIP_SIZE, "so_long");
	if (!conf->mlx)
		free_all_exit(conf);
	array_to_screan(conf->map.map, conf);
}

void	hook_loop_mlx(t_conf *conf)
{
	mlx_hook(conf->win, 2, 1L << 0, key_hook, conf);
	mlx_hook(conf->win, 33, 1L << 17, free_all_exit, conf);
	mlx_loop(conf->mlx);
}

int	main(int ac, char **av)
{
	t_conf	conf;

	args_check(ac, av);
	initialize_conf(&conf);
	conf.map.map = map_set(av[1], &conf);
	map_check(conf.map.map, &conf);
	player_pos_check(conf.map.map, &conf);
	desplay_mlx(&conf);
	hook_loop_mlx(&conf);
}
