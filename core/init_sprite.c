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

int		malloc_sprite(t_info *info)
{
	info->sprite_count = count_sprite(info);
	if (!(info->sprite = (t_xy *)malloc(sizeof(t_xy) * info->sprite_count)))
		return (-1);
	if (!(info->sprite_distance =
			(double *)malloc(sizeof(double) * info->sprite_count)))
	{
		free(info->sprite);
		return (-1);
	}
	if (!(info->sprite_order = (int *)malloc(sizeof(int) * info->sprite_count)))
	{
		free(info->sprite);
		free(info->sprite_distance);
		return (-1);
	}
	add_sprite_pos(info);
	return (0);
}

void	free_sprite(t_info *info)
{
	free(info->sprite);
	free(info->sprite_distance);
	free(info->sprite_order);
}
