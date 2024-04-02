/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:13:51 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/02 16:12:22 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	isometric(t_params *map, float *x, float *y, int z)
{
	*x = (*x - *y) * cos(map->angle);
	*y = (*x + *y) * sin(map->angle) - z;
}

static void	conical(t_params *map, float *x, float *y)
{
	float	d;
	float	scale;

	map->eye_x = 100;
	map->eye_y = 150;
	map->eye_z = 1000;
	map->proj_dist = 1000;
	map->scr_center_x = 1;
	map->scr_center_y = 1;
	d = sqrt(((*x - map->eye_x) * (*x - map->eye_x)) + ((*y - map->eye_y) * (*y
					- map->eye_y)) + ((map->zz - map->eye_z) * (map->zz
					- map->eye_z)));
	scale = map->proj_dist / d;
	*x = map->scr_center_x + scale * (*x - map->eye_x) * cos(map->angle);
	*y = map->scr_center_y + scale * (*y - map->eye_y) * sin(map->angle);
}

static void	parallel(t_params *map, float *x, float *y, int z)
{
	*x = *x * map->scale_z * cos(map->angle);
	*y = *y * map->scale_z * sin(map->angle);
	*y -= z;
}

void	projections(t_params *map, float *x, float *y, int proj)
{
	if (proj == 0)
	{
		isometric(map, x, y, map->z);
		isometric(map, &map->xx, &map->yy, map->zz);
	}
	else if (proj == 1)
	{
		conical(map, x, y);
		conical(map, &map->xx, &map->yy);
	}
	else if (proj == 2)
	{
		parallel(map, x, y, map->z);
		parallel(map, &map->xx, &map->yy, map->zz);
	}
}
