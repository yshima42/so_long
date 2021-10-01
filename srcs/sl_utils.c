/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:13:50 by yshimazu          #+#    #+#             */
/*   Updated: 2021/09/30 16:16:40 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	*chr_to_imgptr(char c, t_conf *conf)
{
	if (c == '0')
		return (conf->images.empty);
	else if (c == '1')
		return (conf->images.wall);
	else if (c == 'C')
		return (conf->images.collectible);
	else if (c == 'E')
		return (conf->images.exit);
	else if (c == 'P')
		return (conf->images.player);
	else
	{
		ft_putstr_fd("You cannot come here!!", 2);
		free_all_exit(conf);
		return (NULL);
	}
}

void	array_to_screan(char **map, t_conf *conf)
{
	void	*img_ptr;
	size_t	y;
	size_t	x;
	size_t	scroll_y;
	size_t	scroll_x;

	mlx_clear_window(conf->mlx, conf->win);
	scroll_y = (conf->player.pos_y / SCREAN_SIZE) * SCREAN_SIZE;
	scroll_x = (conf->player.pos_x / SCREAN_SIZE) * SCREAN_SIZE;
	y = 0;
	while (map[y + scroll_y])
	{
		x = 0;
		while (map[y + scroll_y][x + scroll_x]) // error handring player only be one
		{
			img_ptr = chr_to_imgptr(map[y + scroll_y][x + scroll_x], conf);
			mlx_put_image_to_window(conf->mlx, conf->win, img_ptr,
				CHIP_SIZE * x, CHIP_SIZE * y);
			x++;
		}
		y++;
	}
}

void	chip_set(t_conf *conf)
{
	conf->images.empty = mlx_xpm_file_to_image(conf->mlx, IMG_EMPTY,
			&conf->images.size, &conf->images.size);
	if (!conf->images.empty)
		free_all_exit(conf);
	conf->images.wall = mlx_xpm_file_to_image(conf->mlx, IMG_WALL,
			&conf->images.size, &conf->images.size);
	if (!conf->images.wall)
		free_all_exit(conf);
	conf->images.collectible = mlx_xpm_file_to_image(conf->mlx, IMG_COLLECTIBLE,
			&conf->images.size, &conf->images.size);
	if (!conf->images.collectible)
		free_all_exit(conf);
	conf->images.exit = mlx_xpm_file_to_image(conf->mlx, IMG_EXIT,
			&conf->images.size, &conf->images.size);
	if (!conf->images.exit)
		free_all_exit(conf);
	conf->images.player = mlx_xpm_file_to_image(conf->mlx, IMG_PLAYER,
			&conf->images.size, &conf->images.size);
	if (!conf->images.player)
		free_all_exit(conf);
}

void	initialize_conf(t_conf *conf)
{
	//ayashii??
	conf->mlx = NULL;
	conf->win = NULL;
	conf->map.map = NULL;
	conf->map.width = 0;
	conf->map.height = 0;
	conf->map.n_collectibles = 0;
	conf->map.n_players = 0;
	conf->map.n_exit = 0;
	conf->images.empty = NULL;
	conf->images.wall = NULL;
	conf->images.collectible = NULL;
	conf->images.exit = NULL;
	conf->images.player = NULL;
	conf->images.size = CHIP_SIZE;
	conf->player.pos_y = 0;
	conf->player.pos_x = 0;
	conf->player.n_steps = 0;
	conf->player.collectibles = 0;
}

void	step_counter(t_conf *conf)
{
	conf->player.n_steps++;
	printf("Number of steps: %ld\n", conf->player.n_steps);
	if (conf->player.n_steps > SIZE_MAX)
	{
		ft_putstr_fd("Game Over: You walked way too much!!\n", 2);
		free_all_exit(conf);
	}
}
