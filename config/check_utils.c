/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 01:52:43 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 03:00:23 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	count_map_width_height(t_info *info, char *line)
{
	if (info->map_width < (int)ft_strlen(line))
		info->map_width = ft_strlen(line);
	info->map_height++;
}

void	init_dir_duplicate(t_info *info)
{
	info->dir_check.n = 0;
	info->dir_check.s = 0;
	info->dir_check.e = 0;
	info->dir_check.w = 0;
}

int	check_dir_duplicate(t_info *info)
{
	int		count;

	count = (info->dir_check.n + info->dir_check.s)
		+ (info->dir_check.e + info->dir_check.w);
	if (count == 1)
		return (0);
	else
		return (1);
}

void	count_dir_duplicate(t_info *info, const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N')
			info->dir_check.n++;
		else if (line[i] == 'S')
			info->dir_check.s++;
		else if (line[i] == 'E')
			info->dir_check.e++;
		else if (line[i] == 'W')
			info->dir_check.w++;
		i++;
	}
}

void	check_list_init(t_info *info)
{
	info->read_check.r = 0;
	info->read_check.no = 0;
	info->read_check.so = 0;
	info->read_check.we = 0;
	info->read_check.ea = 0;
	info->read_check.s = 0;
	info->read_check.f = 0;
	info->read_check.c = 0;
	info->map_width = 0;
	info->map_height = 0;
}
