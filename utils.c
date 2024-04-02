/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:13:43 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/02 13:14:02 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_params **map, int ex)
{
	int	i;

	i = 0;
	if ((*map)->coord)
	{
		while ((*map)->coord[i])
		{
			free((*map)->coord[i]);
			i++;
		}
		free((*map)->coord);
	}
	if ((*map)->color)
		free((*map)->color);
	free(*map);
	if (ex)
		exit(1);
	else
		exit(0);
}

void	set_win_values(t_main *fdf)
{
	int	set_width;
	int	set_heigth;

	set_width = (WIDTH - INFO) / fdf->map->width / 1.8;
	set_heigth = HEIGTH / fdf->map->heigth / 1.8;
	fdf->map->zoom = fmin(set_width, set_heigth);
	fdf->map->shift_x = (WIDTH - INFO) / 3 + INFO;
	fdf->map->shift_y = HEIGTH / 3;
	fdf->map->angle = 0.6;
	fdf->map->scale_z = 1;
}

void	zoom(t_main *fdf, float *x, float *y)
{
	*x *= fdf->map->zoom;
	*y *= fdf->map->zoom;
	fdf->map->xx *= fdf->map->zoom;
	fdf->map->yy *= fdf->map->zoom;
}

void	center_img(t_main *fdf, float *x, float *y)
{
	*x += fdf->map->shift_x;
	*y += fdf->map->shift_y;
	fdf->map->xx += fdf->map->shift_x;
	fdf->map->yy += fdf->map->shift_y;
}
