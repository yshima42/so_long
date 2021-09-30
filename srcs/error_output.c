/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:08:59 by yshimazu          #+#    #+#             */
/*   Updated: 2021/09/30 16:09:13 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	maperror_output(char **map, char *output)
{
	map = ft_arrayfree(map);
	ft_putstr_fd("Error\nMap: ", 2);
	ft_putstr_fd(output, 2);
	exit(EXIT_SUCCESS);
}

void	perror_exit(char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}