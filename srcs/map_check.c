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
				maperror_output(map, "Not rectangular or No first line in the file\n");
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
				if (map[y][x] != '1')
					maperror_output(map, "Wall is not closed\n");
		}
		else
			if (map[y][0] != '1' || map[y][conf->map.width - 1] != '1')
                maperror_output(map, "Wall is not closed\n");
	}
}

char	*invalid_char_check(char c, t_conf *conf)
{
	(void)conf;
	if (ft_strchr(VALID_CHAR, c) == NULL)
		return("Invalid charactor in the file\n");
    return (NULL);
}

char	*inmap_char_count(char c, t_conf *conf)
{
	if (c == 'C')
		conf->map.n_collectibles++;
	if (c == 'E')
		conf->map.n_exit++;
	if (c == 'P')
		conf->map.n_players++;
    return (NULL);
}

void	n_char_check(char **map, t_conf *conf)
{
	if (!conf->map.n_exit || conf->map.n_players != 1
		|| !conf->map.n_collectibles)
        maperror_output(map, "Need one P, some E, some C in the file\n");
}