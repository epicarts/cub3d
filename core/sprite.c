/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 04:53:59 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 05:37:48 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_sprite(t_info *info, t_sprite_calc *sc, t_xy *sprite)
{
	sprite->x = (sprite->x + 0.5) - info->pos.x;
	sprite->y = (sprite->y + 0.5) - info->pos.y;
	sc->invDet = 1.0 / (info->plane.x * info->dir.y - info->dir.x
			* info->plane.y);
	set_xy(&sc->transform,
		sc->invDet * (info->dir.y * sprite->x - info->dir.x * sprite->y),
		sc->invDet * (-info->plane.y * sprite->x + info->plane.x * sprite->y));
	sc->screen_x = (int)((info->win_x / 2)
			* (1 + sc->transform.x / sc->transform.y));
	sc->spriteHeight = (int)fabs((info->win_y / sc->transform.y) / VDIV);
	sc->vMoveScreen = (int)(VMOVE / sc->transform.y);
	sc->drawStartY = -sc->spriteHeight / 2 + info->win_y / 2 + sc->vMoveScreen;
	if (sc->drawStartY < 0)
		sc->drawStartY = 0;
	sc->drawEndY = sc->spriteHeight / 2 + info->win_y / 2 + sc->vMoveScreen;
	if (sc->drawEndY >= info->win_y)
		sc->drawEndY = info->win_y - 1;
	sc->spriteWidth = (int)fabs((info->win_y / sc->transform.y) / UDIV);
	sc->drawStartX = -sc->spriteWidth / 2 + sc->screen_x;
	if (sc->drawStartX < 0)
		sc->drawStartX = 0;
	sc->drawEndX = sc->spriteWidth / 2 + sc->screen_x;
	if (sc->drawEndX >= info->win_x)
		sc->drawEndX = info->win_x - 1;
}

void	draw_sprite_color(t_info *info, t_sprite_calc *sc, int y, int x)
{
	int				tex_idx;

	sc->texY = ((((y - sc->vMoveScreen) * 256 - info->win_y * 128
					+ sc->spriteHeight * 128) * TEX_HEIGHT)
			/ sc->spriteHeight) / 256;
	tex_idx = TEX_WIDTH * sc->texY + sc->texX;
	if (0 <= tex_idx && tex_idx < TEX_WIDTH * TEX_HEIGHT - 1)
	{
		sc->color = info->texture[S]
			.texture[TEX_WIDTH * sc->texY + sc->texX];
		if ((sc->color & 0x00FFFFFF) != 0)
			info->buf[y][x] = sc->color;
	}
}

void	draw_sprite(t_info *info, t_xy sprite)
{
	t_sprite_calc	sc;
	int				y;
	int				x;

	init_sprite(info, &sc, &sprite);
	x = sc.drawStartX - 1;
	while (++x <= sc.drawEndX)
	{
		sc.texX = (int)((256 * (x - (-sc.spriteWidth / 2 + sc.screen_x))
					* TEX_WIDTH / sc.spriteWidth) / 256);
		if (sc.transform.y > 0 && x >= 0 && x < info->win_x
			&& sc.transform.y < info->z_buf[x])
			y = sc.drawStartY - 1;
		while (++y <= sc.drawEndY)
		{
			draw_sprite_color(info, &sc, y, x);
		}
	}
}

void	draw_sprites(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->sprite_count)
	{
		info->sprite_order[i] = i;
		info->sprite_distance[i] = ((info->pos.x - info->sprite[i].x)
				* (info->pos.x - info->sprite[i].x)
				+ (info->pos.y - info->sprite[i].y)
				* (info->pos.y - info->sprite[i].y));
	}
	sort_sprites(info->sprite_order, info->sprite_distance, info->sprite_count);
	i = -1;
	while (++i < info->sprite_count)
		draw_sprite(info, info->sprite[info->sprite_order[i]]);
}
