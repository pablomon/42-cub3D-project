/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:55:56 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 15:41:19 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_wall(int row, int col, int v, int h)
{
	int		step;
	char	c;

	step = 0;
	while (1)
	{
		if (row + (v * step) > g_i.nrows - 1)
			return (0);
		if (row + (v * step) < 0)
			return (0);
		if (col + (h * step) > g_i.ncols - 1)
			return (0);
		if (col + (h * step) < 0)
			return (0);
		c = g_i.map[row + v * step][col + h * step];
		if (g_i.map[row + v * step][col + h * step] == '-')
			return (0);
		if (g_i.map[row + v * step][col + h * step] == '1')
			return (1);
		step++;
	}
	return (0);
}

void	is_round_corner(int i, int j)
{
	char	*s;
	char	*ptr;
	int		permut;

	s = (char *)ft_calloc(8, sizeof(char));
	s[0] = g_i.map[j][i];
	s[1] = g_i.map[j][i + 1];
	s[2] = g_i.map[j + 1][i + 1];
	s[3] = g_i.map[j + 1][i];
	s[4] = g_i.map[j][i];
	s[5] = g_i.map[j][i + 1];
	s[6] = g_i.map[j + 1][i + 1];
	ptr = s;
	permut = -1;
	while (permut++ < 4)
	{
		if (*ptr == '-' && *(ptr + 1) == '1'
			&& *(ptr + 2) == '0' && *(ptr + 3) == '1')
		{
			free(s);
			exit_cub(MAP_WALLS_FAIL);
		}
		ptr++;
	}
	free(s);
}

void	check_squared(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_i.ncols - 1)
	{
		j = 0;
		while (j < g_i.nrows - 1)
		{
			is_round_corner(i, j);
			j++;
		}
		i++;
	}
}

void	check_walls(void)
{
	int		found;
	int		row;
	int		col;
	char	c;

	row = -1;
	col = -1;
	while (row++ < g_i.nrows - 1)
	{
		while (col++ < g_i.ncols - 1)
		{
			c = g_i.map[row][col];
			found = 0;
			if (g_i.map[row][col] == '-')
				continue ;
			found += find_wall(row, col, -1, 0);
			found += find_wall(row, col, 1, 0);
			found += find_wall(row, col, 0, -1);
			found += find_wall(row, col, 0, 1);
			if (found != 4)
				exit_cub(MAP_WALLS_FAIL);
		}
		col = -1;
	}
	check_squared();
}

int	check_map_line(int row, char *line, int *cols)
{
	int	i;

	i = 0;
	while (*(line + i) != 0)
	{
		if (!ft_strchr("012NEWS \n", *(line + i)))
		{
			printf("character: '%c'\n", *(line + i));
			return (BAD_MAP_CHAR);
		}
		if (ft_strchr("NEWS", *(line + i)) != 0)
		{
			if (g_i.cardinal != 0)
				return (SPAWN_REPEATED);
			else
			{
				g_i.cardinal = *(line + i);
				g_i.spawn_pos.row = row - 1;
				g_i.spawn_pos.col = i;
			}
		}
		i++;
	}
	*cols = i;
	return (OK);
}
