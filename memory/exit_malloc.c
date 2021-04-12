/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 05:15:05 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 05:21:44 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	**malloc_map(t_info *info)
{
	int	**map;
	int	i;
	int	j;

	map = (int **)malloc(sizeof(int *) * info->map_height);
	if (!(map))
		return (NULL);
	i = 0;
	while (i < info->map_height)
	{
		j = 0;
		map[i] = (int *)malloc(sizeof(int) * info->map_width);
		if (!(map[i]))
			return (NULL);
		while (j < info->map_width)
		{
			map[i][j] = 0;
			j++;
		}
		i++;
	}
	info->malloc.f_map = MALLOC;
	return (map);
}

int	malloc_sprite(t_info *info)
{
	info->sprite_count = count_sprite(info);
	info->sprite = (t_xy *)malloc(sizeof(t_xy) * info->sprite_count);
	if (!(info->sprite))
		return (0);
	info->sprite_distance = (double *)malloc(sizeof(double)
			* info->sprite_count);
	if (!(info->sprite_distance))
	{
		free(info->sprite);
		return (0);
	}
	info->sprite_order = (int *)malloc(sizeof(int) * info->sprite_count);
	if (!(info->sprite_order))
	{
		free(info->sprite);
		free(info->sprite_distance);
		return (0);
	}
	add_sprite_pos(info);
	info->malloc.f_sprite = MALLOC;
	return (1);
}

int	malloc_buf(t_info *info)
{
	int	i;
	int	j;

	info->buf = (int **)malloc(sizeof(int *) * info->win_y);
	if (!(info->buf))
		return (0);
	i = 0;
	while (i < info->win_y)
	{
		j = 0;
		info->buf[i] = (int *)malloc(sizeof(int) * info->win_x);
		if (!(info->buf[i]))
			return (0);
		while (j < info->win_x)
		{
			info->buf[i][j] = 0;
			j++;
		}
		i++;
	}
	info->malloc.f_buf = MALLOC;
	return (1);
}

int	malloc_z_buf(t_info *info)
{
	info->z_buf = (double *)malloc(sizeof(double) * info->win_x);
	if (!(info->z_buf))
		return (0);
	info->malloc.f_z_buf = MALLOC;
	return (1);
}

int	malloc_texture(t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (++i < TEX_WALL_NUM)
	{
		j = -1;
		info->texture[i].texture = (int *)malloc(sizeof(int)
				* (TEX_WIDTH * TEX_HEIGHT));
		if (!(info->texture[i].texture))
			return (0);
		while (++j < (TEX_HEIGHT * TEX_WIDTH))
			info->texture[i].texture[j] = 0;
	}
	info->malloc.f_texture = MALLOC;
	return (1);
}
