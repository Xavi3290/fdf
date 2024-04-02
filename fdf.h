/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:39:08 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/02 15:03:09 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# ifndef WIDTH
#  define WIDTH 1920
# endif
# ifndef HEIGTH
#  define HEIGTH 1080
# endif
# ifndef INFO
#  define INFO 350
# endif
# ifndef DEF_COLOR
#  define DEF_COLOR 0xF0F711
# endif

# include "get_next_line.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			rgb;
	int			is_d;
	int			dr;
	int			dg;
	int			db;
	int			color;
	int			def_color;
}				t_color;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_params
{
	int			x;
	int			y;
	int			z;
	float		xx;
	float		yy;
	int			zz;
	int			**coord;
	int			width;
	int			heigth;
	int			*color;
	int			zoom;
	int			shift_x;
	int			shift_y;
	int			scale_z;
	double		angle;
	float		eye_x;
	float		eye_y;
	float		eye_z;
	int			proj_dist;
	float		scr_center_x;
	float		scr_center_y;
}				t_params;

typedef struct s_main
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_params	*map;
	t_color		rgb;
	int			proj;
}				t_main;

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
int				ft_atohex(char *str);
int				ft_strcmp(const char *s1, const char *s2);

int				create_rgb(int r, int g, int b);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);

void			colors(t_main *fdf, int x, int y, int vertical);
void			colors_pixel(t_main *fdf, int steps);

int				read_map(t_params **map, char *argv);

void			free_map(t_params **map, int ex);
void			set_win_values(t_main *fdf);
void			zoom(t_main *fdf, float *x, float *y);
void			center_img(t_main *fdf, float *x, float *y);

void			draw_lines(t_main *fdf, int proj);

void			projections(t_params *map, float *x, float *y, int proj);

void			info(t_main *fdf);

#endif