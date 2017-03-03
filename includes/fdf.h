/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 10:43:42 by chansen           #+#    #+#             */
/*   Updated: 2017/02/28 20:51:46 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>

# include "./../libft/libft.h"
# include "./../minilibx/mlx.h"

# define WIN_HGT				1000
# define WIN_WDT				1000

typedef struct		s_keys
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				q;
	int				e;
	int				r;
	int				f;
}					t_keys;

typedef struct		s_rot
{
	float			x;
	float			y;
	float			z;
}					t_rot;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_line
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	t_color			c1;
	t_color			c2;
	float			d;
	int				dx;
	int				dy;
	int				xi;
	int				yi;
	int				e;
	int				etmp;
}					t_line;

typedef	struct		s_point
{
	float			x;
	float			y;
	float			z;
	t_color			color;
}					t_point;

typedef struct		s_img
{
	void			*img;
	char			*data;
	int				height;
	int				width;
	int				sizeline;
	int				bits;
	int				endian;
}					t_img;

typedef struct		s_fdf
{
	t_point			**point;
	t_point			center;
	t_img			image;
	t_keys			key;
	t_rot			rot;
	char			*read;
	int				xlen;
	int				ylen;
	void			*mlx;
	void			*win;
}					t_fdf;

int					chknflla(int fd, t_fdf *map);
int					rdin(int fd, t_fdf *map);
int					rowcheck(t_fdf *map, char **r, int *y);

int					fdf_hook(t_fdf *map);
int					key_release_hook(int key, t_fdf *map);
int					key_press_hook(int key, t_fdf *map);
int					expose_hook(t_fdf *map);

void				keycheck(t_fdf *map);

void				rotxaxis(t_fdf *map, float rot);
void				rotyaxis(t_fdf *map, float rot);
void				spinz(t_fdf *map, float rot);
void				reset_rotation(t_fdf *map);

void				scale(t_fdf *map, float xy, float z);
void				xy_scale(t_fdf *map, float scale);
void				z_scale(t_fdf *map, float scale);
void				zoom(t_fdf *map, float zoom);

void				fillimage(t_fdf *map);
void				drawimage(t_fdf *map);
t_line				line(t_point p1, t_point p2, int setx, int sety);
void				drawbline(t_fdf *map, t_line line);
t_color				colorscaling(t_line line);

t_point				find_center(t_fdf *map);
float				xmean(t_fdf *map);
float				ymean(t_fdf *map);
float				zmean(t_fdf *map);

void				put_image_pixel(t_img image, int x, int y, t_color color);
t_point				make_point(float x, float y, float z);
t_color				make_color(int hex);

int					err_msg(char *str);
void				zero_out(t_fdf *map);
int					setx(float centerx);
int					sety(float centery);

#endif
