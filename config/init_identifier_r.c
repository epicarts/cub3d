/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_identifier_r.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:31:05 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 03:35:44 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	identifier_r(t_info *info, char **list)
{
	if (list[1] == NULL || list[2] == NULL )
		return (0);
	if (!(digit_in_str(list[1]) && digit_in_str(list[2])))
		return (0);
	info->win_x = ft_atoi(list[1]);
	info->win_y = ft_atoi(list[2]);
	if (0 < info->win_x && 0 < info->win_y)
		return (1);
	return (0);
}
