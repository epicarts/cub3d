/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_identifier_texture.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:35:48 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 23:59:35 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	identifier_texture_check(t_info *info, char **list)
{
	if (!ft_strcmp(list[0], "NO"))
		info->read_check.no++;
	else if (!ft_strcmp(list[0], "SO"))
		info->read_check.so++;
	else if (!ft_strcmp(list[0], "WE"))
		info->read_check.we++;
	else if (!ft_strcmp(list[0], "EA"))
		info->read_check.ea++;
	else if (!ft_strcmp(list[0], "S"))
		info->read_check.s++;
}

int	identifier_texture(t_info *info, char **list)
{
	if (list[1] == NULL || list[2] != NULL)
		return (0);
	if (!ft_strcmp(list[0], "NO") && info->read_check.no == 0)
		info->texture[NO].texture_path = ft_strdup(list[1]);
	else if (!ft_strcmp(list[0], "SO") && info->read_check.so == 0)
		info->texture[SO].texture_path = ft_strdup(list[1]);
	else if (!ft_strcmp(list[0], "WE") && info->read_check.we == 0)
		info->texture[WE].texture_path = ft_strdup(list[1]);
	else if (!ft_strcmp(list[0], "EA") && info->read_check.ea == 0)
		info->texture[EA].texture_path = ft_strdup(list[1]);
	else if (!ft_strcmp(list[0], "S") && info->read_check.s == 0)
		info->texture[S].texture_path = ft_strdup(list[1]);
	return (1);
}
