/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:16:38 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 04:42:24 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calc_ray_step(t_info *info, t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (info->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - info->pos.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (info->pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - info->pos.y) * ray->delta_dist.y;
	}
}

void	DDA_algorithm(t_info *info, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += (int)ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += (int)ray->step.y;
			ray->side = 1;
		}
		if (info->world_map[(int)ray->map.x][(int)ray->map.y] == 1)
			hit = 1;
	}
}

void	calc_ray(t_info *info, t_ray *r, int x)
{
	double	K;

	K = 2 * x / (double)info->win_x - 1;
	set_xy(&r->ray_dir, info->dir.x + info->plane.x
		* K, info->dir.y + info->plane.y * K);
	set_xy(&r->map, (int)info->pos.x, (int)info->pos.y);
	set_xy(&r->delta_dist, fabs(1. / r->ray_dir.x), fabs(1. / r->ray_dir.y));
	calc_ray_step(info, r);
	DDA_algorithm(info, r);
	if (r->side == 0)
		r->perp_wall_dist = (r->map.x - info->pos.x + (1 - r->step.x) / 2)
			/ r->ray_dir.x;
	else
		r->perp_wall_dist = (r->map.y - info->pos.y + (1 - r->step.y) / 2)
			 / r->ray_dir.y;
}
