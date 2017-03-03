/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:20:43 by chansen           #+#    #+#             */
/*   Updated: 2017/02/27 19:20:46 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fdf.h"

t_color		colorscaling(t_line line)
{
	t_color		pcolr;
	float		pd;
	float		hype;

	pd = sqrt(pow((line.x2 - line.x1), 2) + pow((line.y2 - line.y1), 2));
	if (pd < 0)
		pd *= -1;
	if (line.d == 0)
		return (line.c2);
	else if (pd / line.d >= 0.95)
		return (line.c1);
	else
		hype = (1 - (pd / line.d));
	pcolr.r = ((line.c2.r - line.c1.r) * hype);
	pcolr.g = ((line.c2.g - line.c1.g) * hype);
	pcolr.b = ((line.c2.b - line.c1.b) * hype);
	if (line.c2.r == line.c1.r)
		pcolr.r = line.c2.r;
	if (line.c2.g == line.c1.g)
		pcolr.g = line.c2.g;
	if (line.c2.b == line.c1.b)
		pcolr.b = line.c2.b;
	return (pcolr);
}

void		drawbline(t_fdf *map, t_line line)
{
	line.dx = abs(line.x2 - line.x1);
	line.dy = abs(line.y2 - line.y1);
	line.xi = line.x1 < line.x2 ? 1 : -1;
	line.yi = line.y1 < line.y2 ? 1 : -1;
	line.e = (line.dx > line.dy ? line.dx : -(line.dy)) / 2;
	while (!(line.x1 == line.x2 && line.y1 == line.y2))
	{
		put_image_pixel(map->image, line.x1, line.y1, colorscaling(line));
		line.etmp = line.e;
		if (line.etmp > -(line.dx))
		{
			line.e -= line.dy;
			line.x1 += line.xi;
		}
		if (line.etmp < line.dy)
		{
			line.e += line.dx;
			line.y1 += line.yi;
		}
	}
	put_image_pixel(map->image, line.x1, line.y1, colorscaling(line));
}

t_line		line(t_point p1, t_point p2, int setx, int sety)
{
	t_line		line;

	line.d = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
	if (line.d < 0)
		line.d *= -1;
	line.x1 = p1.x + setx;
	line.y1 = p1.y + sety;
	line.x2 = p2.x + setx;
	line.y2 = p2.y + sety;
	line.c1 = p1.color;
	line.c2 = p2.color;
	return (line);
}

void		drawimage(t_fdf *map)
{
	int			y;
	int			x;

	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			if (y != map->ylen - 1)
				drawbline(map, line(map->point[y][x], map->point[y + 1][x],
					setx(map->center.x), sety(map->center.y)));
			if (x != map->xlen - 1)
				drawbline(map, line(map->point[y][x], map->point[y][x + 1],
					setx(map->center.x), sety(map->center.y)));
			x++;
		}
		y++;
	}
}

void		fillimage(t_fdf *map)
{
	map->image.img = mlx_new_image(map->mlx, WIN_WDT, WIN_HGT);
	map->image.data = mlx_get_data_addr(map->image.img, &map->image.bits,
		&map->image.sizeline, &map->image.endian);
	map->image.height = WIN_HGT;
	map->image.width = WIN_WDT;
	map->center = find_center(map);
	drawimage(map);
}
