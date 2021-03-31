/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:54:37 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 10:58:18 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug_print_info(void)
{
	printf("Resultados del parseado:\n\n");
	printf("Resolution: %d, %d\n", g_i.res_x, g_i.res_y);
	printf("Ceiling: %d, %d, %d\n", g_i.ceil[0], g_i.ceil[1], g_i.ceil[2]);
	printf("Floor: %d, %d, %d\n", g_i.floor[0], g_i.floor[1], g_i.floor[2]);
	printf("NO texture:\t'%s'\n", g_i.tex_paths[0]);
	printf("EA texture:\t'%s'\n", g_i.tex_paths[1]);
	printf("WE texture:\t'%s'\n", g_i.tex_paths[2]);
	printf("SO texture:\t'%s'\n", g_i.tex_paths[3]);
	printf("Sprite texture:\t'%s'\n", g_i.tex_paths[4]);
}

int	sprite_in_cel(int x, int y)
{
	t_list	*node;
	t_sp	*sp;

	node = g_i.sp_lst;
	while (node != NULL && node->content)
	{
		sp = (t_sp *)node->content;
		if (sp->y == y && sp->x == x)
			return (1);
		node = node->next;
	}
	return (0);
}

void	debug_print_map(void)
{
	int		i;
	int		j;
	char	c;

	printf("\n");
	i = 0;
	while (i < g_i.nrows)
	{
		j = 0;
		while (j < g_i.ncols)
		{
			c = g_i.map[i][j];
			if (g_i.spawn_pos.row == i && g_i.spawn_pos.col == j)
				c = ft_tolower(g_i.cardinal);
			if (sprite_in_cel(j, i))
				c = 'x';
			printf("%c", c);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}
