#include "../includes/so_long.h"

void	player_move(int keycode, t_conf *conf)
{
	int	x;
	int	y;

	x = conf->player.pos_x;
	y = conf->player.pos_y;
	if (keycode == W_KEY)
		step_to_next(&conf->map.map[y][x], &conf->map.map[y - 1][x], conf);
	if (keycode == A_KEY)
		step_to_next(&conf->map.map[y][x], &conf->map.map[y][x - 1], conf);
	if (keycode == S_KEY)
		step_to_next(&conf->map.map[y][x], &conf->map.map[y + 1][x], conf);
	if (keycode == D_KEY)
		step_to_next(&conf->map.map[y][x], &conf->map.map[y][x + 1], conf);
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

/* int complete_animation(t_conf *conf)
{
	int count;
	void *img_ptr;

	count = 0;
	ft_putchar_fd('a', 2);
	while (count < 1000)
	{
		count++;
		img_ptr = chr_to_imgptr(conf->map.map[conf->player.pos_y][conf->player.pos_x], conf);
		mlx_put_image_to_window(conf->mlx, conf->win, img_ptr, CHIP_SIZE * 1, CHIP_SIZE * 1);
	}
	return (0);
} */

void	game_complete(char *a, char *b, t_conf *conf)
{	
	if (conf->player.collectibles == conf->map.n_collectibles)
	{
		*b = *a;
		*a = '0';
		printf("Game Clear!!\n");
		//mlx_loop_hook(conf->mlx, complete_animation, conf);
		//conf->map.map = ft_arrayfree(conf->map.map);
		free_all_conf(conf);
		exit(0); //add complete effect and free
	}
}

void	step_to_next(char *current_pos, char *next_pos, t_conf *conf)
{
	if (next_pos_check(*next_pos, 'C') || next_pos_check(*next_pos, '0'))
		step_counter(conf);
	if (next_pos_check(*next_pos, 'C'))
		collect_item(current_pos, next_pos, conf);
	else if (next_pos_check(*next_pos, 'E'))
		game_complete(current_pos, next_pos, conf);
	else if (next_pos_check(*next_pos, '0'))
		ft_swap(current_pos, next_pos);
}
