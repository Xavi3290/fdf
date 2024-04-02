/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:33:32 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/02 13:15:34 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	gradient(t_main *fdf, int steps, int alt)
{
	if (steps != 0)
	{
		fdf->rgb.r = get_r(fdf->rgb.rgb);
		fdf->rgb.g = get_g(fdf->rgb.rgb);
		fdf->rgb.b = get_b(fdf->rgb.rgb);
		fdf->rgb.dr = get_r(fdf->rgb.color) - fdf->rgb.r;
		fdf->rgb.dg = get_g(fdf->rgb.color) - fdf->rgb.g;
		fdf->rgb.db = get_g(fdf->rgb.color) - fdf->rgb.b;
		fdf->rgb.r += fdf->rgb.dr / steps;
		fdf->rgb.g += fdf->rgb.dg / steps;
		fdf->rgb.b += fdf->rgb.db / steps;
		fdf->rgb.rgb = create_rgb(fdf->rgb.r, fdf->rgb.g, fdf->rgb.b);
		if (alt)
			fdf->rgb.def_color = fdf->rgb.rgb;
	}
}

void	colors_pixel(t_main *fdf, int steps)
{
	if (fdf->map->z == fdf->map->zz && fdf->rgb.is_d)
	{
		if (fdf->map->z && fdf->map->zz)
			fdf->rgb.rgb = DEF_COLOR;
	}
	else if (fdf->rgb.is_d)
	{
		if (fdf->rgb.color == 0xffffff && fdf->map->color[(fdf->map->y
					* fdf->map->width) + fdf->map->x == 0xffffff])
		{
			gradient(fdf, steps, 1);
		}
		else
			gradient(fdf, steps, 0);
	}
	else
		gradient(fdf, steps, 0);
}

void	colors(t_main *fdf, int x, int y, int vertical)
{
	fdf->rgb.rgb = fdf->map->color[y * fdf->map->width + x];
	fdf->map->x = x;
	fdf->map->y = y;
	fdf->rgb.color = fdf->map->color[(int)(fdf->map->yy * fdf->map->width)
		+ (int)fdf->map->xx];
	fdf->rgb.def_color = DEF_COLOR;
	if (vertical)
	{
		if (fdf->rgb.rgb == fdf->map->color[((y + 1) * fdf->map->width) + x])
			fdf->rgb.is_d = 1;
		else
			fdf->rgb.is_d = 0;
	}
	else
	{
		if (fdf->rgb.rgb == fdf->map->color[(y * fdf->map->width) + (x + 1)])
			fdf->rgb.is_d = 1;
		else
			fdf->rgb.is_d = 0;
	}
	fdf->rgb.color = fdf->map->color[(int)(fdf->map->yy * fdf->map->width)
		+ (int)fdf->map->xx];
}
