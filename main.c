/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 11:01:42 by chansen           #+#    #+#             */
/*   Updated: 2017/01/27 15:13:38 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		err_msg(char *str)
{
	ft_putstr(str);
	return (0);
}

int		countwords(char *str)
{
	unsigned int	i;
	unsigned int	words;

	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

// int		countlines(int fd)
// {
// 	char			*str;
// 	unsigned long	i;
//
// 	i = 0;
// 	while (get_next_line(fd, &str) == 1)
// 	{
// 		i++;
// 		ft_strdel(&str);
// 	}
// 	return (i);
// }

void	set3to0(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

void	set4to0(int *a, int *b, int *c, int *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

//	FT_ISHEXASCII   &&   FT_ISBINARY

int		ft_ishexascii(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))
		return (1);
	else
		return (0);
}

int		ft_isbinary(char c)
{
	if (c == '1' || c == '0')
		return (1);
	else
		return (0);
}


//  GETNBR

#include <stdio.h>

static int  gethexnbr(char *str, int *i)
{
  int   nbr;

  nbr = 0;
  while (ft_ishexascii(str[(*i)]) == 1)
  {
    nbr *= 16;
    if (ft_isdigit(str[(*i)]) == 1)
      nbr += (str[(*i)] - 48);
    else if (str[(*i)] >= 'a' && str[(*i)] <= 'f')
      nbr += (str[(*i)] - 87);
    else if (str[(*i)] >= 'A' && str[(*i)] <= 'F')
      nbr += (str[(*i)] - 55);
    (*i)++;
  }
  return (nbr);
}

static int  getbinnbr(char *str, int *i)
{
  int    nbr;

  nbr = 0;
  while (ft_isbinary(str[(*i)]) == 1)
  {
    nbr *= 2;
    nbr += (str[(*i)++] - 48);
  }
  return (nbr);
}


int         getnbr(char *str, int *i)
{
  int     nbr;

  nbr = 0;
  if (str[(*i)] == '0' && str[(*i) + 1] == 'x' && ft_ishexascii(str[(*i) + 2]))
	{
		*i += 2;
    return (gethexnbr(str, i));
	}
	else if (str[(*i)] == '0' && str[(*i) + 1] == 'b' && str[(*i) + 2])
	{
		*i += 2;
    return (getbinnbr(str, i));
	}
	while (ft_isdigit(str[(*i)]) == 1)
  {
    nbr *= 10;
    nbr += (str[(*i)++] - 48);
  }
  return (nbr);
}











































t_point		make_point(float x, float y, float z)
{
	t_point		point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}



int		rowcheck(t_fdf *map, char **r, int *y)
{
	int		gx;
	int		i;

	gx = 0;
	while (r[gx] != NULL)
	{
		i = 0;
		if (ft_isdigit(r[gx][i]) == 1)
			map->point[*y][gx] = make_point(gx, *y, getnbr(r[gx], &i));
		if (r[gx][i] == ',')
		{
			i++;
			map->point[*y][gx].color = getnbr(r[gx], &i);
		}
		if (r[gx][i] != '\0')
			return (0);
		if (r[gx][i] == '\0')
			(gx)++;
	}
	if (!map->xlen || map->xlen == gx)
		return (1);
	return (0);
}



int		countcol(char **grid)
{
	unsigned int		y;

	y = 0;
	while (grid[y] != NULL)
		y++;
	return (y);
}

int		rdin(int fd, t_fdf *map)
{
	char 	*line;
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
		line = ft_strjoin(line, "\n");
		line = ft_strjoin(line, row);
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

		// Means VVVVV

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

// Find Center VVVVVVVVV

t_point	find_center(t_fdf *map)
{
		return(make_point(xmean(map), ymean(map), zmean(map)));
}

void key0(t_fdf *map)
{
	map->key.w = 0;
	map->key.s = 0;
	map->key.a = 0;
	map->key.d = 0;
	map->key.q = 0;
	map->key.e = 0;
	map->key.r = 0;
	map->key.f = 0;
}

int		chknflla(int fd, t_fdf *map)
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
				return (0);
		y++;
	}
	if (!(map->mlx = mlx_init()))
		return (err_msg("error\n"));
	map->win = mlx_new_window(map->mlx, WIN_WDT, WIN_HGT, "Im LOrDE");
	key0(map);
	return (1);
}

//  Keypress/Keyrelease  VVVVVVVVV

int			key_press_hook(int key, t_fdf *map)
{
	printf("key_press: %i\n", key);
	if (key == 13)
		map->key.w = 1;
	if (key == 0)
		map->key.a = 1;
	if (key == 1)
		map->key.s = 1;
	if (key == 2)
		map->key.d = 1;
	if (key == 12)
		map->key.q = 1;
	if (key == 14)
		map->key.e = 1;
	if (key == 15)
		map->key.r = 1;
	if (key == 3)
		map->key.f = 1;
	return (key);
}

int			key_release_hook(int key, t_fdf *map)
{
	printf("key_release: %i\n\n", key);
	if (key == 53)
	{
		mlx_destroy_window(map->mlx, map->win);
		exit(0);
	}
	if (key == 13)
		map->key.w = 0;
	if (key == 0)
		map->key.a = 0;
	if (key == 1)
		map->key.s = 0;
	if (key == 2)
		map->key.d = 0;
	if (key == 12)
		map->key.q = 0;
	if (key == 14)
		map->key.e = 0;
	if (key == 15)
		map->key.r = 0;
	if (key == 3)
		map->key.f = 0;
	return (key);
}

 // XYZ Scaling VVVVVVVVV

void xy_scale(t_fdf *map, float scale)
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

void z_scale(t_fdf *map, float scale)
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

void scale(t_fdf *map, float xy, float z)
{
	xy_scale(map, xy);
	z_scale(map, z);
}

// Rotations VVVVVVVV

void rotxaxis(t_fdf *map, float	rot)
{
	double			yd;
	double			zd;
	double			d;
	double			theta;
	int					x;
	int					y;

	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < xlen)
		{
			yd = map->point[y][x].y - map->center.y;
			zd = map->point[y][x].z - map->center.z;
			d = hypot(yd, zd);
			theta = atan2(yd, zd) + rot;
			map->point[y][x].y = d * sin(theta) + map->center.y;
			map->point[y][x].z = d * cos(theta) + map->center.z;
			x++;
		}
		y++;
	}
}

void rotyaxis(t_fdf *map, float rot)
{
	double			xd;
	double			zd;
	double			d;
	double			theta;
	int					x;
	int					y;

	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			xd = map->point[y][x].x - map->center.x;
			zd = map->point[y][x].z - map->center.z;
			d = hypot(xd, yd);
			theta = atan2(xd, yd) + rot; //adjusted angle of rotation around y axis
			map->point[y][x].x = d * cos(theta) + map->center.x; //(hypot * new angle) = x (floa†ing point around center) + mapcenter
			map->point[y][x].z = d * sin(theta) + map->center.z;
			x++;
		}
	}
}

void spinz(t_fdf *map, float rot)
{
	double			xd;
	double			yd;
	double			d;
	double			theta;
	int					x;
	int					y;

	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			xd = map->point[y][x].x - map->center.x;
			yd = map->point[y][x].y - map->center.y;
			d = hypot(xd, yd);
			theta = atan2(xd, yd) + rot;
			map->point[y][x].x = d * cos(theta) + map->center.x;
			map->point[y][x].x = d * sin(theta) + map->center.y;
			x++;
		}
		y++;
	}
}
//
// void zoom(t_fdf *map, float zoom)
// {
//
// }

int			keycheck(t_fdf *map)
{
	//Rotation matrices applied to (x,y,z) when keys are on
	if (map->key.w)
		rotxaxis(map, -0.01);
	else if (map->key.s)
		rotxaxis(map, 0.01);
	if (map->key.a)
		rotyaxis(map, -0.01);
	else if (map->key.d)
		rotyaxis(map, 0.01);
	if (map->key.q)
		spinz(map, -0.01);
	else if (map->key.e)
		spinz(map, 0.01);

// 	// Z00M Z00M VV
//
// 	if (map->key.f)
// 		zoom(map, 1.1);
// 	else if (map->key.r)
// 		zoom(map, 0.9);

}

int			setx(float centerx);
{
	return ((WIN_WDT / 2) - centerx);
}

int			sety(float centery)
{
	return ((WIN_HGT / 2) - centery);
}

void 		put_image_pixel(t_img image, int x, int y, int color)
{
	int		b;

	if (x >= image.width || y >= image.height)
		return ;
	b = (4 * x) + (y * image.sizeline);
	image.data[b++] = color & 0xFF;
	iamge.data[b++] = (color >> 8) & 0xFF;
	image.data[b]		= (color >> 16) & 0xFF;
}

void 		drawline(t_fdf *map, t_line line)
{
	line.dx = abs(line.x2 - line.x1);
	line.dy = abs(line.y2 - line.y1);
	line.xi = line.x1 < line.x2 ? 1 : -1;
	line.yi = line.y1 < line.y2 ? 1 : -1;
	line.e = (line.dx > line.dy ? line.dx : -(line.dy)) / 2;
	while (line.x1 != line.x2 && line.y1 != line.y2)
	{
		put_image_pixel(map->image, line.x1, line.y1, 0xFF0000);
		line.etmp = e;
		if (line.etmp > -(line.dx))
		{
			line.e -= line.dy;
			line.x1 += line.xi;
		}
		if (line.etmp < line.dy)
		{
			line.e += line.dy;
			line.y1 += line.yi;
		}
	}
	put_image_pixel(map->image, line.x1, line.y1, 0xFF0000);
}

t_line	line(t_point p1, t_point p2, int setx, int sety)
{
	t_line		line;

	line.x1 = p1.x + setx;
	line.y1 = p1.y + sety;
	line.x2 = p2.x + setx;
	line.y2 = p2.y + sety;
	return (line);
}

void 		drawimage(t_fdf *map)
{
	int			y;
	int			x;

	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			if (y != map->ylen)
				drawline(map, line(map->point[y][x], map->point[y + 1][x],
					setx(map->center.x), sety(map->center.y)));
			if (x != map->xlen)
				drawline(map, line(map->point[y][x], map->point[y][x + 1],
					setx(map->center.x), sety(map->center.y)));
			x++;
		}
		y++;
	}
}

void			fillimage(t_fdf *map)
{
	map->image.img = mlx_new_image(map->mlx, WIN_WDT, WIN_HGT);
	map->image.data = mlx_get_data_addr(map->image.img, &map->image.bits,
		&map->image.sizeline, &map->image.endian);
	map->image.height = WIN_HGT;
	map->image.width = WIN_WDT;
	map->center = find_center(map);
	drawimage(map);
}

int			fdf_hook(t_fdf *map)
{
		mlx_destroy_image(map->mlx, map->image.img);
		keycheck(map);
		fillimage(map);
		return 0;
}


#include <stdio.h>

int		main(int argc, char **argv)
{
	int				fd;
	t_fdf			*map;

	if (argc != 2 && argc != 4)
		return (err_msg("Usage : ./fdf <filename> [ case_size z_size ]\n"));
	if (!(map = (t_fdf *)malloc(sizeof(t_fdf))))
		return (err_msg("error\n"));
	if (((fd = open(argv[1] , O_RDONLY)) == -1) || chknflla(fd, map) == 0)
		return (err_msg("error\n"));
	if (argv[2] && argv[3])
		scale(map, ft_atoi(argv[2]), ft_atoi(argv[3]));
	else
		scale(map, 20, 20);
	mlx_loop_hook(map->mlx, fdf_hook, map);
	mlx_hook(map->win, 2, 0, key_press_hook, map);
	mlx_hook(map->win, 3, 0, key_release_hook, map);
	mlx_loop(map->mlx);
	return (0);
}








	//
	// printf("yo\n\n");
	// if (str[i] != '\0')
	// {
	// 	while (!(ft_isdigit(str[i])))
	// 		i++;
	// 	if ((ft_isdigit(str[i])))
	// 		printf("str num: %d\n\n", getnbr(str, &i));
	// 	printf("i: %d\nstr[i]: %c\n", i, str[i]);
	// 	if (str[i] == ',')
	// 	{
	// 		i++;
	// 		printf("str num 2: %d\n\n", getnbr(str, &i));
	// 	}
	// }
	// printf("yoyo\n\n");
