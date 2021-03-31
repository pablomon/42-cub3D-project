/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:56:33 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/28 19:35:23 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast4(t_raycast *r)
{
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	r->texx = (int)(r->wallx * g_d.texs[r->tex_num]->w);
	if (r->side == 0 && r->raydirx > 0)
		r->texx = g_d.texs[r->tex_num]->w - r->texx - 1;
	if (r->side == 1 && r->raydiry < 0)
		r->texx = g_d.texs[r->tex_num]->w - r->texx - 1;
	step = 1.0 * g_d.texs[r->tex_num]->h / r->line_h;
	tex_pos = (r->draw_start - g_d.sh / 2 + r->line_h / 2) * step;
	y = r->draw_start;
	while (y < r->draw_end)
	{
		r->texy = (int)tex_pos & (g_d.texs[r->tex_num]->h - 1);
		tex_pos += step;
		color = get_color(g_d.texs[r->tex_num], r->texx, r->texy);
		if (r->side == 1)
			color = (color >> 1) & 8355711;
		put_pix(r->x, y, color, 1);
		y++;
	}
}

void	raycast3(t_raycast *r)
{
	r->draw_start = -r->line_h / 2 + g_d.sh / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_h / 2 + g_d.sh / 2;
	if (r->draw_end >= g_d.sh)
		r->draw_end = g_d.sh - 1;
	if (r->side == 0 && r->raydirx > 0)
		r->tex_num = 3;
	if (r->side == 0 && r->raydirx < 0)
		r->tex_num = 0;
	if (r->side == 1 && r->raydiry > 0)
		r->tex_num = 1;
	if (r->side == 1 && r->raydiry < 0)
		r->tex_num = 2;
	if (r->side == 0)
		r->wallx = g_d.posx + r->p_wal_dst * r->raydiry;
	else
		r->wallx = g_d.posy + r->p_wal_dst * r->raydirx;
	r->wallx -= floor(r->wallx);
}

void	raycast2(t_raycast *r)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->side_distx < r->side_disty)
		{
			r->side_distx += r->delta_distx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->side_disty += r->delta_disty;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (g_i.map[r->mapx][r->mapy] == '1')
			hit = 1;
	}
	if (r->side == 0)
		r->p_wal_dst = (r->mapx - g_d.posy + (1 - r->stepx) / 2) / r->raydirx;
	else
		r->p_wal_dst = (r->mapy - g_d.posx + (1 - r->stepy) / 2) / r->raydiry;
	r->line_h = (int)(g_d.sh / r->p_wal_dst);
}

void	raycast1(t_raycast *r)
{
	r->camx = 2 * r->x / (double)g_d.sw - 1;
	r->raydirx = g_d.diry + g_d.planex * r->camx;
	r->raydiry = g_d.dirx + g_d.planey * r->camx;
	r->mapx = (int)(g_d.posy);
	r->mapy = (int)(g_d.posx);
	r->delta_distx = fabs(1 / r->raydirx);
	r->delta_disty = fabs(1 / r->raydiry);
	r->stepx = 1;
	r->side_distx = (r->mapx + 1.0 - g_d.posy) * r->delta_distx;
	if (r->raydirx < 0)
	{
		r->stepx = -1;
		r->side_distx = (g_d.posy - r->mapx) * r->delta_distx;
	}
	r->stepy = 1;
	r->side_disty = (r->mapy + 1.0 - g_d.posx) * r->delta_disty;
	if (r->raydiry < 0)
	{
		r->stepy = -1;
		r->side_disty = (g_d.posx - r->mapy) * r->delta_disty;
	}
}
