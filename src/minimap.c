/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:56:00 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 09:56:01 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	minimap_actors(int ofstx, int ofsty, int sz)
{
	t_list	*node;
	int		i;
	int		j;

	node = g_i.sp_lst;
	while (node != NULL)
	{
		i = ((t_sp *)(node->content))->x;
		j = ((t_sp *)(node->content))->y;
		put_pix(ofstx + i * sz, ofsty + j * sz, GRAY, sz);
		node = node->next;
	}
	put_pix(ofsty + sz * (int)g_d.posx, ofstx + sz * (int)g_d.posy, RED, sz);
}

void	minimap(int ofstx, int ofsty, int sz)
{
	int		i;
	int		j;
	int		color;
	int		max_sz;

	max_sz = (int)floor((double)g_d.sh / g_i.nrows);
	if (((int)floor((double)g_d.sw / g_i.ncols)) < max_sz)
		max_sz = ((int)floor((double)g_d.sw / g_i.ncols));
	if (sz > max_sz)
		sz = max_sz;
	i = 0;
	while (i < g_i.nrows)
	{
		j = 0;
		while (j < g_i.ncols)
		{
			color = BLACK;
			if (g_i.map[i][j] == '1')
				color = WHITE;
			put_pix(ofstx + j * sz, ofsty + i * sz, color, sz);
			j++;
		}
		i++;
	}
	minimap_actors(ofstx, ofsty, sz);
}
