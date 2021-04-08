#include "../cub3d.h"

void draw_ceiling(t_info *info, int x, t_wall_calc w)
{
	int y;

	y = 0;
	while (y < w.drawStart) {
		//천장
		info->buf[y][x] = info->ceil_color;
		y++;
	}
}

void draw_floor(t_info *info, int x, t_wall_calc w)
{
	int y;

	if (w.drawEnd < 0) //오버플로우 시 그리지 않도록..
		w.drawEnd = WIN_HEIGHT;
	y = w.drawEnd + 1;
	while (y < WIN_HEIGHT)
	{
		//바닥
		info->buf[y][x] = info->floor_color;
		y++;
	}
}
