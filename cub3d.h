//
// Created by YoungHo on 2021/03/20.
//

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>

#include "mlx/mlx.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE		3
# define X_EVENT_EXIT			17

#define KEY_ESC			53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define KEY_LEFT			123
# define KEY_RIGHT			124

# define ERROR 0
# define SUCCESS 1

# define VISITED	9

#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#define NO 0
#define SO 1
#define WE 2
#define EA 3
#define S  4
#define TEX_WALL_NUM 5

#define MALLOC 1


//parameters for scaling and moving the sprites
//uDiv = 2, vDiv = 2, vMove = 0.0 일 때 스프라이트는 절반 크기
#define uDiv 1
#define vDiv 1
#define vMove 0.0

typedef struct		s_xy {
	double x;
	double y;
}					t_xy;

typedef struct		s_int_xy {
	int x;
	int y;
}					t_int_xy;

typedef struct 	s_ray {
	int		side;
	double	perp_wall_dist;
	t_xy	ray_dir;
	t_xy	step; // 밫의 방향을 어디로 쐇는지 기록. 오른쪽? 왼쪽? 아래? 위? //칸을 이동하는 방향.
	t_xy	delta_dist; // 1칸의 광선의 이동거리. delta_dist.x x한칸당 이동거리. / delta_dist.y y한칸당 이동거리
	t_xy	side_dist; // 맨처음만나는 x, y값의 거리
	t_xy	map;
}				t_ray;

typedef struct s_read_check
{
	int	r;
	int	no;
	int	so;
	int	we;
	int ea;
	int	s;
	int	f;
	int	c;
}				t_read_check;


typedef struct		s_key {
	int w;
	int a;
	int s;
	int d;
	int l;
	int r;
}					t_key;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	// 커스텀. 폭, 높이
	int			width;
	int			height;

	//You don't need to understand the 3 values below.
	//After declaration, it will be automatically initialized when passed to mlx_get_data_addr function.
	//아래 3개 값은 이해 안해도 사용하는데 지장이 없음.
	//선언한뒤 함수의 인자로만 잘 넣어주면 알아서 정보를 받아나옴.
	int			size_line;
	int			bpp;
	int			endian;
}				t_img;

typedef struct s_texture
{
	char	*texture_path; //저장경로.
	int		*texture;
} t_texture;

typedef struct s_sprite_calc
{
	t_xy transform;
	double invDet;
	int screen_x;
	int vMoveScreen;
	int spriteHeight;
	int drawStartY;
	int drawStartX;
	int drawEndY;
	int drawEndX;
	int spriteWidth;
	int d;
	int texY;
	int texX;
	int color;
} t_sprite_calc;

typedef struct s_color
{
	int red;
	int green;
	int blue;
} t_color;

typedef struct s_dir_check
{
	int w;
	int n;
	int s;
	int e;
} t_dir_check;

typedef struct s_map_check
{
	t_int_xy map_size;
	int **map;
	t_int_xy dir[4];
	int result;
} t_map_check;

typedef struct t_malloc
{
	int f_texture_path;
	int f_map;
	int f_mlx;
	int f_sprite;
	int f_buf;
	int f_z_buf;
	int f_texture;
} t_malloc;

typedef struct		s_info
{
	void			*mlx_ptr;
	void			*win;
	t_xy	dir; //방향
	t_xy	pos; //위치
	t_xy	plane; //오른쪽 blue 끝점.

	// 키보드.
	t_key	key;

	t_xy	move; //움직임? => 키보드 눌릴 시 사용.

	double	move_speed;
	double	rotate_speed; // 회전시 필요.

	t_img	img;
	int		**buf;

	t_texture texture[5];

	int		floor_color;
	int		ceil_color;

	int		**world_map;
	int		map_width;
	int		map_height;

	t_read_check	read_check;
	t_dir_check		dir_check;

	int win_x;
	int win_y;

	double	*z_buf;

	t_xy *sprite;
	int sprite_count;
	int *sprite_order;
	double *sprite_distance;

	int	screenshot_flag;
	char *map_path;

	t_malloc malloc;
}					t_info;

typedef struct s_wall_calc
{
	int lineHeight;
	int drawStart;
	int drawEnd;
	double wallX; // 벽과 double  거리
	double step_;
	int		texY;
	int		texX;
	double	texPos;
	int		color;
} t_wall_calc;

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

int		get_next_line(int fd, char **line);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int		cub3d(int fd, char **line);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int digit_in_str(char *str);


void read_map(t_info *info, char *map_path);

int		init_identifier(t_info *info, int fd);
int identifier_fc(t_info *info, char** list);
void identifier_fc_check(t_info *info, char** list);
void identifier_texture_check(t_info *info, char** list);
int identifier_texture(t_info *info, char** list);
int		identifier_r(t_info *info, char** list);

int		init_map(t_info *info, int fd);
void free_2d_malloc(char **s);
int is_map(int c);
int is_map_in_line(char *line);
void set_xy(t_xy *xy, double x, double y);
void set_int_xy(t_int_xy *xy, int x, int y);

void count_map_width_height(t_info *info, char *line);
void init_dir_duplicate(t_info *info);
int check_dir_duplicate(t_info *info);
void count_dir_duplicate(t_info *info, const char *line);
void check_list_init(t_info *info);

char *move_map_line(int fd);
int read_map_end_line(int fd, char *line, int i);
int read_map_line(t_info *info, int fd, char *line);

int		load_textures(t_info *info);

void	calc_ray(t_info *info, t_ray *ray, int x);
void	draw_wall(t_info *info, t_ray *ray, int x);

void free_texture_path(t_info *info);

void draw_sprites(t_info *info);

void add_sprite_pos(t_info *info);
void draw_ceiling(t_info *info, int x, t_wall_calc w);
void draw_floor(t_info *info, int x, t_wall_calc w);
int map_check(int **src_map, t_xy pos, int map_y, int map_x);

void move_front_back(t_info *info);
void move_left_right(t_info *info);

void arg_parse(t_info *info, int argc, char *argv[]);

void screenshot(t_info *info);
void	ft_bzero(void *s, size_t n);

int		key_press(int keycode, t_info *info);
int		key_release(int keycode, t_info *info);
void	rotate(t_info *info);

int	exit_all(t_info *info, char *msg, int status);

int		count_sprite(t_info *info);
/*
 * malloc / free
*/
int ** malloc_map(t_info *info);
void free_map(t_info *info);

int malloc_sprite(t_info *info);
void free_sprite(t_info *info);

int	malloc_buf(t_info *info);
void free_buf(t_info *info);

int malloc_z_buf(t_info *info);
void free_z_buf(t_info *info);

int malloc_texture(t_info *info);
void free_texture(t_info *info);

#endif
