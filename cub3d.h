/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 05:35:48 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 06:17:23 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx/mlx.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_EXIT			17

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define KEY_LEFT			123
# define KEY_RIGHT			124

# define ERROR 		0
# define SUCCESS 	1

# define VISITED	9

# define TEX_WIDTH 	64
# define TEX_HEIGHT 64

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define S  4
# define TEX_WALL_NUM 5

# define MALLOC 1

# define UDIV	1
# define VDIV	1
# define VMOVE	0.0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_xy {
	double	x;
	double	y;
}	t_xy;

typedef struct s_int_xy {
	int	x;
	int	y;
}	t_int_xy;

typedef struct s_ray {
	int		side;
	double	perp_wall_dist;
	t_xy	ray_dir;
	t_xy	step;
	t_xy	delta_dist;
	t_xy	side_dist;
	t_xy	map;
}	t_ray;

typedef struct s_read_check
{
	int	r;
	int	no;
	int	so;
	int	we;
	int	ea;
	int	s;
	int	f;
	int	c;
}	t_read_check;

typedef struct s_key {
	int	w;
	int	a;
	int	s;
	int	d;
	int	l;
	int	r;
}	t_key;

typedef struct s_img
{
	void		*img_ptr;
	int			*data;
	int			width;
	int			height;
	int			size_line;
	int			bpp;
	int			endian;
}	t_img;

typedef struct s_texture
{
	char	*texture_path;
	int		*texture;
}	t_texture;

typedef struct s_sprite_calc
{
	t_xy	transform;
	double	invDet;
	int		screen_x;
	int		vMoveScreen;
	int		spriteHeight;
	int		drawStartY;
	int		drawStartX;
	int		drawEndY;
	int		drawEndX;
	int		spriteWidth;
	int		d;
	int		texY;
	int		texX;
	int		color;
}	t_sprite_calc;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_dir_check
{
	int	w;
	int	n;
	int	s;
	int	e;
}	t_dir_check;

typedef struct s_map_check
{
	t_int_xy	map_size;
	int			**map;
	t_int_xy	dir[4];
	int			result;
}	t_map_check;

typedef struct s_malloc
{
	int	f_texture_path;
	int	f_map;
	int	f_mlx;
	int	f_sprite;
	int	f_buf;
	int	f_z_buf;
	int	f_texture;
}	t_malloc;

typedef struct s_info
{
	void			*mlx_ptr;
	void			*win;

	t_xy			dir;
	t_xy			pos;
	t_xy			plane;
	t_key			key;

	t_xy			move;
	double			move_speed;
	double			rotate_speed;

	t_img			img;
	int				**buf;
	t_texture		texture[5];

	int				floor_color;
	int				ceil_color;

	int				**world_map;

	int				map_width;
	int				map_height;
	char			*map_path;

	t_read_check	read_check;
	t_dir_check		dir_check;

	int				win_x;
	int				win_y;

	double			*z_buf;
	t_xy			*sprite;
	int				sprite_count;
	int				*sprite_order;
	double			*sprite_distance;

	int				screenshot_flag;

	t_malloc		malloc;
}	t_info;

typedef struct s_wall_calc
{
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	double	wallX;
	double	step_;
	int		texY;
	int		texX;
	double	texPos;
	int		color;
}	t_wall_calc;

typedef struct s_pair
{
	double	first;
	int		second;
}	t_pair;

// GNL
int		get_next_line(int fd, char **line);

// utils
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		digit_in_str(char *str);
void	set_xy(t_xy *xy, double x, double y);
void	set_int_xy(t_int_xy *xy, int x, int y);
void	free_2d_malloc(char **s);
void	ft_bzero(void *s, size_t n);

// config
void	arg_parse(t_info *info, int argc, char *argv[]);
void	read_map(t_info *info, char *map_path);
void	screen_check(t_info *info);
void	init_info(t_info *info);
void	init_dir_duplicate(t_info *info);
int		check_dir_duplicate(t_info *info);
void	count_dir_duplicate(t_info *info, const char *line);
int		load_textures(t_info *info);

// config - identifier
int		init_identifier(t_info *info, int fd);
int		identifier_fc(t_info *info, char **list);
void	identifier_fc_check(t_info *info, char **list);
void	identifier_texture_check(t_info *info, char **list);
int		identifier_texture(t_info *info, char **list);
int		identifier_r(t_info *info, char **list);
void	check_list_init(t_info *info);

// config - map
int		init_map(t_info *info, int fd);
char	*move_map_line(int fd);
int		is_map(int c);
int		is_map_in_line(char *line);
int		read_map_end_line(int fd, char *line, int i);
int		read_map_line(t_info *info, int fd, char *line);
int		dfs(t_map_check *m, int y, int x);
void	count_map_width_height(t_info *info, char *line);
int		map_check(int **src_map, t_xy pos, int map_y, int map_x);

// core
void	calc_ray(t_info *info, t_ray *ray, int x);
void	draw_wall(t_info *info, t_ray *ray, int x);
void	draw_sprites(t_info *info);
void	draw_ceiling(t_info *info, int x, t_wall_calc w);
void	draw_floor(t_info *info, int x, t_wall_calc w);
int		exit_all(t_info *info, char *msg, int status);

// core - sprite
void	sort_order(t_pair *orders, int amount);
void	sort_sprites(int *order, double *dist, int amount);
void	add_sprite_pos(t_info *info);
int		count_sprite(t_info *info);

// core - key events
void	move_front_back(t_info *info);
void	move_left_right(t_info *info);
int		key_press(int keycode, t_info *info);
int		key_release(int keycode, t_info *info);
void	rotate(t_info *info);

// core - save options
void	screenshot(t_info *info);

// malloc & free
int		**malloc_map(t_info *info);
void	free_map(t_info *info);

int		malloc_sprite(t_info *info);
void	free_sprite(t_info *info);

int		malloc_buf(t_info *info);
void	free_buf(t_info *info);

int		malloc_z_buf(t_info *info);

int		malloc_texture(t_info *info);
void	free_texture(t_info *info);

void	init_malloc_flag(t_info *info);

void	free_texture_path(t_info *info);

#endif
