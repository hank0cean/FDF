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
# include "./mlx/mlx.h"

# define WIN_HGT				1000
# define WIN_WDT				1000

typedef struct	s_keys
{
	int						w;
	int						s;
	int						a;
	int						d;
	int						q;
	int						e;
	int						r;
	int						f;
}								t_keys;

typedef struct	s_line
{
	float					x1;
	float					y1;
	float					x2;
	float					y2;
	int						dx;
	int						dy;
	int						xi;
	int						yi;
	int						e;
	int						etmp;
}								t_line;

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

typedef struct  s_fdf
{
	t_point				**point;
	t_point				center;
	t_img					image;
	t_keys				key;
	char					*read;
  int						xlen;
  int						ylen;
  void					*mlx;
  void					*win;
}               t_fdf;

#endif
