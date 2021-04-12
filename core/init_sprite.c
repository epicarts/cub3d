#include "../cub3d.h"

int		count_sprite(t_info *info)
{
	int i;
	int j;
	int count;

	count = 0;
	i = -1;
	while (++i < info->map_height)
	{
		j = -1;
		while (++j < info->map_width)
		{
			if (info->world_map[i][j] == 2)
				count++;
		}
	}
	return (count);
}

void	add_sprite_pos(t_info *info)
{
	int i;
	int j;
	int count;

	count = 0;
	i = -1;
	while (++i < info->map_height)
	{
		j = -1;
		while (++j < info->map_width)
		{
			if (info->world_map[i][j] == 2)
			{
				info->sprite[count].x = i;
				info->sprite[count].y = j;
				count++;
			}
		}
	}
}


