/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong_leakcheck.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimazu <yshimazu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:52:27 by yshimazu          #+#    #+#             */
/*   Updated: 2021/09/30 16:13:54 by yshimazu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void    destructor_leaks(void)__attribute__((destructor));

void    destructor_leaks(void)
{
    system("leaks so_long | grep 'leaks for'");
}