/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 09:35:39 by chansen           #+#    #+#             */
/*   Updated: 2017/02/28 09:35:40 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fdf.h"

void		xy_scale(t_fdf *map, float scale)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			map->point[y][x].x *= scale;
			map->point[y][x].y *= scale;
			x++;
		}
		y++;
	}
}

void		z_scale(t_fdf *map, float scale)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			map->point[y][x].z *= scale;
			x++;
		}
		y++;
	}
}

void		scale(t_fdf *map, float xy, float z)
{
	xy_scale(map, xy);
	z_scale(map, z);
}

void		zoom(t_fdf *map, float zoom)
{
	xy_scale(map, zoom);
	z_scale(map, zoom);
}
