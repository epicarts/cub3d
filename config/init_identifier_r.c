//
// Created by YoungHo on 2021/04/01.
//
#include "../cub3d.h"

int identifier_r(t_info *info, char** list)
{
	if (list[1] == NULL || list[2] == NULL )
		return (0);
	if (!(digit_in_str(list[1]) || digit_in_str(list[2])))
		return (0);
	info->win_x = ft_atoi(list[1]);
	info->win_y = ft_atoi(list[2]);
	if (0 < info->win_x && 0 < info->win_y) //음수거나 0이면 안댐.
		return (1);
	return (0);
}