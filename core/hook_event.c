
#include "../cub3d.h"

int		key_press(int keycode, t_info *info)
{
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

int		key_release(int keycode, t_info *info)
{
	if (keycode == KEY_ESC)
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


int exit_win(t_info *info)
{
	//todo 전체 free
	exit(0);
}

