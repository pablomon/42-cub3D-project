/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:56:22 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 15:52:07 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(void)
{
	t_raycast	r;

	g_d.img.ptr = mlx_new_image(g_d.mlx, g_d.sw, g_d.sh);
	g_d.img.addr = (int *)mlx_get_data_addr(g_d.img.ptr, &g_d.img.bpp, \
		&g_d.img.size_line, &g_d.img.bigendian);
	if (!g_d.img.addr)
		exit_cub(MLX_ERROR);
	r.x = 0;
	while (r.x < g_d.sw)
	{
		raycast1(&r);
		raycast2(&r);
		raycast3(&r);
		raycast4(&r);
		draw_floor_ceil(&r);
		g_d.zbuff[r.x] = r.p_wal_dst;
		r.x++;
	}
	sprites();
	minimap(20, 20, 4);
	if (!g_i.is_scnshot)
		mlx_put_image_to_window(g_d.mlx, g_d.win, g_d.img.ptr, 0, 0);
}
