//
// Created by YoungHo on 2021/03/20.
//

#include <math.h>
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
	else if (keycode == KEY_LEFT)
		info->key.l = 1;
	else if (keycode == KEY_RIGHT)
		info->key.r = 1;
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
	else if (keycode == KEY_LEFT)
		info->key.l = 0;
	else if (keycode == KEY_RIGHT)
		info->key.r = 0;
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
	info->key.l = 0;
	info->key.r = 0;

//	//벽, 땅 색깔 초기화
//	info->ceil_color = rgb_to_int(120,120,0);
//	info->floor_color = rgb_to_int(0,120,120);
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
	flag = info->key.l == 1 ? 1 : -1;

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
		if (!info->world_map[(int)(info->pos.x + info->dir.x * info->move_speed)][(int)(info->pos.y)])
			info->pos.x += info->dir.x * info->move_speed;
		if (!info->world_map[(int)(info->pos.x)][(int)(info->pos.y + info->dir.y * info->move_speed)])
			info->pos.y += info->dir.y * info->move_speed;
	}
	else if (info->key.s)
	{
		if (!info->world_map[(int)(info->pos.x - info->dir.x * info->move_speed)][(int)(info->pos.y)])
			info->pos.x -= info->dir.x * info->move_speed;
		if (!info->world_map[(int)(info->pos.x)][(int)(info->pos.y - info->dir.y * info->move_speed)])
			info->pos.y -= info->dir.y * info->move_speed;
	}
	else if (info->key.d)
	{
		if (!info->world_map[(int)(info->pos.x)][(int)(info->pos.y - info->dir.x * info->move_speed)])
			info->pos.y -= info->dir.x * info->move_speed;
		if (!info->world_map[(int)(info->pos.x + info->dir.y * info->move_speed)][(int)(info->pos.y)])
			info->pos.x += info->dir.y * info->move_speed;
	}
	else if (info->key.a)
	{
		if (!info->world_map[(int)(info->pos.x)][(int)(info->pos.y + info->dir.x * info->move_speed)])
			info->pos.y += info->dir.x * info->move_speed;
		if (!info->world_map[(int)(info->pos.x - info->dir.y * info->move_speed)][(int)(info->pos.y)])
			info->pos.x -= info->dir.y * info->move_speed;
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

void draw_sprite(t_info *info)
{
	//SPRITE CASTING
	//sort sprites from far to close
	//translate sprite position to relative to camera
	double spriteX = 2.5 - info->pos.x;
	double spriteY = 2.5 - info->pos.y;

	//transform sprite with the inverse camera matrix
	// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
	// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
	// [ planeY   dirY ]                                          [ -planeY  planeX ]

	double invDet = 1.0 / (info->plane.x * info->dir.y - info->dir.x * info->plane.y); //required for correct matrix multiplication

	double transformX = invDet * (info->dir.y * spriteX - info->dir.x * spriteY);
	double transformY = invDet * (-info->plane.y * spriteX + info->plane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

	int spriteScreenX = (int)((WIN_WIDTH / 2) * (1 + transformX / transformY));

	//parameters for scaling and moving the sprites
	#define uDiv 1
	#define vDiv 1
	#define vMove 0.0
	int vMoveScreen = (int)(vMove / transformY);

	//calculate height of the sprite on screen
	int spriteHeight = (int)fabs((WIN_HEIGHT / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
	//calculate lowest and highest pixel to fill in current stripe
	int drawStartY = -spriteHeight / 2 + WIN_HEIGHT / 2 + vMoveScreen;
	if(drawStartY < 0) drawStartY = 0;
	int drawEndY = spriteHeight / 2 + WIN_HEIGHT / 2 + vMoveScreen;
	if(drawEndY >= WIN_HEIGHT) drawEndY = WIN_HEIGHT - 1;

	//calculate width of the sprite
	int spriteWidth = (int)fabs((WIN_HEIGHT / transformY) / uDiv);
	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	if(drawStartX < 0) drawStartX = 0;
	int drawEndX = spriteWidth / 2 + spriteScreenX;
	if(drawEndX >= WIN_WIDTH) drawEndX = WIN_WIDTH - 1;

	//loop through every vertical stripe of the sprite on screen
	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
	{
		int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_WIDTH / spriteWidth) / 256);
		//the conditions in the if are:
		//1) it's in front of camera plane so you don't see things behind you
		//2) it's on the screen (left)
		//3) it's on the screen (right)
		//4) ZBuffer, with perpendicular distance
		if(transformY > 0 && stripe > 0 && stripe < WIN_WIDTH && transformY < info->zBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y-vMoveScreen) * 256 - WIN_HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * TEX_HEIGHT) / spriteHeight) / 256;
				int color = info->s_texture.texture[TEX_WIDTH * texY + texX]; //get current color from the texture
				if((color & 0x00FFFFFF) != 0) // 검은색이 아닐경우.
					info->buf[y][stripe] = color; // 픽셀 색깔로 칠함.
			}
	}
}

