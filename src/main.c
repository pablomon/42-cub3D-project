/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:54:03 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 15:51:57 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

t_info	g_i;
t_data	g_d;

void	exit_cub(int status)
{
	free_info();
	free_data();
	if (status > 0)
	{
		prt_err(status);
		exit(EXIT_FAILURE);
	}
	ft_putstr("Bye!\n");
	exit(EXIT_SUCCESS);
}

void	start_mlx(void)
{
	int	mw;
	int	mh;

	g_d.mlx = mlx_init();
	mlx_get_screen_size(g_d.mlx, &mw, &mh);
	g_d.sw = g_i.res_x;
	g_d.sh = g_i.res_y;
	if (g_i.res_x > mw)
		g_d.sw = mw;
	if (g_i.res_y > mh)
		g_d.sh = mh;
	if (!g_i.is_scnshot)
		g_d.win = mlx_new_window(g_d.mlx, g_d.sw, g_d.sh, "Cub3d");
}

int	args_check(int ac, char **av)
{
	g_i.is_scnshot = 0;
	if (ac == 3 && ext_chk(av[1], "cub") == SUCCESS
		&& !ft_strncmp(av[2], "--save", 7))
	{
		g_i.is_scnshot = 1;
		return (SUCCESS);
	}
	else if (ac == 2)
	{
		if (ext_chk(av[1], "cub") == SUCCESS)
			return (SUCCESS);
		else
		{
			prt_err(BAD_EXTENSION);
			exit(EXIT_FAILURE);
		}
	}
	if (ac == 1)
		prt_err(NO_ARGS);
	if (ac > 3)
		prt_err(TOO_MANY_ARGS);
	prt_err(ARGS_ERROR);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	int	i;

	args_check(ac, av);
	init_info(av[1]);
	parse_file();
	init_data();
	start_mlx();
	g_d.zbuff = (double *)calloc(g_d.sw, sizeof(double));
	i = -1;
	while (i++ < 5 - 1)
		g_d.texs[i] = new_img(g_i.tex_paths[i]);
	render();
	if (g_i.is_scnshot == 1)
	{
		save_bmp();
		mlx_destroy_image(g_d.mlx, g_d.img.ptr);
		exit_cub (SUCCESS);
	}
	mlx_hook(g_d.win, 17, 1L << 17, &close_window, &g_d);
	mlx_hook(g_d.win, 2, 1L << 0, &key_pressed, &g_d);
	mlx_loop(g_d.mlx);
	exit_cub(EXIT_SUCCESS);
	return (0);
}
