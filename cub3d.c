//
// Created by YoungHo on 2021/03/20.
//

#include <math.h>
#include <fcntl.h>
#include "cub3d.h"

void map_validation();

int main_loop();

int key_release();





void draw_wall(t_info *info, t_ray *ray, int x);


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
		info->key.s = 1;
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
		info->key.s = 0;
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
int	worldMap[mapWidth][mapHeight] =
		{
				{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
				{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
				{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
				{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
				{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
				{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
				{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
				{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
				{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
				{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
				{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
				{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
				{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
				{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
				{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
				{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
				{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
				{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
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
	info->move_speed = 0.05;
	info->rotate_speed = 0.05;

	// 키보드 초기화.
	info->key.w = 0;
	info->key.a = 0;
	info->key.s = 0;
	info->key.d = 0;

//	//벽, 땅 색깔 초기화
//	info->ceil_color = rgb_to_int(120,120,0);
//	info->floor_color = rgb_to_int(0,120,120);
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


//void	load_image(t_info *info, int *textures, char *path, t_img *img)
//{
//	img->img_ptr = mlx_xpm_file_to_image(info->mlx_ptr, path, &img->width, &img->height);
//	img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
//	for (int y = 0; y < img->height; y++)
//	{
//		for (int x = 0; x < img->width; x++)
//		{
//			textures[img->width * y + x] = img->data[img->width * y + x];
//		}
//	}
//	mlx_destroy_image(info->mlx_ptr, img->img_ptr); // 배열에 저장했으므로 포인터 제거.
//}
//
//void	load_textures(t_info *info)
//{
//	t_img	img;
//
//	load_image(info, info->textures[0], "textures/eagle.xpm", &img); // 동
//	load_image(info, info->textures[1], "textures/redbrick.xpm", &img); //서
//	load_image(info, info->textures[2], "textures/purplestone.xpm", &img); //남
//	load_image(info, info->textures[3], "textures/greystone.xpm", &img); // 북
//	load_image(info, info->textures[4], "textures/bluestone.xpm", &img); // sprite?
//	load_image(info, info->textures[5], "textures/mossy.xpm", &img);
//	load_image(info, info->textures[6], "textures/wood.xpm", &img);
//	load_image(info, info->textures[7], "textures/colorstone.xpm", &img);
//}

void	calc_ray(t_info *info, t_ray *ray, int x)
{
	double K = 2 * x / (double)WIN_WIDTH - 1; // -1 ~ 1 로 정규화. 0 일떄 -1 / x가 최대값이면 2 - 1 = 1

	//ray의 방향. plane의 k배수
	set_xy(&ray->ray_dir,info->dir.x + info->plane.x * K, info->dir.y + info->plane.y * K);

	//내림을 통해 내 현재 광선 위치.
	set_xy(&ray->map, (int)info->pos.x, (int)info->pos.y);

	set_xy(&ray->delta_dist, fabs(1. / ray->ray_dir.x), fabs(1. / ray->ray_dir.y));

	t_xy side_dist; // 맨처음만나는 x, y값의 거리

	if (ray->ray_dir.x < 0) // 왼쪽 방향으로 쐇다.
	{
		ray->step.x = -1; //x가 음의 방향인가?
		side_dist.x = (info->pos.x - ray->map.x) * ray->delta_dist.x; //플레이어 - 맵.
	}
	else
	{
		ray->step.x = 1; //x가 양의 방향인가?
		side_dist.x = (ray->map.x + 1.0 - info->pos.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		side_dist.y = (info->pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		side_dist.y = (ray->map.y + 1.0 - info->pos.y) * ray->delta_dist.y;
	}

	//DDA 알고리즘
	int hit = 0;
	//칸수 체크하면서 hit되었는지 봄.
	while (hit == 0)
	{
		// y가 더 가파른 경우. y의 증가폭이 큰경우. x를 1씩 증가시켜야함.
		if(side_dist.x < side_dist.y)
		{
			side_dist.x += ray->delta_dist.x; //다음번 x선을 만날떄까지 길이를 계속 더해줌.
			ray->map.x += (int)ray->step.x; //오른쪽으로 x가 움직이는지 왼쪽으로 움직이는지. 기울기가 음수 양수
			ray->side = 0; //세로선과 부딪힘.  //위아래선이냐, 오른쪽 왼쪽 선이냐
		}
		else {
			side_dist.y += ray->delta_dist.y; //다음번 y선을 만날떄까지 길이를 계속 더해줌
			ray->map.y += (int)ray->step.y;//ray 오른쪽으로 왼쪽으로 움직이는지. 기울기가 음수 양수
			ray->side = 1; // 가로선과 부딪힘.
		}
		if (worldMap[(int)ray->map.x][(int)ray->map.y] > 0) // 벽은 1로 표현되어짐. todo
			hit = 1;
	}

	//레이에서 hit되었을때 카메라 평면과의 수선의 발의 길이. 둥글게 보임.
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map.x - info->pos.x + (1 - ray->step.x) / 2) / ray->ray_dir.x; //step은 1
	else
		ray->perp_wall_dist = (ray->map.y - info->pos.y + (1 - ray->step.y) / 2) / ray->ray_dir.y;
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

void	put_draw(t_info *info)
{
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			info->img.data[y * WIN_WIDTH + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win, info->img.img_ptr, 0, 0);
}

void draw_floor_ceiling(t_info *info, t_ray *ray, int x)
{
	//255, 255, 255
	int y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		//바닥.
		info->buf[y][x] = info->floor_color;
		//천장
		info->buf[WIN_HEIGHT - y - 1][x] = info->ceil_color;
	}
}


int main_loop(t_info *info)
{

	//keyboard rotate
	if (info->key.w || info->key.s)
		move(info);
	if (info->key.a || info->key.d)
		rotate(info);

	t_ray	ray;
	int x;

	x = -1; // 0 ~ 최대폭 까지
	while (++x < WIN_WIDTH)
	{
		draw_floor_ceiling(info, &ray, x);
		calc_ray(info, &ray, x);	// init ray
		draw_wall(info, &ray, x); // 벽 그리기.
	}

	put_draw(info);

	//update 로직. 키가 업데이트 되었을때 화면을 바꿔야함.
	//		update_screen(game);
	//		update_window(game);
	return (0);
}

void draw_wall(t_info *info, t_ray *ray, int x) {
// win 높이를 사용해서 벽의 높이를 구함
	int lineHeight = (int)(WIN_HEIGHT / ray->perp_wall_dist); //거리에 반비례.

	//텍스쳐의 시작 위치로 활용가능.
	int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if(drawStart < 0) // 시작 위치가 음수일경우 0부터 그리도록.
		drawStart = 0;
	int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2; // 끝나는 높이 좌표.
	if(drawEnd >= WIN_HEIGHT) // 높이가 초과될경우 화면의 가장 끝에 보이도록.
		drawEnd = WIN_HEIGHT - 1;

	// 0번째 텍스쳐도 0, 벽이 없는것도 0 => 1이면 texNum이 0 이되어 텍스쳐 종류를 가르킴.
	int texNum = worldMap[(int)ray->map.x][(int)ray->map.y] - 1;

	// 벽과 double  거리
	double wallX;
	if (ray->side == 0)
		wallX = info->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		wallX = info->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	wallX -= floor(wallX);

	// x coordinate on the texture
	// 벽과 거리와 텍스쳐 두께를 이용해 texX를 구함.
	int texX = (int)(wallX * (double)texWidth);
	if (ray->side == 0 && ray->ray_dir.x > 0)
		texX = texWidth - texX - 1;
	if (ray->side == 1 && ray->ray_dir.y < 0)
		texX = texWidth - texX - 1;

	// How much to increase the texture coordinate perscreen pixel
	double step_ = 1.0 * texHeight / lineHeight; // 2.0으로 할경우 벽이 가로 두개로 나뉘어짐.

	//텍스쳐의 위치.
	double texPos = (drawStart - WIN_HEIGHT / 2 + lineHeight / 2) * step_;
	for (int y = drawStart; y < drawEnd; y++) // y좌표를 그린다.
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (texHeight - 1);
		texPos += step_;
		int color = info->textures[texNum][texHeight * texY + texX]; // 위치에 맞는 데이터를 가져옴.
		// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if (ray->side == 1) // y벽면에 부딪히는경우. 색을 어둡게.
			color = (color >> 1) & 8355711;
		info->buf[y][x] = color;
	}
}

int			main(int argc, char *argv[])
{
	t_info	info;

	// 인자가 두개 이상왔는데, save가 옵션이 아닐경우. 종료
	if (argc >= 3 && ft_strcmp(argv[2] , "--save")) //2번쨰 인자가 올경우
		exit(0);
	if (argc == 1) // 인자가 아무것도 없으면 종료.
		exit(0);
	//map_init(&info, argv[1]); //맵 초기화
	read_map(&info, "./map.cub");
	/*

init_info(&info);

//텍스쳐가 스크린 사이즈 버퍼. => 버퍼에 저장해놓고 그림.
for (int i = 0; i < WIN_HEIGHT; i++)
{
for (int j = 0; j < WIN_WIDTH; j++)
{
	info.buf[i][j] = 0;
}
}

// 텍스쳐 사이즈 생성. 동적할당. todo free
if (!(info.texture = (int **)malloc(sizeof(int *) * 8)))
return (-1);
for (int i = 0; i < 8; i++)
{
if (!(info.texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
	return (-1);
}
for (int i = 0; i < 8; i++)
{
for (int j = 0; j < texHeight * texWidth; j++)
{
	info.texture[i][j] = 0;
}
}

load_texture(&info);
info.img.img_ptr = mlx_new_image(info.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
info.img.data = (int *)mlx_get_data_addr(info.img.img_ptr, &info.img.bpp, &info.img.size_line, &info.img.endian);

//키 이벤트, 키 함수.
mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
mlx_hook(info.win, X_EVENT_KEY_release, 0, &key_release, &info);

//
mlx_loop_hook(info.mlx_ptr, &main_loop, &info);

// 시작.
mlx_loop(info.mlx_ptr);
*/
	return (0);
}



//dfs 로 유효성 검사void map_validation() {
	//맵에 대한 검증.

//}

//https://harm-smits.github.io/42docs/libs/minilibx/prototypes.html#mlx_get_screen_size
//int   *ft_screen_check(t_all *s)
//{
//	int max_x;
//	int max_y;
//	mlx_get_screen_size(s->mlx.ptr, &max_x, &max_y);
//	if (max_x < s->win.x)
//		s->win.x = max_x;
//	if (max_y < s->win.y)
//		s->win.y = max_y;
//	return (mlx_new_window(s->mlx.ptr, s->win.x, s->win.y, “cub3D”));
//}