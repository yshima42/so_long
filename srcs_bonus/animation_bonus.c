/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 00:21:10 by yshimazu          #+#    #+#             */
/*   Updated: 2021/10/03 00:21:16 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	ani_to_dis(int pos_y, int pos_x, char **map, t_conf *conf)
{
	void	*img_ptr;
	size_t	scroll_y;
	size_t	scroll_x;

	scroll_y = (conf->player.pos_y / SCREAN_SIZE) * SCREAN_SIZE;
	scroll_x = (conf->player.pos_x / SCREAN_SIZE) * SCREAN_SIZE;
	img_ptr = chr_to_imgptr(map[pos_y][pos_x], conf);
	mlx_put_image_to_window(conf->mlx, conf->win, img_ptr,
		CHIP_SIZE * (pos_x - scroll_x), CHIP_SIZE * (pos_y - scroll_y));
}

void	new_img_set(char *img_player, char *img_enemy, t_conf *conf)
{
	mlx_destroy_image(conf->mlx, conf->images.player);
	conf->images.player = mlx_xpm_file_to_image(conf->mlx, img_player,
			&conf->images.size, &conf->images.size);
	ani_to_dis(conf->player.pos_y, conf->player.pos_x, conf->map.map, conf);
	mlx_destroy_image(conf->mlx, conf->images.enemy);
	conf->images.enemy = mlx_xpm_file_to_image(conf->mlx, img_enemy,
			&conf->images.size, &conf->images.size);
	ani_to_dis(conf->enemy.pos_y, conf->enemy.pos_x, conf->map.map, conf);
}

int	animation(t_conf *conf)
{
	static int	count;

	count++;
	if (count == 10000)
		new_img_set(IMG_PLAYER, IMG_ENEMY_1, conf);
	else if (count == 20000)
		new_img_set(IMG_PLAYER_2, IMG_ENEMY_2, conf);
	if (count == 20000)
		count = 0;
	return (0);
}
