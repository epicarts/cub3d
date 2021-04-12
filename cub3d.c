//
// Created by YoungHo on 2021/03/20.
//

#include <math.h>
#include "cub3d.h"

//메모리 할당
void init_malloc_flag(t_info *info)
{
	info->malloc.f_texture_path = 0;
	info->malloc.f_map = 0;
	info->malloc.f_mlx = 0;
	info->malloc.f_sprite = 0;
	info->malloc.f_buf = 0;
	info->malloc.f_z_buf = 0;
	info->malloc.f_texture = 0;
}

int	exit_all(t_info *info, char *msg, int status)
{
	if (info->malloc.f_texture_path == MALLOC)
		free_texture_path(info);
	if (info->malloc.f_map == MALLOC)
		free_map(info);
	if (info->malloc.f_mlx == MALLOC)
		mlx_destroy_window(info->mlx_ptr, info->win);
	if (info->malloc.f_sprite == MALLOC)
		free_sprite(info);
	if (info->malloc.f_buf == MALLOC)
		free_buf(info);
	if (info->malloc.f_z_buf == MALLOC)
		free_z_buf(info);
	if (info->malloc.f_texture == MALLOC)
		free_texture(info);
	if (status == ERROR) // 에러면
	{
		printf("%s\n", msg);
		system("leaks cub3D > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
		exit(EXIT_FAILURE); //실패 반환
	}
	printf("%s\n", msg);
	system("leaks cub3D > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	exit(EXIT_SUCCESS);//정상 종료
}

void	init_info(t_info *info)
{
	//mlx초기화, 윈도우초기화
	if (!(info->mlx_ptr = mlx_init()) || !(info->win = mlx_new_window(
			info->mlx_ptr, info->win_x, info->win_y, "cub3D")))
		exit_all(info, "mlx 초기화 실패", ERROR);
	info->malloc.f_mlx = MALLOC;
	set_xy(&info->move, 0, 0);
	info->move_speed = 0.05; 	//회전 및 움직임 정도.
	info->rotate_speed = 0.05;
	info->key.w = 0; // 키보드 초기화.
	info->key.a = 0;
	info->key.s = 0;
	info->key.d = 0;
	info->key.l = 0;
	info->key.r = 0;
	if (!malloc_sprite(info))
		exit_all(info, "sprite 할당 실패", ERROR);
	if (!malloc_buf(info))
		exit_all(info, "buf 할당 실패", ERROR);
	if (!malloc_z_buf(info)) //todo free
		exit_all(info, "z_buf 할당 실패", ERROR);
	if (!malloc_texture(info))
		exit_all(info, "texture 초기화 실패", ERROR);
	if (!load_textures(info))
		exit_all(info, "texture 로드 실패", ERROR);
}


void	put_draw(t_info *info)
{
	int y;
	int x;

	y = 0;
	while (y < info->win_y)
	{
		x = 0;
		while (x < info->win_x)
		{
			info->img.data[y * info->win_x + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win, info->img.img_ptr, 0, 0);
}

int main_loop(t_info *info)
{
	t_ray	ray;
	int x;

	if (info->key.w || info->key.s)
		move_front_back(info);
	else if (info->key.a || info->key.d)
		move_left_right(info);
	if (info->key.r || info->key.l)
		rotate(info);
	x = -1; // 0 ~ 최대폭 까지
	while (++x < info->win_x)
	{
		calc_ray(info, &ray, x); // init ray
		draw_wall(info, &ray, x); // 벽 그리기.
	}
	draw_sprites(info);
	if (info->screenshot_flag == 1)
		screenshot(info);
	put_draw(info);
	return (0);
}

void  ft_screen_check(t_info *info)
{
	int max_x;
	int max_y;

	printf("winx x: %d  winy y %d\n", info->win_x, info->win_y);
	if (info->screenshot_flag == 1)
		return;
	mlx_get_screen_size(info->mlx_ptr, &max_x, &max_y);
	if (max_x < info->win_x)
		info->win_x = max_x;
	if (max_y < info->win_y)
		info->win_y = max_y;
	printf("max x: %d  max y %d\n", max_x, max_y);
	printf("winx x: %d  winy y %d\n", info->win_x, info->win_y);
}


int			main(int argc, char *argv[])
{
	t_info	info;

	init_malloc_flag(&info);
	arg_parse(&info, argc, argv);
	read_map(&info, info.map_path);
	ft_screen_check(&info); // 화면 사이즈 나오기전에 할당.
	init_info(&info);

	info.img.img_ptr = mlx_new_image(info.mlx_ptr, info.win_x, info.win_y);
	info.img.data = (int *)mlx_get_data_addr(info.img.img_ptr, &info.img.bpp, &info.img.size_line, &info.img.endian);

	if (info.screenshot_flag == 1)
		main_loop(&info);

	//키 이벤트, 키 함수.
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);
	mlx_hook(info.win, X_EVENT_EXIT, 0, &exit_all, &info);

	mlx_loop_hook(info.mlx_ptr, &main_loop, &info);

	// 시작.
	mlx_loop(info.mlx_ptr);
	return (0);
}
