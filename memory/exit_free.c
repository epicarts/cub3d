/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 05:13:43 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 05:14:59 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_map(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->map_height)
	{
		free(info->world_map[i]);
		i++;
	}
	free(info->world_map);
}

void	free_sprite(t_info *info)
{
	free(info->sprite);
	free(info->sprite_distance);
	free(info->sprite_order);
}

void 	free_buf(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->win_y)
	{
		free(info->buf[i]);
		i++;
	}
	free(info->buf);
}

void	free_texture(t_info *info)
{
	int	i;

	i = 0;
	while (i < TEX_WALL_NUM)
	{
		free(info->texture[i].texture);
		i++;
	}
}

void	free_texture_path(t_info *info)
{
	int	i;

	i = 0;
	while (i < TEX_WALL_NUM)
	{
		free(info->texture[i].texture_path);
		i++;
	}
}
