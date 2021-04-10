

#include "../cub3d.h"

void move_front_back(t_info *info)
{
	if (info->key.w)
	{
		if (!(info->world_map[(int)(info->pos.x + info->dir.x *
				info->move_speed)][(int)(info->pos.y)] == 1))
			info->pos.x += info->dir.x * info->move_speed;
		if (!(info->world_map[(int)(info->pos.x)]
				[(int)(info->pos.y + info->dir.y * info->move_speed)] == 1))
			info->pos.y += info->dir.y * info->move_speed;
	}
	else if (info->key.s)
	{
		if (!(info->world_map[(int)(info->pos.x - info->dir.x *
				info->move_speed)][(int)(info->pos.y)] == 1))
			info->pos.x -= info->dir.x * info->move_speed;
		if (!(info->world_map[(int)(info->pos.x)]
				[(int)(info->pos.y - info->dir.y * info->move_speed)] == 1))
			info->pos.y -= info->dir.y * info->move_speed;
	}
}


void move_left_right(t_info *info)
{
	if (info->key.d)
	{
		if (!(info->world_map[(int)(info->pos.x)]
				[(int)(info->pos.y - info->dir.x * info->move_speed)] == 1))
			info->pos.y -= info->dir.x * info->move_speed;
		if (!(info->world_map[(int)(info->pos.x + info->dir.y *
				info->move_speed)][(int)(info->pos.y)] == 1))
			info->pos.x += info->dir.y * info->move_speed;
	}
	else if (info->key.a)
	{
		if (!(info->world_map[(int)(info->pos.x)]
				[(int)(info->pos.y + info->dir.x * info->move_speed)] == 1))
			info->pos.y += info->dir.x * info->move_speed;
		if (!(info->world_map[(int)(info->pos.x - info->dir.y *
				info->move_speed)][(int)(info->pos.y)] == 1))
			info->pos.x -= info->dir.y * info->move_speed;
	}
}