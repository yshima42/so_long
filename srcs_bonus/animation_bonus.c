//add header

#include "../includes/so_long_bonus.h"

void	animation_to_screan(char **map, t_conf *conf)
{
	void	*img_ptr;
	size_t	scroll_y;
	size_t	scroll_x;

	scroll_y = (conf->player.pos_y / SCREAN_SIZE) * SCREAN_SIZE;
	scroll_x = (conf->player.pos_x / SCREAN_SIZE) * SCREAN_SIZE;
	
	img_ptr = chr_to_imgptr(map[conf->player.pos_y][conf->player.pos_x], conf);
	mlx_put_image_to_window(conf->mlx, conf->win, img_ptr,
		CHIP_SIZE * (conf->player.pos_x - scroll_x), CHIP_SIZE * (conf->player.pos_y - scroll_y));
}

int	animation(t_conf *conf)
{
	static int count;
	
	count++;
	if (count <= 500)
	{
		conf->images.player = mlx_xpm_file_to_image(conf->mlx, IMG_PLAYER,
			&conf->images.size, &conf->images.size);
		animation_to_screan(conf->map.map, conf);
	}
	else if (count <= 1000)
	{
		conf->images.player = mlx_xpm_file_to_image(conf->mlx, IMG_PLAYER_2,
			&conf->images.size, &conf->images.size);
		animation_to_screan(conf->map.map, conf);
	}
	if (count == 1000)
		count = 0;
	return (0);
}