//
// Created by YoungHo on 2021/03/20.
//

#include <math.h>
#include "cub3d.h"

void map_init();

void map_validation();

int main_loop();

int key_release();

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

#define mapWidth 24
#define mapHeight 24



typedef struct		s_xy {
	double x;
	double y;
}					t_xy;

typedef struct		s_key {
	int w;
	int a;
	int s;
	int d;
}					t_key;

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

}					t_info;

typedef struct	s_camera
{
	t_xy	pos;
	t_xy	dir;
	t_xy	x_dir;
	t_xy	plane;
}				t_camera;

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

void exit_game()
{

}


//keycode는 내가 누른 키보드 입력값.
int				key_press(int keycode, t_info *info) {
	static int a = 0;

	if (keycode == KEY_ESC) //프로그램 종료.
		exit(0);
	else if (keycode == KEY_W)
		info->key.w = 1;
	else if (keycode == KEY_A)
		info->key.a = 1;
	else if (keycode == KEY_S)
		info->key.w = 1;
	else if (keycode == KEY_D)
		info->key.d = 1;
	return (0);
}

//키보드를 땠을때.
int key_release(int keycode, t_info *info) {
	if (keycode == KEY_ESC) //프로그램 종료.
		exit(0);
	else if (keycode == KEY_W)
		info->key.w = 0;
	else if (keycode == KEY_A)
		info->key.a = 0;
	else if (keycode == KEY_S)
		info->key.w = 0;
	else if (keycode == KEY_D)
		info->key.d = 0;
	return (0);
}

//	// W 버튼일때 x증가.
//	if (keycode == KEY_W)//Action when W key pressed
//		param->x++;
//	else if (keycode == KEY_S) //s키 일때,
//		param->x--;
//	else if (keycode == KEY_A)

// 눌리고 있을때로 추정됨.
//int		key_release(int key, t_info *info)
//{
//
//}

