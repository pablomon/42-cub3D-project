/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmontese <pmontese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:54:34 by pmontese          #+#    #+#             */
/*   Updated: 2021/03/27 10:58:18 by pmontese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# define OK 0
# define ERROR -1
/*
** LINUX KEY_CODES
*/
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

# define FOV 0.6666
# define MOVE_SPEED 0.2
# define ROT_SPEED 0.05

/*
** COLORS
*/
# define BLACK 0
# define WHITE 16777215
# define RED 16711680
# define GRAY 9868950

typedef enum e_error
{
	SUCCESS,
	UNDEFINED_ERROR,
	ARGS_ERROR,
	REPEATED_ID_ERROR,
	RES_LINE_ERROR,
	CEILING_ERROR,
	MALLOC_ERROR,
	FLOOR_ERROR,
	EXPECTED_IDENTIFIER,
	TEX_PATH_ERROR,
	UNKNOWN_IDENTIFIER,
	READ_FILE_ERROR,
	BAD_MAP_CHAR,
	MAP_WALLS_FAIL,
	SPAWN_REPEATED,
	FILE_FORMAT_ERROR,
	MLX_ERROR,
	TEXTURE_LOAD_ERROR,
	MIS_SPAWN_ERROR,
	INVALID_MAP,
	MAP_SURR_NOT_SQRD,
	BAD_EXTENSION,
	NO_ARGS,
	TOO_MANY_ARGS,
}					t_error;

typedef struct s_coord
{
	int				row;
	int				col;
}					t_coord;

typedef struct s_sprite
{
	double			x;
	double			y;
	double			sqr_dist;
}					t_sp;

typedef struct s_raycast
{
	int			x;
	double		camx;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		side_distx;
	double		side_disty;
	double		delta_distx;
	double		delta_disty;
	double		p_wal_dst;
	int			stepx;
	int			stepy;
	int			side;
	int			line_h;
	double		wallx;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	int			texx;
	int			texy;

}				t_raycast;

/*
** Textures order: NEWS
*/
typedef struct s_file_info
{
	char			*file_path;
	char			is_scnshot;
	int				res_x;
	int				res_y;
	int				ceil[3];
	int				floor[3];
	char			*tex_paths[5];
	int				ids_read;
	int				nrows;
	int				ncols;
	char			**map;
	char			cardinal;
	t_list			*sp_lst;
	t_coord			spawn_pos;
}					t_info;
extern t_info		g_i;

typedef struct s_mlx_img
{
	void			*ptr;
	void			*addr;
	int				size_line;
	int				bpp;
	int				bigendian;
	int				w;
	int				h;
}					t_mlx_img;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_mlx_img		img;
	t_mlx_img		*texs[5];
	double			sw;
	double			sh;
	double			posx;
	double			posy;
	double			diry;
	double			dirx;
	double			planex;
	double			planey;
	double			*zbuff;
	int				*sp_z;
}					t_data;
extern t_data		g_d;

/* FUNCTIONS */

int					prt_err(int err);
void				exit_cub(int status);
void				free_info(void);
void				free_data(void);
void				init_info(char *av);
void				init_data(void);
void				save_bmp(void);

//parse
int					ext_chk(char *arg, char *ext);
void				parse_file(void);
int					parse_id(char *ids);
int					parse_id_line(char *line);
int					parse_res(char *resx, char *resy);
int					parse_color(char *str, int errn, int *color_ptr);
int					parse_tex(char *ele, int free_var);
int					check_map_line(int row, char *line, int *cols);
void				init_map(void);
void				map_to_array(int start, int fd);
void				check_walls(void);
int					add_sprite(int x, int y);

int					get_next_line(int fd, char **line);

//controls
int					close_window(void);
void				plyr_mov(double rot_dir, double fwd_dir, double side_dir);
int					key_pressed(int key_code);
void				render(void);

// render

void				raycast1(t_raycast *r);
void				raycast2(t_raycast *r);
void				raycast3(t_raycast *r);
void				raycast4(t_raycast *r);
int					draw_floor_ceil(t_raycast *r);
void				sprites(void);
void				minimap(int offsetx, int offsety, int thickness);

// mlx
t_mlx_img			*new_img(char *path);
int					color_to_int(int r, int g, int b);
void				put_pix(int x, int y, int color, int thickness);
void				put_line(int x, int start, int end, int color);
// sprites
void				sort_sprites(void);
void				draw_sprites(void);
int					get_color(t_mlx_img *img, int x, int y);

//lists
void				free_content(void *content);
t_list				*get_node(size_t pos, t_list *first);

//tools
void				remove_endtrails(char *str);
int					is_spaces_line(char *str);
t_list				*get_node(size_t pos, t_list *first);
void				empty_function(void);

//debug
void				debug_print_map(void);
void				debug_print_info(void);

#endif
