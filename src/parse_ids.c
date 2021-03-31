/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:56:15 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 10:58:53 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_c_f(char *ids)
{
	if ((ids[0] == 'C' && g_i.ceil[0] != -1)
		|| (ids[0] == 'F' && g_i.floor[0] != -1))
		return (REPEATED_ID_ERROR);
	if (ids[0] == 'C')
		return (parse_color(ids, CEILING_ERROR, &g_i.ceil[0]));
	else if (ids[0] == 'F')
		return (parse_color(ids, FLOOR_ERROR, &g_i.floor[0]));
	return (OK);
}

int	check_r(char *id)
{
	char	*resx;
	char	*resy;

	if (g_i.res_x != 0)
		return (REPEATED_ID_ERROR);
	id += 2;
	while (ft_isspace(*id))
		id++;
	resx = id;
	while (ft_isdigit(*id))
		id++;
	while (ft_isspace(*id))
		id++;
	resy = id;
	while (ft_isdigit(*id))
		id++;
	while (ft_isspace(*id))
		id++;
	if (*id != '\0')
		return (RES_LINE_ERROR);
	if (parse_res(resx, resy) == ERROR)
		return (RES_LINE_ERROR);
	if (g_i.res_x == 0 || g_i.res_y == 0)
		return (RES_LINE_ERROR);
	return (OK);
}

int	parse_id(char *ids)
{
	if (ids[0] == 'R' && ids[1] == ' ')
		return (check_r(ids));
	else if ((ids[0] == 'C' || ids[0] == 'F') && ids[1] == ' ')
		return (check_c_f(ids));
	else if (!ft_strncmp(ids, "NO ", 3))
		return (parse_tex(ids + 3, 0));
	else if (!ft_strncmp(ids, "EA ", 3))
		return (parse_tex(ids + 3, 1));
	else if (!ft_strncmp(ids, "WE ", 3))
		return (parse_tex(ids + 3, 2));
	else if (!ft_strncmp(ids, "SO ", 3))
		return (parse_tex(ids + 3, 3));
	else if (!ft_strncmp(ids, "S ", 2))
		return (parse_tex(ids + 2, 4));
	return (UNKNOWN_IDENTIFIER);
}

int	parse_id_line(char *line)
{
	char	*str;

	str = line;
	if (g_i.ids_read < 8)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == 0)
			return (OK);
		if (ft_iscontained(*str, "RFCNEWS"))
			return (parse_id(str));
		else
			return (EXPECTED_IDENTIFIER);
	}
	return (REPEATED_ID_ERROR);
}