// 2차원 배열의 맵.
int worldMap[mapWidth][mapHeight]=
{
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void set_xy(t_xy *xy, double x, double y)
{
	xy->x = x;
	xy->y = y;
}

//t_xy	dir; //방향
//t_xy	pos; //위치
//t_xy	plane; //평면
//t_xy	move; //움직임? => 키보드 눌릴 시 사용.
//t_xy	x_move; // x축 움직임? => 키보드 눌릴 시 사용.
//t_xy	rotate; // 회전시 필요


void init_info(t_info *info)
{
	//mlx초기화, 윈도우초기화
	if (!(info->mlx_ptr = mlx_init()) || !(info->win = mlx_new_window(
			info->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d")))
		exit(0); //실패시 종료
	set_xy(&info->pos, 12, 5); // 현재 위치.

	// 보고 있는 방향. 카메라 평면
	set_xy(&info->dir, -1, 0); //방향
	set_xy(&info->plane, 0, 0.66);

	set_xy(&info->move, 0, 0);
	set_xy(&info->x_move, 0, 0);

	//회전 및 움직임 정도.
	info->move_speed = 0.5;
	info->rotate_speed = 0.05;

	// 키보드 초기화.
	info->key.w = 0;
	info->key.a = 0;
	info->key.s = 0;
	info->key.d = 0;

}

//x의 위치에서 세로로쭉 pixel을 하나씩 찍어주는 함수.
void	verLine(t_info *info, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(info->mlx_ptr, info->win, x, y, color);
		y++;
	}
}

// 맵 체크. 리턴 1
int map_check()
{

	//# define IN_MAP(p, c)		(CHECK_TOP(p) && CHECK_BOT(p, c))

	//# define CHECK_TOP(p)		(FINT(p.x) >= 0 && FINT(p.y) >= 0)
	//# define CHECK_BOT(p, c)	(FINT(p.x) < (c).columns && FINT(p.y) < (c).rows)

	// # define FINT(x)			((int)floor(x))

	//# define MAP(p, c) 			(c).map[(FINT(p.y) * (c).columns) + FINT(p.x)]
	//# define MAP_XY(x, y, c) 	(c).map[(FINT(y) * (c).columns) + FINT(x)]
}

void	calc(t_info *info)
{
	int x;

	x = -1; // 0 ~ 최대폭 까지
	// init ray
	while (++x < WIN_WIDTH)
	{
		double K = 2 * x / (double)WIN_WIDTH - 1; // -1 ~ 1 로 정규화. 0 일떄 -1 / x가 최대값이면 2 - 1 = 1

		//ray의 방향. plane의 k배수
		t_xy ray_dir;
		set_xy(&ray_dir,info->dir.x + info->plane.x * K, info->dir.y + info->plane.y * K);

		//내림을 통해 내 현재 광선 위치.
		int mapX = (int)info->pos.x;
		int mapY = (int)info->pos.y;

		t_xy delta_dist; // 1칸의 광선의 이동거리. delta_dist.x x한칸당 이동거리. / delta_dist.y y한칸당 이동거리
		set_xy(&delta_dist, fabs(1. / ray_dir.x), fabs(1. / ray_dir.y));

		t_xy side_dist; // 맨처음만나는 x, y값의 거리

		// 밫의 방향을 어디로 쐇는지 기록. 오른쪽? 왼쪽? 아래? 위? //칸을 이동하는 방향.
		t_xy step;
		if (ray_dir.x < 0) // 왼쪽 방향으로 쐇다.
		{
			step.x = -1; //x가 음의 방향인가?
			side_dist.x = (info->pos.x - mapX) * delta_dist.x; //플레이어 - 맵.
		}
		else
		{
			step.x = 1; //x가 양의 방향인가?
			side_dist.x = (mapX + 1.0 - info->pos.x) * delta_dist.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_dist.y = (info->pos.y - mapY) * delta_dist.y;
		}
		else
		{
			step.y = 1;
			side_dist.y = (mapY + 1.0 - info->pos.y) * delta_dist.y;
		}

		//DDA 알고리즘
		int hit = 0;
		int side; //위아래선이냐, 오른쪽 왼쪽 선이냐
		//칸수 체크하면서 hit되었는지 봄.
		while (hit == 0)
		{
			// y가 더 가파른 경우. y의 증가폭이 큰경우. x를 1씩 증가시켜야함.
			if(side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x; //다음번 x선을 만날떄까지 길이를 계속 더해줌.
				mapX += (int)step.x; //오른쪽으로 x가 움직이는지 왼쪽으로 움직이는지. 기울기가 음수 양수
				side = 0; //세로선과 부딪힘.
			}
			else {
				side_dist.y += delta_dist.y; //다음번 y선을 만날떄까지 길이를 계속 더해줌
				mapY += (int)step.y;//ray 오른쪽으로 왼쪽으로 움직이는지. 기울기가 음수 양수
				side = 1; // 가로선과 부딪힘.
			}
			if (worldMap[mapX][mapY] > 0) // 벽은 1로 표현되어짐. todo
				hit = 1;
		}

		//레이에서 hit되었을때 카메라 평면과의 수선의 발의 길이. 둥글게 보임.
		double perpWallDist;

		if (side == 0)
			perpWallDist = (mapX - info->pos.x + (1 - step.x) / 2) / ray_dir.x; //step은 1
		else
			perpWallDist = (mapY - info->pos.y + (1 - step.y) / 2) / ray_dir.y;

		// win 높이를 사용해서 벽의 높이를 구함
		int lineHeight = (int)(WIN_HEIGHT / perpWallDist); //거리에 반비례.

		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if(drawStart < 0) // 시작 위치가 음수일경우 0부터 그리도록.
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2; // 끝나는 높이 좌표.
		if(drawEnd >= WIN_HEIGHT) // 높이가 초과될경우 화면의 가장 끝에 보이도록.
			drawEnd = WIN_HEIGHT - 1;

		int	color;
		if (worldMap[mapY][mapX] == 1)
			color = 0xFF0000;
		else if (worldMap[mapY][mapX] == 2)
			color = 0x00FF00;
		else if (worldMap[mapY][mapX] == 3)
			color = 0x0000FF;
		else if (worldMap[mapY][mapX] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;

		//색상 값 조절.
		if (side == 1)
			color = color / 2;

		verLine(info, x, drawStart, drawEnd, color);
	}
}

//key_event.c todo
//회전 행렬을 곱해야함. 방향벡터와 카메라평면벡터 둘 다 회전
void rotate(t_info *info)
{
	int flag;
	double old;

//	if (info->key.a)
//		flag = 1;
//	else
//		flag = -1;
	// 오른쪽이면
	flag = info->key.a == 1 ? 1 : -1;

	//방향벡터 회전
	old = info->dir.x;
	info->dir.x = info->dir.x * cos(info->rotate_speed * flag)
			- info->dir.y * sin(info->rotate_speed * flag);
	info->dir.y = old * sin(info->rotate_speed * flag)
			+ info->dir.y * cos(info->rotate_speed * flag);

	old = info->plane.x;
	info->plane.x = info->plane.x * cos(info->rotate_speed * flag)
				  - info->plane.y * sin(info->rotate_speed * flag);
	info->plane.y = old * sin(info->rotate_speed * flag)
				  + info->plane.y * cos(info->rotate_speed * flag);

	//	double oldDirX = dirX;
	//	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
	//	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
	//	double oldPlaneX = planeX;
	//	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
	//	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
}

//위 아래로 움직여야함.
void move(t_info *info)
{

	if (info->key.w)
	{
		if (!worldMap[(int)(info->pos.x + info->dir.x * info->move_speed)][(int)(info->pos.y)])
			info->pos.x += info->dir.x * info->move_speed;
		if (!worldMap[(int)(info->pos.x)][(int)(info->pos.y + info->dir.y * info->move_speed)])
			info->pos.y += info->dir.y * info->move_speed;
	}
	else if (info->key.s)
	{
		if (!worldMap[(int)(info->pos.x - info->dir.x * info->move_speed)][(int)(info->pos.y)])
			info->pos.x -= info->dir.x * info->move_speed;
		if (!worldMap[(int)(info->pos.x)][(int)(info->pos.y - info->dir.y * info->move_speed)])
			info->pos.y -= info->dir.y * info->move_speed;
	}
}


int main_loop(t_info *info)
{

	//keyboard rotate
	if (info->key.a || info->key.d)
		rotate(info);
	else if (info->key.w || info->key.s)
		move(info);



	calc(info);
	//update 로직. 키가 업데이트 되었을때 화면을 바꿔야함.
	//		update_screen(game);
	//		update_window(game);
	return (0);
}

int			main(void)
{
	t_info	info;
	int		count_w;
	int		count_h;
	t_img	img;

	map_init(); //맵 초기화
	init_info(&info);

	//키 이벤트, 키 함수.
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_release, 0, &key_release, &info);

	//
	mlx_loop_hook(info.mlx_ptr, &main_loop, &info);

	// 시작.
	mlx_loop(info.mlx_ptr);
	return (0);
}



void map_init() {
	//맵초기화.

	map_validation(); //맵에 대한 검증.
}

void map_validation() {
	//맵에 대한 검증.

}





