/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:54:46 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 09:54:46 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_floor_ceil(t_raycast *r)
{
	int		color;
	int		y;

	if ((r->draw_start < 0 || r->draw_start > g_d.sh) || \
		(r->draw_end < 0 || r->draw_end > g_d.sh))
		return (0);
	color = color_to_int(g_i.ceil[0], g_i.ceil[1], g_i.ceil[2]);
	y = 0;
	while (y < r->draw_start)
	{
		put_pix(r->x, y, color, 1);
		y++;
	}
	color = color_to_int(g_i.floor[0], g_i.floor[1], g_i.floor[2]);
	y = r->draw_end;
	while (y < g_d.sh)
	{
		put_pix(r->x, y, color, 1);
		y++;
	}
	return (0);
}
