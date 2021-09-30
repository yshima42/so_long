#include "../includes/so_long.h"

char	**ft_arrayfree(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	return (NULL);
}

void	free_all_conf(t_conf *conf)
{
	if (conf->map.map)
		conf->map.map = ft_arrayfree(conf->map.map);
	if (conf->images.empty)
		mlx_destroy_image(conf->mlx, conf->images.empty);
	if (conf->images.wall)
		mlx_destroy_image(conf->mlx, conf->images.wall);
	if (conf->images.collectible)
		mlx_destroy_image(conf->mlx, conf->images.collectible);
	if (conf->images.exit)
		mlx_destroy_image(conf->mlx, conf->images.exit);
	if (conf->images.player)
		mlx_destroy_image(conf->mlx, conf->images.player);
	if (conf->win)
		mlx_destroy_window(conf->mlx, conf->win);
	if (conf->mlx)
	{
		mlx_destroy_display(conf->mlx);
		free(conf->mlx);
		conf->mlx = NULL;
	}
}
