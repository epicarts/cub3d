/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:42:11 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 03:44:03 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_dir(t_info *info, char c)
{
	if (c == 'N')
	{
		set_xy(&info->dir, -1.0, 0.0);
		set_xy(&info->plane, 0.0, 0.66);
	}
	if (c == 'S')
	{
		set_xy(&info->dir, 1.0, 0.0);
		set_xy(&info->plane, 0.0, -0.66);
	}
	if (c == 'E')
	{
		set_xy(&info->dir, 0.0, 1.0);
		set_xy(&info->plane, 0.66, 0.0);
	}
	if (c == 'W')
	{
		set_xy(&info->dir, 0.0, -1.0);
		set_xy(&info->plane, -0.66, 0.0);
	}
}

void	add_array_map(t_info *info, const char *line, int height)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == ' ')
			info->world_map[height][i] = 0;
		else if (line[i] == '1')
			info->world_map[height][i] = 1;
		else if (line[i] == '2')
			info->world_map[height][i] = 2;
		else if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			init_dir(info, line[i]);
			set_xy(&info->pos, height + 0.5, i + 0.5);
			info->world_map[height][i] = 0;
		}
		i++;
	}
}

int	init_map(t_info *info, int fd)
{
	int		i;
	int		height;
	char	*line;

	info->world_map = malloc_map(info);
	if (!(info->world_map))
		return (-1);
	height = 0;
	while (1)
	{
		i = get_next_line(fd, &line);
		if (*line != '\0' && is_map_in_line(line))
		{
			add_array_map(info, line, height);
			height++;
		}
		free(line);
		if (i <= 0)
			break ;
	}
	if (map_check(info->world_map, info->pos,
			info->map_height, info->map_width))
		return (-1);
	return (0);
}
