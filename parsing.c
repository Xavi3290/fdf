/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xroca-pe <xroca-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:56:05 by xroca-pe          #+#    #+#             */
/*   Updated: 2024/04/02 13:12:44 by xroca-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	point_fdf(char *argv)
{
	int	i;

	i = ft_strlen(argv);
	i -= 4;
	if (!ft_strcmp(".fdf", &argv[i]))
		return (1);
	return (0);
}

static int	get_width_height(t_params **map, char *argv)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (fd);
	line = get_next_line(fd);
	split = ft_split(line, ' ');
	(*map)->width = 0;
	(*map)->heigth = 0;
	while (split[(*map)->width])
	{
		free(split[(*map)->width]);
		(*map)->width++;
	}
	free(split);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		(*map)->heigth++;
	}
	close(fd);
	return (0);
}

static void	memory_map(t_params **map)
{
	int	i;

	i = 0;
	(*map)->coord = malloc(sizeof(int *) * ((*map)->heigth + 1));
	if (!(*map)->coord)
		free_map(map, 1);
	while (i < (*map)->heigth)
	{
		(*map)->coord[i] = malloc(sizeof(int) * ((*map)->width + 1));
		if (!(*map)->coord[i])
			free_map(map, 1);
		i++;
	}
	(*map)->color = malloc(sizeof(int) * ((*map)->width * (*map)->heigth + 1));
	if (!(*map)->color)
		free_map(map, 1);
}

static void	get_numbers(t_params **map, char *line, int i)
{
	char	**split;
	int		j;
	int		k;

	split = ft_split(line, ' ');
	j = 0;
	while (split[j])
	{
		(*map)->coord[i][j] = ft_atoi(split[j]);
		(*map)->color[i * (*map)->width + j] = 16777215;
		k = 0;
		while (split[j][k])
		{
			if (split[j][k] == ',')
			{
				k++;
				(*map)->color[i * (*map)->heigth + j] = ft_atohex(&split[j][k]);
			}
			k++;
		}
		free(split[j]);
		j++;
	}
	(*map)->coord[i][j] = 0;
	free(split);
}

int	read_map(t_params **map, char *argv)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	if (!point_fdf(argv) || get_width_height(map, argv) < 0)
		return (-1);
	memory_map(map);
	fd = open(argv, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		get_numbers(map, line, i);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	(*map)->coord[i] = 0;
	(*map)->color[(*map)->width * (*map)->heigth] = 0;
	close(fd);
	return (0);
}
