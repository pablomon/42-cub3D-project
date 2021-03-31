/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:56:08 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 09:56:08 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	color_to_int(int r, int g, int b)
{
	int	color;

	color = (r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff);
	return (color);
}

void	put_pix(int x, int y, int color, int thickness)
{
	char	*dst;
	int		sx;
	int		sy;

	sx = 0;
	while (sx < thickness)
	{
		sy = 0;
		while (sy < thickness)
		{
			dst = g_d.img.addr + ((y + sy) * g_d.img.size_line
					+ (x + sx) * (g_d.img.bpp / 8));
			*(unsigned int *)dst = color;
			sy++;
		}
		sx++;
	}
}

int	get_color(t_mlx_img *img, int x, int y)
{
	void	*ptr;
	int		*ptr_int;

	ptr = &(img->addr[img->size_line * y + img->bpp / 8 * x]);
	ptr_int = (int *)ptr;
	return (*ptr_int);
}

t_mlx_img	*new_img(char *path)
{
	t_mlx_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		exit_cub(MALLOC_ERROR);
	img->ptr = mlx_xpm_file_to_image(g_d.mlx, path, &img->w, &img->h);
	if (!img->ptr)
	{
		free(img);
		printf("Loading texture '%s'\n", path);
		exit_cub(TEXTURE_LOAD_ERROR);
	}
	img->addr = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
			&img->size_line, &img->bigendian);
	if (!img->addr)
	{
		free(img->ptr);
		free(img);
		printf("Loading texture '%s'\n", path);
		exit_cub(TEXTURE_LOAD_ERROR);
	}
	return (img);
}
