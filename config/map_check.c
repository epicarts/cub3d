/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:44:06 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 03:59:14 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	**copy_map(int **src_map, int y, int x)
{
	int	**dst_map;
	int	i;
	int	j;

	dst_map = (int **)malloc(sizeof(int *) * y);
	if (!(dst_map))
		return (NULL);
	i = 0;
	while (i < y)
	{
		j = 0;
		dst_map[i] = (int *)malloc(sizeof(int) * x);
		while (j < x)
		{
			if (src_map[i][j] == 2 || src_map[i][j] == 0)
				dst_map[i][j] = 0;
			else
				dst_map[i][j] = 1;
			j++;
		}
		i++;
	}
	return (dst_map);
}

void	free_copy_map(int **map, int y)
{
	int	i;

	i = 0;
	while (i < y)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	map_check(int **src_map, t_xy pos, int map_y, int map_x)
{
	t_map_check	map_info;

	set_int_xy(&map_info.dir[0], 1, 0);
	set_int_xy(&map_info.dir[1], 0, 1);
	set_int_xy(&map_info.dir[2], -1, 0);
	set_int_xy(&map_info.dir[3], 0, -1);
	map_info.map_size.y = map_y;
	map_info.map_size.x = map_x;
	map_info.map = copy_map(src_map, map_y, map_x);
	if (!(map_info.map))
		return (-1);
	map_info.result = 1;
	dfs(&map_info, (int)pos.x, (int)pos.y);
	free_copy_map(map_info.map, map_y);
	if (map_info.result == -1)
		return (-1);
	return (0);
}
