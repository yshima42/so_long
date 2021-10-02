#include "../includes/so_long_bonus.h"

void	enemy_step_to_next(char *current_pos, char *next_pos, t_conf *conf)
{
	(void)conf;
	if (next_pos_check(*next_pos, '0'))
		ft_swap(current_pos, next_pos);
}

void	uni_move(int u_y, int u_x, t_conf *conf)
{
	int	dis_x;
	int	dis_y;

	dis_x = ABS(conf->player.pos_x - u_x);
	dis_y = ABS(conf->player.pos_y - u_y);
	if (dis_y > dis_x)
	{
		if ((conf->player.pos_y < u_y))
			enemy_step_to_next(&conf->map.map[u_y][u_x], &conf->map.map[u_y - 1][u_x], conf);
		else
			enemy_step_to_next(&conf->map.map[u_y][u_x], &conf->map.map[u_y + 1][u_x], conf);
	}
	else
	{
		if (conf->player.pos_x < u_x)
			enemy_step_to_next(&conf->map.map[u_y][u_x], &conf->map.map[u_y][u_x - 1], conf);
		else
			enemy_step_to_next(&conf->map.map[u_y][u_x], &conf->map.map[u_y][u_x + 1], conf);
	}
}

void	enemy_move(int e_y, int e_x, t_conf *conf)
{
	conf->player.n_clicks++;
	if (conf->player.n_clicks % 6 < 3)
		enemy_step_to_next(&conf->map.map[e_y][e_x], &conf->map.map[e_y + 1][e_x], conf);
	else
		enemy_step_to_next(&conf->map.map[e_y][e_x], &conf->map.map[e_y - 1][e_x], conf);
}