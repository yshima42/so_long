/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:10:30 by yshimazu          #+#    #+#             */
/*   Updated: 2021/09/30 16:13:39 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	rectangular_check(char **map, t_conf *conf)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][++x])
		{
			if (y == 0)
				conf->map.width = ft_strlen(map[y]);
			if (conf->map.width > INT32_MAX)
				maperror_output(map, "Map is too big\n");
			if (conf->map.width != ft_strlen(map[y]))
				maperror_output(map,
					"Not rectangular or No first line in the file\n");
			x++;
		}
		y++;
	}
}

//more than 25 lines
void	wall_check(char **map, t_conf *conf)
{	
	size_t	x;
	size_t	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		if (y == 0 || y == conf->map.height - 1)
		{
			while (map[y][x])
			{
				if (map[y][x] != '1')
					maperror_output(map, "Wall is not closed\n");
			x++;
			}
		}
		else
			if (map[y][0] != '1' || map[y][conf->map.width - 1] != '1')
				maperror_output(map, "Wall is not closed\n");
		y++;
	}
}

char	*invalid_char_check(char c, t_conf *conf)
{
	(void)conf;
	if (ft_strchr(VALID_CHAR, c) == NULL)
		return ("Invalid charactor in the file\n");
	else
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
	if (conf->map.n_collectibles > SIZE_MAX || conf->map.n_exit > SIZE_MAX)
		return ("Too many C or E");
	else
		return (NULL);
}

void	n_char_check(char **map, t_conf *conf)
{
	if (!conf->map.n_exit || conf->map.n_players != 1
		|| !conf->map.n_collectibles)
		maperror_output(map,
			"Need one P, more than one E, more than one C in the file\n");
}
