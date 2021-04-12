/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 04:33:54 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 04:42:18 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_front_back(t_info *info)
{
	if (info->key.w)
	{
		if (!(info->world_map[(int)(info->pos.x + info->dir.x
					* info->move_speed)][(int)(info->pos.y)] == 1))
			info->pos.x += info->dir.x * info->move_speed;
		if (!(info->world_map[(int)(info->pos.x)]
			[(int)(info->pos.y + info->dir.y * info->move_speed)] == 1))
			info->pos.y += info->dir.y * info->move_speed;
	}
	else if (info->key.s)
	{
		if (!(info->world_map[(int)(info->pos.x
					- info->dir.x *info->move_speed)][(int)(info->pos.y)] == 1))
			info->pos.x -= info->dir.x * info->move_speed;
		if (!(info->world_map[(int)(info->pos.x)]
			[(int)(info->pos.y - info->dir.y * info->move_speed)] == 1))
			info->pos.y -= info->dir.y * info->move_speed;
	}
}

void	move_left_right(t_info *info)
{
	if (info->key.d)
	{
		if (!(info->world_map[(int)(info->pos.x)]
			[(int)(info->pos.y - info->dir.x * info->move_speed)] == 1))
			info->pos.y -= info->dir.x * info->move_speed;
		if (!(info->world_map[(int)(info->pos.x + info->dir.y
					* info->move_speed)][(int)(info->pos.y)] == 1))
			info->pos.x += info->dir.y * info->move_speed;
	}
	else if (info->key.a)
	{
		if (!(info->world_map[(int)(info->pos.x)]
			[(int)(info->pos.y + info->dir.x * info->move_speed)] == 1))
			info->pos.y += info->dir.x * info->move_speed;
		if (!(info->world_map[(int)(info->pos.x - info->dir.y
					* info->move_speed)][(int)(info->pos.y)] == 1))
			info->pos.x -= info->dir.y * info->move_speed;
	}
}

void	rotate(t_info *info)
{
	int		flag;
	double	old;

	if (info->key.l == 1)
		flag = 1;
	else
		flag = -1;
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
}
