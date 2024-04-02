/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:56:39 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/02 16:41:20 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
+ 69
- 78
up 126
down 125
left 123
right 124
w 13
s 1
9 92
6 88
8 91
5 87
1 83
2 84
3 85
*/
static void	keys_and_new_image(int keycode, t_main *fdf)
{
	if (keycode == 83)
		fdf->proj = 0;
	else if (keycode == 84)
		fdf->proj = 1;
	else if (keycode == 85)
		fdf->proj = 3;
	free(fdf->img.img);
	free(fdf->img.addr);
	fdf->img.img = mlx_new_image(fdf->mlx, WIDTH, HEIGTH);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel,
			&fdf->img.line_length, &fdf->img.endian);
	draw_lines(fdf, fdf->proj);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	info(fdf);
}

static int	keys2(int keycode, t_main *fdf)
{
	if (keycode == 53)
	{
		mlx_destroy_window(fdf->mlx, fdf->win);
		free_map(&fdf->map, 0);
	}
	else if (keycode == 91)
	{
		if (fdf->map->scale_z == 1)
			fdf->map->scale_z -= 2;
		else
			fdf->map->scale_z -= 1;
	}
	else if (keycode == 87)
	{
		if (fdf->map->scale_z == 1)
			fdf->map->scale_z += 2;
		else
			fdf->map->scale_z += 1;
	}
	else if (keycode == 92)
		fdf->map->angle -= 0.1;
	else if (keycode == 88)
		fdf->map->angle += 0.1;
	return (0);
}

static int	keys(int keycode, t_main *fdf)
{
	if (keycode == 69)
		fdf->map->zoom += 2;
	else if (keycode == 78)
		fdf->map->zoom -= 2;
	else if (keycode == 123)
		fdf->map->shift_x -= 10;
	else if (keycode == 124)
		fdf->map->shift_x += 10;
	else if (keycode == 126)
		fdf->map->shift_y -= 10;
	else if (keycode == 125)
		fdf->map->shift_y += 10;
	keys2(keycode, fdf);
	keys_and_new_image(keycode, fdf);
	return (0);
}

static int	close_win_mouse(t_main *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	free_map(&mlx->map, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	fdf;

	if (argc == 2)
	{
		fdf.map = malloc(sizeof(t_params));
		if (!fdf.map)
			return (0);
		if (read_map(&fdf.map, argv[1]) == -1)
			return (0);
		fdf.proj = 0;
		fdf.rgb.rgb = fdf.map->color[0];
		set_win_values(&fdf);
		fdf.mlx = mlx_init();
		fdf.win = mlx_new_window(fdf.mlx, WIDTH, HEIGTH, "FDF");
		fdf.img.img = mlx_new_image(fdf.mlx, WIDTH, HEIGTH);
		fdf.img.addr = mlx_get_data_addr(fdf.img.img, &fdf.img.bits_per_pixel,
				&fdf.img.line_length, &fdf.img.endian);
		draw_lines(&fdf, fdf.proj);
		mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img.img, 0, 0);
		info(&fdf);
		mlx_hook(fdf.win, 2, 0, keys, &fdf);
		mlx_hook(fdf.win, 17, 0, close_win_mouse, &fdf);
		mlx_loop(fdf.mlx);
	}
	return (0);
}
