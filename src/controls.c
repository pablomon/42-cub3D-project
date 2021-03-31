/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:54:00 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 15:47:13 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int	close_window(void)
{
	ft_putstr("User closes window\n");
	exit_cub(SUCCESS);
	return (OK);
}

int	key_pressed(int key_code)
{
	double	rot_dir;
	double	fwd_dir;
	double	swd_dir;

	rot_dir = 0;
	fwd_dir = 0;
	swd_dir = 0;
	if (key_code == ESC)
		close_window();
	if (key_code == LEFT_ARROW)
		rot_dir = +1;
	if (key_code == RIGHT_ARROW)
		rot_dir = -1;
	if (key_code == W)
		fwd_dir = +1;
	if (key_code == S)
		fwd_dir = -1;
	if (key_code == A)
		swd_dir = -1;
	if (key_code == D)
		swd_dir = +1;
	plyr_mov(rot_dir, fwd_dir, swd_dir);
	return (OK);
}

void	player_translate(double fwd_dir, double side_dir)
{
	double	fwd;
	double	swd;
	double	rad;
	double	perp_dirx;
	double	perp_diry;

	fwd = fwd_dir * MOVE_SPEED;
	if (g_i.map[(int)(g_d.posy)][(int)(g_d.posx + g_d.dirx * fwd)] == '0')
		g_d.posx += g_d.dirx * fwd;
	if (g_i.map[(int)(g_d.posy + g_d.diry * fwd)][(int)(g_d.posx)] == '0')
		g_d.posy += g_d.diry * fwd;
	if (side_dir != 0)
	{
		swd = MOVE_SPEED;
		rad = side_dir * 3.1416 / 2;
		perp_dirx = g_d.dirx * cos(rad) - g_d.diry * sin(rad);
		perp_diry = g_d.dirx * sin(rad) + g_d.diry * cos(rad);
		if (g_i.map[(int)(g_d.posy)][(int)(g_d.posx + perp_dirx * swd)] == '0')
			g_d.posx += perp_dirx * swd;
		if (g_i.map[(int)(g_d.posy + perp_diry * swd)][(int)(g_d.posx)] == '0')
			g_d.posy += perp_diry * swd;
	}
}

void	player_rotate(double rot_dir)
{
	double	rot;
	double	old;

	rot = rot_dir * ROT_SPEED;
	old = g_d.diry;
	g_d.diry = g_d.diry * cos(rot) - g_d.dirx * sin(rot);
	g_d.dirx = old * sin(rot) + g_d.dirx * cos(rot);
	old = g_d.planex;
	g_d.planex = g_d.planex * cos(rot) - g_d.planey * sin(rot);
	g_d.planey = old * sin(rot) + g_d.planey * cos(rot);
}

void	plyr_mov(double rot_dir, double fwd_dir, double side_dir)
{
	if (fwd_dir != 0 || side_dir != 0)
		player_translate(fwd_dir, side_dir);
	if (rot_dir != 0)
		player_rotate(rot_dir);
	if (rot_dir != 0 || fwd_dir != 0 || side_dir != 0)
	{
		mlx_destroy_image(g_d.mlx, g_d.img.ptr);
		render();
	}
}
