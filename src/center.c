/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:43:21 by chansen           #+#    #+#             */
/*   Updated: 2017/02/27 19:43:27 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fdf.h"

float		zmean(t_fdf *map)
{
	float		sum;
	int			d;
	int			x;
	int			y;

	sum = 0;
	d = 0;
	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			sum += map->point[y][x].z;
			d++;
			x++;
		}
		y++;
	}
	return (sum / (float)d);
}

float		ymean(t_fdf *map)
{
	float		sum;
	int			d;
	int			x;
	int			y;

	sum = 0;
	d = 0;
	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			sum += map->point[y][x].y;
			d++;
			x++;
		}
		y++;
	}
	return (sum / (float)d);
}

float		xmean(t_fdf *map)
{
	float		sum;
	int			d;
	int			x;
	int			y;

	sum = 0;
	d = 0;
	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			sum += map->point[y][x].x;
			d++;
			x++;
		}
		y++;
	}
	return (sum / (float)d);
}

t_point		find_center(t_fdf *map)
{
	return (make_point(xmean(map), ymean(map), zmean(map)));
}
