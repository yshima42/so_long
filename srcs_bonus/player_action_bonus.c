#include "../includes/so_long_bonus.h"

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
	while(n_while++ < 5)
	{
		count = 0;
		while (count++ < 2000)
		{
			conf->images.player = mlx_xpm_file_to_image(conf->mlx, img1,
				&conf->images.size, &conf->images.size);
			animation_to_screan(conf->player.pos_y, conf->player.pos_x, conf->map.map, conf);
			if (!(conf->player.pos_y % SCREAN_SIZE) || !(conf->player.pos_x % SCREAN_SIZE))
				mlx_clear_window(conf->mlx, conf->win);
		}
		while (count++ < 4000)
		{
			conf->images.player = mlx_xpm_file_to_image(conf->mlx, img2,
				&conf->images.size, &conf->images.size);
			animation_to_screan(conf->player.pos_y, conf->player.pos_x, conf->map.map, conf);
		}
	}
}