/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:24:36 by chansen           #+#    #+#             */
/*   Updated: 2017/02/27 19:24:38 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fdf.h"

int			err_msg(char *str)
{
	ft_putstr(str);
	return (0);
}

void		zero_out(t_fdf *map)
{
	map->key.w = 0;
	map->key.s = 0;
	map->key.a = 0;
	map->key.d = 0;
	map->key.q = 0;
	map->key.e = 0;
	map->key.r = 0;
	map->key.f = 0;
	map->rot.x = 0;
	map->rot.y = 0;
	map->rot.z = 0;
}

int			setx(float centerx)
{
	return ((WIN_WDT / 2) - centerx);
}

int			sety(float centery)
{
	return ((WIN_HGT / 2) - centery);
}
