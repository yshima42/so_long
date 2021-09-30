/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:09:20 by yshimazu          #+#    #+#             */
/*   Updated: 2021/09/30 16:09:20 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	extension_check(char *filename)
{
	char	*dot_ptr;

	dot_ptr = ft_strchr(filename, '.');
	if (dot_ptr == NULL)
		return (-1);
	else
	{
		if (ft_strncmp(dot_ptr, ".ber", 4))
			return (-1);
	}
	return (0);
}

void	args_check(int ac, char **av)
{
	if (ac != 2 || extension_check(av[1]) == -1)
	{
		ft_putstr_fd("Error\nUsage: ./so_long xxx.ber", 2);
		exit (EXIT_SUCCESS);
	}
}
