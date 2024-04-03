/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:34:09 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/03 10:29:35 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	controls(t_main *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, 5, 70, 0x00ff00, "'+' to zoom in");
	mlx_string_put(fdf->mlx, fdf->win, 5, 90, 0x00ff00, "'-' to zoom out");
	mlx_string_put(fdf->mlx, fdf->win, 5, 110, 0x00ff00, "'->' right");
	mlx_string_put(fdf->mlx, fdf->win, 5, 130, 0x00ff00, "'<-' left");
	mlx_string_put(fdf->mlx, fdf->win, 5, 150, 0x00ff00, "'^' up");
	mlx_string_put(fdf->mlx, fdf->win, 5, 170, 0x00ff00, "'v' down");
	mlx_string_put(fdf->mlx, fdf->win, 5, 190, 0x00ff00, "'9' rotate right");
	mlx_string_put(fdf->mlx, fdf->win, 5, 210, 0x00ff00, "'6' rotate left");
	mlx_string_put(fdf->mlx, fdf->win, 5, 230, 0x00ff00,
		"'8' decrease altitude");
	mlx_string_put(fdf->mlx, fdf->win, 5, 250, 0x00ff00,
		"'5' increase altitude");
	mlx_string_put(fdf->mlx, fdf->win, 5, 270, 0x00ff00, "'1' isometric");
	mlx_string_put(fdf->mlx, fdf->win, 5, 290, 0x00ff00, "'2' conical");
	mlx_string_put(fdf->mlx, fdf->win, 5, 310, 0x00ff00, "'3' parallel");
}

void	info(t_main *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, 5, 40, 0xff0000, "Controls");
	controls(fdf);
}
