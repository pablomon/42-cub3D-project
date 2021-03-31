/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:56:12 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 14:55:25 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(int fd, int start)
{
	init_map();
	map_to_array(start, fd);
	if (g_i.cardinal == 0)
		exit_cub(MIS_SPAWN_ERROR);
	check_walls();
}

int	check_map(int fd, int cols, int res, int map_started)
{
	int		ret;
	char	*line;

	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (is_spaces_line(line) && !map_started)
		{
			free(line);
			continue ;
		}
		map_started = 1;
		res = check_map_line(g_i.nrows + 1, line, &cols);
		free(line);
		if (res != OK)
			exit_cub(res);
		if (cols > g_i.ncols)
			g_i.ncols = cols;
		g_i.nrows = g_i.nrows + 1;
	}
	if (g_i.ncols < 3 || g_i.nrows < 3)
		exit_cub(INVALID_MAP);
	return (OK);
}

void	parse_identifiers(int fd, int *ids_end_line)
{
	char	*line;
	int		ret;
	int		res;
	int		is_map;

	ret = 1;
	is_map = 0;
	while (ret == 1 && g_i.ids_read < 8)
	{
		ret = get_next_line(fd, &line);
		res = parse_id_line(line);
		if (res != OK)
		{
			free(line);
			exit_cub(res);
		}
		free(line);
		*ids_end_line = *ids_end_line + 1;
	}
}

void	parse_file(void)
{
	int		fd;
	int		ids_end_line;

	ids_end_line = 0;
	fd = open(g_i.file_path, O_RDONLY);
	if (fd == -1)
		exit_cub(READ_FILE_ERROR);
	parse_identifiers(fd, &ids_end_line);
	check_map(fd, 0, 0, 0);
	close(fd);
	fd = open(g_i.file_path, O_RDONLY);
	if (fd == -1)
		exit_cub(READ_FILE_ERROR);
	parse_map(fd, ids_end_line);
	close(fd);
}
