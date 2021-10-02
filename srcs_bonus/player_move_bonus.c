/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:13:46 by yshimazu          #+#    #+#             */
/*   Updated: 2021/09/30 16:13:47 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	enemy_step_to_next(char *current_pos, char *next_pos, t_conf *conf)
{
	(void)conf;
	if (next_pos_check(*next_pos, '0'))
		ft_swap(current_pos, next_pos);
}

void	uni_move(int u_y, int u_x, t_conf *conf)
{
	if (conf->player.n_clicks % 6 < 3)
		enemy_step_to_next(&conf->map.map[u_y][u_x], &conf->map.map[u_y + 1][u_x], conf);
	else
		enemy_step_to_next(&conf->map.map[u_y][u_x], &conf->map.map[u_y - 1][u_x], conf);
}

void	enemy_move(int e_y, int e_x, t_conf *conf)
{
	conf->player.n_clicks++;
	if (conf->player.n_clicks % 6 < 3)
		enemy_step_to_next(&conf->map.map[e_y][e_x], &conf->map.map[e_y + 1][e_x], conf);
	else
		enemy_step_to_next(&conf->map.map[e_y][e_x], &conf->map.map[e_y - 1][e_x], conf);
}

void	player_move(int keycode, t_conf *conf)
{
	int	p_x;
	int	p_y;
	int	e_x;
	int	e_y;
	int	u_x;
	int	u_y;

	p_x = conf->player.pos_x;
	p_y = conf->player.pos_y;
	e_x = conf->enemy.pos_x;
	e_y = conf->enemy.pos_y;
	u_x = conf->uni.pos_x;
	u_y = conf->uni.pos_y;
	if (keycode == W_KEY || keycode == A_KEY || keycode == S_KEY || keycode == D_KEY)
	{
		enemy_move(e_y, e_x, conf);
		uni_move(u_y, u_x, conf);
	}
	if (keycode == W_KEY)
		step_to_next(&conf->map.map[p_y][p_x], &conf->map.map[p_y - 1][p_x], conf);
	if (keycode == A_KEY)
		step_to_next(&conf->map.map[p_y][p_x], &conf->map.map[p_y][p_x - 1], conf);
	if (keycode == S_KEY)
		step_to_next(&conf->map.map[p_y][p_x], &conf->map.map[p_y + 1][p_x], conf);
	if (keycode == D_KEY)
		step_to_next(&conf->map.map[p_y][p_x], &conf->map.map[p_y][p_x + 1], conf);
}

int	next_pos_check(char next_pos_c, char check_c)
{
	if (next_pos_c == check_c)
		return (1);
	else
		return (0);
}

void	collect_item(char *a, char *b, t_conf *conf)
{
	*b = *a;
	*a = '0';
	conf->player.collectibles++;
}

void	game_finish_animation(char *img1, char *img2, t_conf *conf)
{
	int	count;
	int	n_while;
	
	n_while = 0;
	while(n_while++ < 4)
	{
		count = 0;
		while (count++ < 2000)
		{
			conf->images.player = mlx_xpm_file_to_image(conf->mlx, img1,
				&conf->images.size, &conf->images.size);
			animation_to_screan(conf->map.map, conf);
			if (!(conf->player.pos_y % SCREAN_SIZE) || !(conf->player.pos_x % SCREAN_SIZE))
				mlx_clear_window(conf->mlx, conf->win);
		}
		while (count++ < 4000)
		{
			conf->images.player = mlx_xpm_file_to_image(conf->mlx, img2,
				&conf->images.size, &conf->images.size);
			animation_to_screan(conf->map.map, conf);
		}
	}
}

void	game_complete(char *a, char *b, t_conf *conf)
{	
	if (conf->player.collectibles == conf->map.n_collectibles)
	{
		*b = *a;
		*a = '0';
		char_pos_check(conf->map.map, conf);
		array_to_screan(conf->map.map, conf);
		game_finish_animation(IMG_PLAYER_5, IMG_PLAYER, conf);
		ft_putstr_fd("Game Clear!!\n", 1);
		free_all_exit(conf);
	}
}

void	game_over(char *a, char *b, t_conf *conf)
{	
	*b = *a;
	*a = '0';
	char_pos_check(conf->map.map, conf);
	array_to_screan(conf->map.map, conf);
	game_finish_animation(IMG_PLAYER_3, IMG_PLAYER_4, conf);
	ft_putstr_fd("Game Over: You hit an enemy!!\n", 1);
	free_all_exit(conf);
}

void	step_to_next(char *current_pos, char *next_pos, t_conf *conf)
{
	if (next_pos_check(*next_pos, 'C') || next_pos_check(*next_pos, '0'))
		step_counter(conf);
	if (next_pos_check(*next_pos, 'C'))
		collect_item(current_pos, next_pos, conf);
	else if (next_pos_check(*next_pos, 'E'))
		game_complete(current_pos, next_pos, conf);
	else if (next_pos_check(*next_pos, 'T'))
		game_over(current_pos, next_pos, conf);
	else if (next_pos_check(*next_pos, 'U'))
		game_over(current_pos, next_pos, conf);
	else if (next_pos_check(*next_pos, '0'))
		ft_swap(current_pos, next_pos);
}
