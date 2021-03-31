/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:55:52 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/28 19:05:22 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_info(char *av)
{
	int		i;

	g_i.file_path = ft_strdup(av);
	g_i.ids_read = 0;
	g_i.res_x = 0;
	g_i.res_y = 0;
	g_i.ceil[0] = -1;
	g_i.ceil[1] = -1;
	g_i.ceil[2] = -1;
	g_i.floor[0] = -1;
	g_i.floor[1] = -1;
	g_i.floor[2] = -1;
	i = -1;
	while (i++ < 5)
		g_i.tex_paths[i] = NULL;
	g_i.nrows = 0;
	g_i.ncols = 0;
	g_i.cardinal = 0;
	g_i.map = NULL;
	g_i.sp_lst = NULL;
}

void	free_content(void *content)
{
	if ((t_sp *)content)
	{
		free((t_sp *)content);
		content = NULL;
	}
}

void	free_info(void)
{
	int		i;

	if (g_i.file_path != NULL)
		free(g_i.file_path);
	i = -1;
	while (i++ < 5 - 1)
		if (g_i.tex_paths[i] != NULL)
			free(g_i.tex_paths[i]);
	i = -1;
	if (g_i.map != NULL)
	{
		while (i++ < g_i.nrows - 1)
			if (g_i.map[i] != NULL)
				free(g_i.map[i]);
		free(g_i.map);
	}
	ft_lstclear(&g_i.sp_lst, &free_content);
}

void	init_data(void)
{
	int	i;

	g_d.mlx = NULL;
	g_d.posx = g_i.spawn_pos.col + 0.5;
	g_d.posy = g_i.spawn_pos.row + 0.5;
	g_d.dirx = 0;
	g_d.diry = 0;
	if (g_i.cardinal == 'N')
		g_d.diry = -1;
	else if (g_i.cardinal == 'S')
		g_d.diry = +1;
	else if (g_i.cardinal == 'E')
		g_d.dirx = +1;
	else if (g_i.cardinal == 'W')
		g_d.dirx = -1;
	g_d.planex = FOV * g_d.dirx;
	g_d.planey = -FOV * g_d.diry;
	g_d.sp_z = (int *)ft_calloc(ft_lstsize(g_i.sp_lst), sizeof(int));
	i = -1;
	while (i++ < 5)
		g_d.texs[i] = NULL;
}

void	free_data(void)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (g_d.texs[i] != NULL)
			mlx_destroy_image(g_d.mlx, g_d.texs[i]->ptr);
		i++;
	}
	if (g_d.mlx != NULL)
	{
		if (g_d.win != NULL)
			mlx_destroy_window(g_d.mlx, g_d.win);
		free(g_d.mlx);
	}
	free(g_d.sp_z);
	if (g_d.zbuff != NULL)
		free(g_d.zbuff);
}
