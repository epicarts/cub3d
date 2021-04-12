/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 04:01:42 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 04:01:44 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_ceiling(t_info *info, int x, t_wall_calc w)
{
	int	y;

	y = 0;
	while (y < w.drawStart)
	{
		info->buf[y][x] = info->ceil_color;
		y++;
	}
}

void	draw_floor(t_info *info, int x, t_wall_calc w)
{
	int	y;

	if (w.drawEnd < 0)
		w.drawEnd = info->win_y;
	y = w.drawEnd + 1;
	while (y < info->win_y)
	{
		info->buf[y][x] = info->floor_color;
		y++;
	}
}
