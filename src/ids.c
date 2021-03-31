/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ids.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:55:47 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 09:55:48 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_res(char *resx, char *resy)
{
	g_i.res_x = ft_atoi(resx);
	g_i.res_y = ft_atoi(resy);
	if (g_i.res_x == 0 || g_i.res_y == 0)
		return (RES_LINE_ERROR);
	g_i.ids_read++;
	return (OK);
}

int	jump_comma(char **str)
{
	char	*ptr;
	int		i;

	ptr = *str;
	i = 0;
	while (ft_isspace(ptr[i]))
		i++;
	if (ptr[i] != ',')
		return (ERROR);
	i++;
	while (ft_isspace(ptr[i]))
		i++;
	*str += i;
	return (OK);
}

int	parse_color_component(char **str, int *dest)
{
	int		i;
	char	comp[4];
	char	*ptr;

	i = 0;
	ptr = *str;
	ft_memset(comp, 0, 3);
	while (ft_isdigit(ptr[i]) && i < 3)
	{
		comp[i] = ptr[i];
		i++;
	}
	if (i == 0)
		return (ERROR);
	comp[i] = '\0';
	*dest = ft_atoi(comp);
	if (*dest < 0 || *dest > 255)
		return (ERROR);
	*str += i;
	return (OK);
}

int	parse_color(char *str, int errn, int *color_ptr)
{
	str += 2;
	while (ft_isspace(*str))
		str++;
	if (parse_color_component(&str, color_ptr) == ERROR)
		return (errn);
	jump_comma(&str);
	if (parse_color_component(&str, color_ptr + 1) == ERROR)
		return (errn);
	jump_comma(&str);
	if (parse_color_component(&str, color_ptr + 2) == ERROR)
		return (errn);
	while (ft_isspace(*str))
		str++;
	if (*str != '\0')
		return (errn);
	g_i.ids_read++;
	return (OK);
}

int	parse_tex(char *id, int tex)
{
	if (g_i.tex_paths[tex] != NULL)
		return (REPEATED_ID_ERROR);
	while (ft_isspace(*id))
		id++;
	if (*id == '\n')
		return (TEX_PATH_ERROR);
	remove_endtrails(id);
	g_i.tex_paths[tex] = ft_strdup(id);
	g_i.ids_read++;
	return (OK);
}
