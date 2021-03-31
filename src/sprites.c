/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:56:27 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 09:56:27 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_sprite_calc
{
	double		spx;
	double		spy;
	double		inv_det;
	double		tx;
	double		ty;
	int			scx;
	int			udiv;
	int			vdiv;
	double		vmove;
	int			vmove_sc;
	int			w;
	int			h;
	int			draw_starty;
	int			draw_startx;
	int			draw_endx;
	int			draw_endy;
	int			d;
	int			texx;
	int			texy;
}				t_sprite_calc;

void	calc_sprites_distance(void)
{
	t_list		*node;
	t_sp		*s1;
	int			i;

	node = g_i.sp_lst;
	i = -1;
	while (i++ < ft_lstsize(g_i.sp_lst) - 1)
	{
		g_d.sp_z[i] = i;
		node = get_node(i, g_i.sp_lst);
		s1 = (t_sp *) node->content;
		s1->sqr_dist = pow(s1->x - g_d.posx, 2) + pow(s1->y - g_d.posy, 2);
	}
}

void	sort_sprites(void)
{
	void	*c1;
	void	*c2;
	int		i;
	int		is_sorted;
	int		temp;

	calc_sprites_distance();
	is_sorted = 0;
	while (!is_sorted)
	{
		is_sorted = 1;
		i = -1;
		while (i++ < ft_lstsize(g_i.sp_lst) - 2)
		{
			c1 = get_node(g_d.sp_z[i], g_i.sp_lst)->content;
			c2 = get_node(g_d.sp_z[i + 1], g_i.sp_lst)->content;
			if (((t_sp *)c1)->sqr_dist < ((t_sp *)c2)->sqr_dist)
			{
				temp = g_d.sp_z[i];
				g_d.sp_z[i] = g_d.sp_z[i + 1];
				g_d.sp_z[i + 1] = temp;
				is_sorted = 0;
			}
		}
	}
}

void	calc_sprite(double x, double y, t_sprite_calc *s_c)
{
	s_c->spx = x - g_d.posx;
	s_c->spy = y - g_d.posy;
	s_c->inv_det = 1.0 / (g_d.planey * g_d.diry - g_d.dirx * g_d.planex);
	s_c->tx = s_c->inv_det * (g_d.diry * s_c->spx - g_d.dirx * s_c->spy);
	s_c->ty = s_c->inv_det * (-g_d.planex * s_c->spx + g_d.planey * s_c->spy);
	s_c->scx = (int)((g_d.sw / 2) * (1 + s_c->tx / s_c->ty));
	s_c->udiv = 1;
	s_c->vdiv = 1;
	s_c->vmove = 0.0;
	s_c->vmove_sc = (int)(s_c->vmove / s_c->ty);
	s_c->h = abs((int)(g_d.sh / (s_c->ty))) / s_c->vdiv;
	s_c->draw_starty = (int)(-s_c->h / 2 + g_d.sh / 2 + s_c->vmove_sc);
	if (s_c->draw_starty < 0)
		s_c->draw_starty = 0;
	s_c->draw_endy = (int)(s_c->h / 2 + g_d.sh / 2 + s_c->vmove_sc);
	if (s_c->draw_endy >= g_d.sh)
		s_c->draw_endy = (int)g_d.sh - 1;
	s_c->w = abs((int)(g_d.sh / (s_c->ty))) / s_c->udiv;
	s_c->draw_startx = -s_c->w / 2 + s_c->scx;
	if (s_c->draw_startx < 0)
		s_c->draw_startx = 0;
	s_c->draw_endx = s_c->w / 2 + s_c->scx;
	if (s_c->draw_endx >= g_d.sw)
		s_c->draw_endx = (int)g_d.sw - 1;
}

void	draw_sprite(double sp_posx, double sp_posy)
{
	t_sprite_calc	s_c;
	int				stp;
	int				y;
	int				color;

	calc_sprite(sp_posx, sp_posy, &s_c);
	stp = s_c.draw_startx;
	while (stp < s_c.draw_endx)
	{
		s_c.texx = (256 * (stp + (s_c.w / 2 - s_c.scx)) * \
			g_d.texs[4]->w / s_c.w) / 256;
		if (s_c.ty > 0 && stp > 0 && stp < g_d.sw && s_c.ty < g_d.zbuff[stp])
		{
			y = s_c.draw_starty;
			while (y < s_c.draw_endy)
			{
				s_c.d = (y - s_c.vmove_sc) * 256 - \
					(int)g_d.sh * 128 + s_c.h * 128;
				s_c.texy = ((s_c.d * g_d.texs[4]->h) / s_c.h) / 256;
				color = get_color(g_d.texs[4], s_c.texx, s_c.texy);
				if ((color & 0x00FFFFFF) != 0)
					put_pix(stp, y, color, 1);
				y++;
			}
		}
		stp++;
	}
}

void	sprites(void)
{
	t_list	*node;
	t_sp	*sp;
	int		i;

	if (g_i.sp_lst != NULL && g_i.sp_lst->next != NULL)
	{
		sort_sprites();
		i = 0;
		while (i < ft_lstsize(g_i.sp_lst))
		{
			node = get_node(g_d.sp_z[i], g_i.sp_lst);
			sp = (t_sp *)(node->content);
			draw_sprite(sp->x, sp->y);
			i++;
		}
	}
}