//void draw_sprite(t_info *info)
//{
//	double spriteX = 1.5 - info->pos.x;
//	double spriteY = 1.5 - info->pos.y;
//
//
//	//transform sprite with the inverse camera matrix
//	// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
//	// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
//	// [ planeY   dirY ]                                          [ -planeY  planeX ]
//
//	double invDet = 1.0 / (info->plane.x * info->dir.y - info->dir.x * info->plane.y); //required for correct matrix multiplication
//
//	double transformX = invDet * (info->dir.y * spriteX - info->dir.x * spriteY);
//	double transformY = invDet * (-info->plane.y * spriteX + info->plane.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])
//
//	int spriteScreenX = (int)((WIN_WIDTH / 2) * (1 + transformX / transformY));
//
//	//parameters for scaling and moving the sprites
//	#define uDiv 1
//	#define vDiv 1
//	#define vMove 0.0
//	int vMoveScreen = (int)(vMove / transformY);
//
//	//calculate height of the sprite on screen
//	int spriteHeight = (int)fabs((WIN_HEIGHT / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
//	//calculate lowest and highest pixel to fill in current stripe
//	int drawStartY = -spriteHeight / 2 + WIN_HEIGHT / 2 + vMoveScreen;
//	if(drawStartY < 0) drawStartY = 0;
//	int drawEndY = spriteHeight / 2 + WIN_HEIGHT / 2 + vMoveScreen;
//	if(drawEndY >= WIN_HEIGHT) drawEndY = WIN_HEIGHT - 1;
//
//	//calculate width of the sprite
//	int spriteWidth = (int)fabs((WIN_HEIGHT / transformY) / uDiv);
//	int drawStartX = -spriteWidth / 2 + spriteScreenX;
//	if(drawStartX < 0) drawStartX = 0;
//	int drawEndX = spriteWidth / 2 + spriteScreenX;
//	if(drawEndX >= WIN_WIDTH) drawEndX = WIN_WIDTH - 1;
//
//	//loop through every vertical stripe of the sprite on screen
//	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
//	{
//		int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEX_WIDTH / spriteWidth) / 256);
//		//the conditions in the if are:
//		//1) it's in front of camera plane so you don't see things behind you
//		//2) it's on the screen (left)
//		//3) it's on the screen (right)
//		//4) ZBuffer, with perpendicular distance
//		if(transformY > 0 && stripe > 0 && stripe < WIN_WIDTH && transformY < info->zBuffer[stripe]) //perpWallDist
//			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
//			{
//				int d = (y-vMoveScreen) * 256 - WIN_HEIGHT * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
//				int texY = ((d * TEX_HEIGHT) / spriteHeight) / 256;
//				int color = info->s_texture.texture[TEX_WIDTH * texY + texX]; //get current color from the texture
//				if((color & 0x00FFFFFF) != 0) info->buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
//			}
//	}
//}

int main_loop(t_info *info)
{

	//keyboard rotate
	if (info->key.w || info->key.s || info->key.a || info->key.d)
		move(info);
	if (info->key.r || info->key.l)
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
	draw_sprite(info);

	put_draw(info);

	//update 로직. 키가 업데이트 되었을때 화면을 바꿔야함.
	//		update_screen(game);
	//		update_window(game);
	return (0);
}



//todo 동적할당으로 지정한 경로 free. 프로그램 종료시 호출
void free_texture_path(t_info *info)
{
	int i;

	i = 0;
	while (i < LOAD_TEX_SIZE)
	{
		free(info->texture[i].texture_path);
		i++;
	}
}
void free_texture(t_info *info)
{
	int i;

	i = 0;
	while (i < LOAD_TEX_SIZE)
	{
		free(info->texture[i].texture);
		i++;
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

	init_info(&info);

	//텍스쳐가 스크린 사이즈 버퍼. => 버퍼에 저장해놓고 그림.
	for (int i = 0; i < WIN_HEIGHT; i++)
	{
		for (int j = 0; j < WIN_WIDTH; j++)
		{
			info.buf[i][j] = 0;
		}
	}

	if (init_texture(&info))
	{
		printf("texture 초기화 실패");
		free_texture_path(&info);
		exit(-1);
	}
	if (load_textures(&info))
	{
		printf("texture 로드 실패");
		free_texture_path(&info);
		free_texture(&info);
		//todo free
		exit(-1);
	}

	info.img.img_ptr = mlx_new_image(info.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	info.img.data = (int *)mlx_get_data_addr(info.img.img_ptr, &info.img.bpp, &info.img.size_line, &info.img.endian);

	//키 이벤트, 키 함수.
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_release, 0, &key_release, &info);

	//
	mlx_loop_hook(info.mlx_ptr, &main_loop, &info);

	// 시작.
	mlx_loop(info.mlx_ptr);
	return (0);
}

// todo 스크린 자동 조절
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