/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:53:53 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 15:02:57 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <fcntl.h>

/*
**	BMP format
**	Important bytes
file header : 14 bytes
0 Signature = 'B'
1 Signature = 'M'
2-5 file size
11-15 data offset

info header : 40 bytes
0-3 size
4-7 width
8-11 height
12 planes = 1
14 bits per pixel
20-23 data size
*/

typedef struct __attribute__((__packed__)) s_file_header
{
	char	signature[2];
	int		file_size;
	int		reserved;
	int		data_offset;
}	t_file_h;

typedef struct __attribute__((__packed__)) s_info_header
{
	int				size;
	int				width;
	int				height;
	unsigned char	planes[2];
	unsigned char	bits_per_pixel[2];
	int				compression;
	int				data_size;
	int				h_res;
	int				v_res;
	int				colors;
	int				important_colors;
}	t_info_h;

void	init_bmp(t_file_h *fh, t_info_h *ih, int width, int height)
{
	fh->signature[0] = 'B';
	fh->signature[1] = 'M';
	fh->reserved = 0;
	fh->file_size = sizeof(t_file_h) + sizeof(t_info_h) + width * height * 4;
	fh->data_offset = sizeof(t_file_h) + sizeof(t_info_h);
	ih->size = 40;
	ih->planes[0] = 1;
	ih->planes[1] = 0;
	ih->bits_per_pixel[0] = 32;
	ih->bits_per_pixel[1] = 0;
	ih->compression = 0;
	ih->data_size = 0;
	ih->h_res = 0;
	ih->v_res = 0;
	ih->colors = 0;
	ih->important_colors = 0;
	ih->width = width;
	ih->height = height;
}

void	write_color_bmp(int fd, int x, int y)
{
	int				icolor;
	unsigned char	color[4];

	icolor = get_color(&g_d.img, x, y);
	color[0] = (icolor) & 0xff;
	color[1] = (icolor >> 8) & 0xff;
	color[2] = (icolor >> 16) & 0xff;
	color[3] = (unsigned char)(0);
	write(fd, &color, 4);
}

void	save_bmp(void)
{
	t_file_h	fh;
	t_info_h	ih;
	int			fd;
	int			i;
	int			j;

	init_bmp(&fh, &ih, g_d.sw, g_d.sh);
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 00700);
	write(fd, &fh, sizeof(fh));
	write(fd, &ih, sizeof(ih));
	i = g_d.sh;
	while (i > 0)
	{
		j = 0;
		while (j < g_d.sw)
		{
			write_color_bmp(fd, j, i);
			j++;
		}
		i--;
	}
	close (fd);
	printf ("First render saved to screenshot.bmp\n");
}
