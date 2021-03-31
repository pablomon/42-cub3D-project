/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:56:19 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/28 19:32:33 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(void)
{
	int		i;
	int		j;

	g_i.map = (char **)malloc(sizeof(char *) * g_i.nrows);
	if (g_i.map == NULL)
		exit_cub(MALLOC_ERROR);
	i = -1;
	while (i++ < g_i.nrows - 1)
	{
		g_i.map[i] = (char *)malloc(sizeof(char) * (g_i.ncols + 1));
		if (g_i.map[i] == NULL)
			exit_cub(MALLOC_ERROR);
		j = -1;
		while (j++ < g_i.ncols)
			g_i.map[i][j] = '-';
		g_i.map[i][g_i.ncols] = '\0';
	}
}

void	line_to_array(int row, char *line)
{
	int	col;

	col = 0;
	while (*(line + col) != 0)
	{
		if (*(line + col) != ' ')
		{
			g_i.map[row][col] = '0';
			if (*(line + col) == '1')
				g_i.map[row][col] = '1';
			if (*(line + col) == '2')
				add_sprite(col, row);
		}
		col++;
	}
}

void	map_to_array(int skip_lines, int fd)
{
	char	*line;
	int		ret;
	int		row;
	int		map_started;

	map_started = 0;
	row = 0;
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (skip_lines > 0 || (is_spaces_line(line) && !map_started))
		{
			skip_lines--;
			free(line);
			continue ;
		}
		map_started = 1;
		line_to_array(row, line);
		free(line);
		row++;
	}
}

int	add_sprite(int x, int y)
{
	t_sp	*sprite;

	sprite = (t_sp *)ft_calloc(1, sizeof(t_sp));
	if (sprite == NULL)
		return (MALLOC_ERROR);
	sprite->x = x + 0.5;
	sprite->y = y + 0.5;
	sprite->sqr_dist = 0;
	ft_lstadd_back(&g_i.sp_lst, ft_lstnew(sprite));
	return (OK);
}
