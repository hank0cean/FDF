/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:19:39 by chansen           #+#    #+#             */
/*   Updated: 2017/02/27 19:19:44 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/fdf.h"

int			key_press_hook(int key, t_fdf *map)
{
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

int			expose_hook(t_fdf *map)
{
	reset_rotation(map);
	return (1);
}

int			fdf_hook(t_fdf *map)
{
	keycheck(map);
	fillimage(map);
	mlx_put_image_to_window(map->mlx, map->win, map->image.img, 0, 0);
	return (0);
}

int			main(int argc, char **argv)
{
	int				fd;
	t_fdf			*map;

	if (argc != 2 && argc != 4)
		return (err_msg("Usage : ./fdf <filename> [ case_size z_size ]\n"));
	if (!(map = (t_fdf *)malloc(sizeof(t_fdf))))
		return (err_msg("error1\n"));
	if (((fd = open(argv[1], O_RDONLY)) == -1) || chknflla(fd, map) == 0)
		return (err_msg("error2\n"));
	if (argv[2] && argv[3])
		scale(map, ft_atoi(argv[2]), ft_atoi(argv[3]));
	else
		scale(map, 20, 20);
	mlx_expose_hook(map->win, expose_hook, map);
	mlx_hook(map->win, 2, 0, key_press_hook, map);
	mlx_hook(map->win, 3, 0, key_release_hook, map);
	mlx_loop_hook(map->mlx, fdf_hook, map);
	mlx_loop(map->mlx);
	return (0);
}
