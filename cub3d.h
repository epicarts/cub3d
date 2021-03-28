//
// Created by YoungHo on 2021/03/20.
//

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

#include "mlx/mlx.h"

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_release		3
#define X_EVENT_KEY_EXIT		17 //exit key code

#define KEY_ESC			53
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define KEY_LEFT			123
# define KEY_DOWN			125
# define KEY_RIGHT			124
# define KEY_UP				126

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

#define mapWidth 24
#define mapHeight 24

#define texWidth 64
#define texHeight 64


typedef struct		s_xy {
	double x;
	double y;
}					t_xy;

typedef struct 	s_ray {
	int		side;
	double	perp_wall_dist;
	t_xy	ray_dir;
	t_xy	step; // 밫의 방향을 어디로 쐇는지 기록. 오른쪽? 왼쪽? 아래? 위? //칸을 이동하는 방향.
	t_xy	delta_dist; // 1칸의 광선의 이동거리. delta_dist.x x한칸당 이동거리. / delta_dist.y y한칸당 이동거리
	t_xy	map;
}				t_ray;


typedef struct		s_key {
	int w;
	int a;
	int s;
	int d;
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
	t_xy	x_move; // x축 움직임? => 키보드 눌릴 시 사용. 뭘까

	double	move_speed;
	double	rotate_speed; // 회전시 필요.

	t_img	img;
	int		buf[WIN_HEIGHT][WIN_WIDTH];
	int		**texture;

}					t_info;

typedef struct	s_camera
{
	t_xy	pos;
	t_xy	dir;
	t_xy	x_dir;
	t_xy	plane;
}				t_camera;



int		cub3d(int fd, char **line);


#endif
