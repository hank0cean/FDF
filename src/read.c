/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:20:28 by chansen           #+#    #+#             */
/*   Updated: 2017/02/27 19:20:32 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fdf.h"

t_color		make_color(int hex)
{
	t_color color;

	if (hex == 0)
	{
		color.r = 255;
		color.g = 255;
		color.b = 255;
		return (color);
	}
	color.r = hex & 0xFF;
	color.g = (hex >> 8) & 0xFF;
	color.b = (hex >> 16) & 0xFF;
	return (color);
}

t_point		make_point(float x, float y, float z)
{
	t_point		point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

int			rowcheck(t_fdf *map, char **r, int *y)
{
	int		gx;
	int		i;

	gx = 0;
	while (r[gx] != NULL)
	{
		i = 0;
		if (ft_isdigit(r[gx][i]) == 1)
			map->point[*y][gx] = make_point(gx, *y, ft_getnbr(r[gx], &i));
		if (r[gx][i] == ',')
		{
			i++;
			map->point[*y][gx].color = make_color(ft_getnbr(r[gx], &i));
		}
		else
			map->point[*y][gx].color = make_color(0);
		if (r[gx][i] != '\0')
			return (0);
		if (r[gx][i] == '\0')
			(gx)++;
	}
	if (!map->xlen || map->xlen == gx)
		return (1);
	return (0);
}

int			rdin(int fd, t_fdf *map)
{
	char	*line;
	char	*row;
	int		rlen;
	int		y;

	rlen = 0;
	y = 0;
	line = ft_strdup("");
	while (get_next_line(fd, &row) == 1)
	{
		if (y == 0)
			map->xlen = countwords(row);
		else if (map->xlen != countwords(row))
			return (0);
		line = ft_strjoin(ft_strjoin(line, "\n"), row);
		ft_strdel(&row);
		y++;
	}
	map->read = ft_strdup(line);
	ft_strdel(&line);
	y < 2 ? 0 : (map->ylen = y);
	map->point = (t_point**)malloc(sizeof(t_point*) * map->ylen);
	while (y >= 0)
		map->point[y--] = (t_point*)malloc(sizeof(t_point) * map->xlen);
	return (1);
}

int			chknflla(int fd, t_fdf *map)
{
	char	**lines;
	int		y;

	y = 0;
	if (rdin(fd, map) == 0)
		return (0);
	lines = ft_strsplit(map->read, '\n');
	ft_strdel(&map->read);
	while (y < map->ylen)
	{
		if (rowcheck(map, ft_strsplit(lines[y], ' '), &y) != 1)
			return (err_msg("error\n"));
		y++;
	}
	if (!(map->mlx = mlx_init()))
		return (err_msg("mlx_error\n"));
	map->win = mlx_new_window(map->mlx, WIN_WDT, WIN_HGT, "FDF - chansen");
	zero_out(map);
	return (1);
}
