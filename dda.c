/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:31:42 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/02 15:01:29 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	my_mlx_pixel_put(t_main *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->img.addr + (y * fdf->img.line_length + x
			* (fdf->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	altitude(t_main *fdf, int x, int y)
{
	fdf->map->z = fdf->map->coord[y][x];
	fdf->map->zz = fdf->map->coord[(int)fdf->map->yy][(int)fdf->map->xx];
	if (fdf->map->z)
		fdf->map->z *= fdf->map->scale_z;
	if (fdf->map->zz)
		fdf->map->zz *= fdf->map->scale_z;
}

static void	dda(t_main *fdf, float x, float y, int proj)
{
	float	dx;
	float	dy;
	int		steps;

	steps = proj;
	altitude(fdf, (int)x, (int)y);
	zoom(fdf, &x, &y);
	projections(fdf->map, &x, &y, proj);
	center_img(fdf, &x, &y);
	dx = fdf->map->xx - x;
	dy = fdf->map->yy - y;
	steps = fmax(fabsf(dx), fabsf(dy));
	dx /= steps;
	dy /= steps;
	while (steps)
	{
		colors_pixel(fdf, steps);
		if (x < INFO || y < 0 || x > WIDTH || y > HEIGTH)
			break ;
		my_mlx_pixel_put(fdf, x, y, fdf->rgb.rgb);
		x += dx;
		y += dy;
		steps--;
	}
}

void	draw_lines(t_main *fdf, int proj)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->heigth)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			fdf->map->xx = x;
			fdf->map->yy = y + 1;
			colors(fdf, x, y, 1);
			if (y < fdf->map->heigth - 1)
				dda(fdf, x, y, proj);
			fdf->map->xx = x + 1;
			fdf->map->yy = y;
			colors(fdf, x, y, 0);
			if (x < fdf->map->width - 1)
				dda(fdf, x, y, proj);
			x++;
		}
		y++;
	}
}
