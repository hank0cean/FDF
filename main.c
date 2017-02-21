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












































int		rowcheck(t_fdf *map, char **r, int *y)
{
	int		gx;
	int		i;

	gx = 0;
	while (r[gx] != NULL)
	{
		i = 0;
		if (ft_isdigit(r[gx][i]) == 1)
			map->point[*y][gx].z = getnbr(r[gx], &i);
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
		y++;
	}
	map->read = line;
	y < 2 ? 0 : (map->ylen = y);
	map->point = (t_point**)malloc(sizeof(t_point*) * map->ylen);
	while (y >= 0)
		map->point[y--] = (t_point*)malloc(sizeof(t_point) * map->xlen);
	return (1);
}

int		chknflla(int fd, t_fdf *map)
{
	char	**lines;
	int		y;

	y = 0;
	if (rdin(fd, map) == 0)
		return (0);
	lines = ft_strsplit(map->read, '\n');
	while (y < map->ylen)
	{
		if (rowcheck(map, ft_strsplit(lines[y], ' '), &y) != 1)
				return (0);
		y++;
	}
	map->centerx = (map->xlen / 2);
	map->centery = (map->ylen / 2);
	if (!(map->mlx = mlx_init()))
		return (err_msg("error\n"));
	map->window = mlx_new_window(map->mlx, WIN_WDT, WIN_HGT, "Im LOrDE");
	return (1);
}

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
	return (key);
}

int			key_release_hook(int key, t_fdf *map)
{
	printf("key_release: %i\n\n", key);
	if (key == 53)
	{
		mlx_destroy_window(map->mlx, map->window);
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
	return (key);
}

int			fdf_loop_hook(t_fdf *map)
{
		map->image.img = mlx_new_image(map->mlx, WIN_WDT, WIN_HGT);


		return 0;
}

#include <stdio.h>

int		main(int argc, char **argv)
{
	int				fd;
	t_fdf		*map;

	if (argc == 1 || argc == 3 || argc > 4)
		return (err_msg("Usage : ./fdf <filename> [ case_size z_size ]\n"));
	if (!(map = (t_fdf *)malloc(sizeof(t_fdf))))
		return (err_msg("error\n"));
	if (((fd = open(argv[1] , O_RDONLY)) == -1) || chknflla(fd, map) == 0)
		return (err_msg("error\n"));

	printf("MLXvvv ::: centerx: %d\tcentery: %d\twindowcenterx: %d\twindowcentery: %d\n\n",
		map->centerx, map->centery, WIN_WDT / 2, WIN_HGT / 2);




	mlx_hook(map->window, 2, 0, key_press_hook, map);
	printf("hello\n");
	fdf_loop_hook(map);
	mlx_hook(map->window, 3, 0, key_release_hook, map);
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
