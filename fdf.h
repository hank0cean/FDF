/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 10:43:42 by chansen           #+#    #+#             */
/*   Updated: 2017/01/26 01:10:20 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>

# include "./libft/libft.h"
# include "./minilibx/mlx.h"

# define WIN_HGT				1000
# define WIN_WDT				1000

typedef struct	s_keys
{
	int						q;
	int						e;
	int						a;
	int						s;
	int						d;
	int						w;
}								t_keys;

typedef	struct	s_point
{
	float					x;
	float					y;
	float 				z;
	unsigned int 	color;
}								t_point;

typedef struct	s_img
{
	void 					*img;
	char					*data;
	int						height;
	int						width;
	int						sizeline;
	int						bits;
	int						endian;
}								t_img;

typedef	struct	s_cam
{
	float					x;
	float					y;
	float					z;
}								t_cam;

typedef struct  s_fdf
{
	t_point				**point;
	t_img					image;
	t_cam					view;
	t_keys				key;
	char					*read;
  int						xlen;
  int						ylen;
	int						centerx;
	int						centery;
  void					*mlx;
  void					*window;
}               t_fdf;

#endif
