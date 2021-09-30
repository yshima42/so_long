#include "../includes/so_long.h"

void	rectangular_check(char **map, t_conf *conf)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (y == 0)
				conf->map.width = ft_strlen(map[y]);
			if (conf->map.width != ft_strlen(map[y]))
			{
				printf("Map is not rectangular\n");
				map = ft_arrayfree(map);
				exit(EXIT_SUCCESS);
			}
		}
	}
}

//more than 25 lines
void	wall_check(char **map, t_conf *conf)
{	
	size_t	x;
	size_t	y;

	y = -1;
	while (map[++y])
	{
		if (y == 0 || y == conf->map.height - 1)
		{
			x = -1;
			while (map[y][++x])
			{
				if (map[y][x] != '1')
				{
					map = ft_arrayfree(map);
					printf("wall is not closed");
					exit(0);
				}
			}
		}
		else
		{
			if (map[y][0] != '1' || map[y][conf->map.width - 1] != '1')
			{
				map = ft_arrayfree(map);
				printf("wall is not closed");
				exit(0);
			}
		}
	}
}

//delete conf
void	invalid_char_check(char c, t_conf *conf)
{
	(void)conf;
	if (ft_strchr(VALID_CHAR, c) == NULL)
	{
		ft_putstr_fd("bad char", 2);
		exit(EXIT_SUCCESS);
	}
}

void	inmap_char_count(char c, t_conf *conf)
{
	if (c == 'C')
		conf->map.n_collectibles++;
	if (c == 'E')
		conf->map.n_exit++;
	if (c == 'P')
		conf->map.n_players++;
}

void	n_char_check(char **map, t_conf *conf)
{
	if (!conf->map.n_exit || conf->map.n_players != 1
		|| !conf->map.n_collectibles)
	{
		map = ft_arrayfree(map);
		printf("You need to have one P, some E, some C\n");
		exit(0);
	}
}
