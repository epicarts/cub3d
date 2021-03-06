/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 04:30:28 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 04:31:13 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int keycode, t_info *info)
{
	if (keycode == KEY_ESC)
		exit_all(info, "정상적으로 종료", SUCCESS);
	else if (keycode == KEY_W)
		info->key.w = 1;
	else if (keycode == KEY_A)
		info->key.a = 1;
	else if (keycode == KEY_S)
		info->key.s = 1;
	else if (keycode == KEY_D)
		info->key.d = 1;
	else if (keycode == KEY_LEFT)
		info->key.l = 1;
	else if (keycode == KEY_RIGHT)
		info->key.r = 1;
	return (0);
}

int	key_release(int keycode, t_info *info)
{
	if (keycode == KEY_ESC)
		exit_all(info, "정상적으로 종료", SUCCESS);
	else if (keycode == KEY_W)
		info->key.w = 0;
	else if (keycode == KEY_A)
		info->key.a = 0;
	else if (keycode == KEY_S)
		info->key.s = 0;
	else if (keycode == KEY_D)
		info->key.d = 0;
	else if (keycode == KEY_LEFT)
		info->key.l = 0;
	else if (keycode == KEY_RIGHT)
		info->key.r = 0;
	return (0);
}
