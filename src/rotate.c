/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:24:05 by chansen           #+#    #+#             */
/*   Updated: 2017/02/27 19:24:07 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fdf.h"

void		rotxaxis(t_fdf *map, float rot)
{
	double			yd;
	double			zd;
	double			theta;
	int				x;
	int				y;

	map->rot.x += rot;
	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			yd = map->point[y][x].y - map->center.y;
			zd = map->point[y][x].z - map->center.z;
			theta = atan2(yd, zd) + rot;
			map->point[y][x].y = hypot(yd, zd) * sin(theta) + map->center.y;
			map->point[y][x].z = hypot(yd, zd) * cos(theta) + map->center.z;
			x++;
		}
		y++;
	}
}

void		rotyaxis(t_fdf *map, float rot)
{
	double			xd;
	double			zd;
	double			theta;
	int				x;
	int				y;

	map->rot.y += rot;
	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			xd = map->point[y][x].x - map->center.x;
			zd = map->point[y][x].z - map->center.z;
			theta = atan2(xd, zd) + rot;
			map->point[y][x].x = hypot(xd, zd) * sin(theta) + map->center.x;
			map->point[y][x].z = hypot(xd, zd) * cos(theta) + map->center.z;
			x++;
		}
		y++;
	}
}

void		spinz(t_fdf *map, float rot)
{
	double			xd;
	double			yd;
	double			theta;
	int				x;
	int				y;

	map->rot.z += rot;
	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			xd = map->point[y][x].x - map->center.x;
			yd = map->point[y][x].y - map->center.y;
			theta = atan2(yd, xd) + rot;
			map->point[y][x].x = hypot(xd, yd) * cos(theta) + map->center.x;
			map->point[y][x].y = hypot(xd, yd) * sin(theta) + map->center.y;
			x++;
		}
		y++;
	}
}

void		keycheck(t_fdf *map)
{
	if (map->key.w)
		rotxaxis(map, -0.05);
	else if (map->key.s)
		rotxaxis(map, 0.05);
	if (map->key.a)
		rotyaxis(map, -0.05);
	else if (map->key.d)
		rotyaxis(map, 0.05);
	if (map->key.q)
		spinz(map, -0.05);
	else if (map->key.e)
		spinz(map, 0.05);
	if (map->key.f)
		zoom(map, 1.1);
	else if (map->key.r)
		zoom(map, 0.9);
}

void		reset_rotation(t_fdf *map)
{
	map->rot.x *= -1;
	map->rot.y *= -1;
	map->rot.z *= -1;
	rotxaxis(map, map->rot.x);
	rotyaxis(map, map->rot.y);
	spinz(map, map->rot.z);
	map->rot.x = 0;
	map->rot.y = 0;
	map->rot.z = 0;
}
