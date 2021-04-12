/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_dfs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:59:46 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 03:59:48 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_in_map(t_map_check *m, int y, int x)
{
	if (y > m->map_size.y - 1 || x > m->map_size.x - 1)
		return (0);
	return (1);
}

int	is_visited(t_map_check *m, int y, int x)
{
	if (m->map[y][x] == 0)
		return (0);
	return (1);
}

int	dfs(t_map_check *m, int y, int x)
{
	int	i;

	if (m->result == -1)
		return (-1);
	m->map[y][x] = VISITED;
	i = -1;
	while (++i < 4)
	{
		if (is_in_map(m, y + m->dir[i].y, x + m->dir[i].x))
		{
			if (!is_visited(m, y + m->dir[i].y, x + m->dir[i].x))
				dfs(m, y + m->dir[i].y, x + m->dir[i].x);
		}
		else
			m->result = -1;
	}
	return (1);
}
