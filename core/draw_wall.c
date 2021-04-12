/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 04:01:52 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 04:30:20 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_wall(t_info *info, t_wall_calc *w, t_ray *ray)
{
	w->lineHeight = (int)(info->win_y / ray->perp_wall_dist);
	w->drawStart = -w->lineHeight / 2 + info->win_y / 2;
	if (w->drawStart < 0)
		w->drawStart = 0;
	w->drawEnd = w->lineHeight / 2 + info->win_y / 2;
	if (w->drawEnd >= info->win_y)
		w->drawEnd = info->win_y - 1;
	if (ray->side == 0)
		w->wallX = info->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		w->wallX = info->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	w->wallX -= floor(w->wallX);
	w->texX = (int)(w->wallX * (double)TEX_WIDTH);
	if (ray->side == 0 && ray->ray_dir.x > 0)
		w->texX = TEX_WIDTH - w->texX - 1;
	if (ray->side == 1 && ray->ray_dir.y < 0)
		w->texX = TEX_WIDTH - w->texX - 1;
	w->step_ = 1.0 * TEX_HEIGHT / w->lineHeight;
	w->texPos = (w->drawStart - info->win_y / 2 + w->lineHeight / 2) * w->step_;
}

void	calc_wall_texture(t_info *info, t_wall_calc *w, t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->ray_dir.y < 0)
			w->color = info->texture[WE]
				.texture[TEX_HEIGHT * w->texY + w->texX];
		else
			w->color = info->texture[EA]
				.texture[TEX_HEIGHT * w->texY + w->texX];
	}
	else
	{
		if (ray->ray_dir.x < 0)
			w->color = info->texture[NO]
				.texture[TEX_HEIGHT * w->texY + w->texX];
		else
			w->color = info->texture[SO]
				.texture[TEX_HEIGHT * w->texY + w->texX];
	}
}

void	draw_wall(t_info *info, t_ray *ray, int x)
{
	t_wall_calc	w;
	int			y;

	init_wall(info, &w, ray);
	y = w.drawStart;
	while (y <= w.drawEnd)
	{
		w.texY = (int)w.texPos & (TEX_HEIGHT - 1);
		w.texPos += w.step_;
		calc_wall_texture(info, &w, ray);
		info->buf[y][x] = w.color;
		y++;
	}
	draw_ceiling(info, x, w);
	draw_floor(info, x, w);
	info->z_buf[x] = ray->perp_wall_dist;
}
