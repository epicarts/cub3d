/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_map_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 02:02:42 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 03:08:57 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*move_map_line(int fd)
{
	char	*line;
	int		i;

	while (1)
	{
		i = get_next_line(fd, &line);
		if (i <= 0)
			break ;
		if (*line != '\0' && is_map_in_line(line))
			break ;
		else if (*line == '\0')
			;
		else
		{
			free(line);
			return (NULL);
		}
		free(line);
	}
	if (i <= 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	read_map_end_line(int fd, char *line, int i)
{
	while (1)
	{
		if (*line == '\0')
			free(line);
		else
		{
			free(line);
			return (-1);
		}
		if (i <= 0)
			return (0);
		i = get_next_line(fd, &line);
	}
}

int	read_map_line(t_info *info, int fd, char *line)
{
	int	i;

	count_map_width_height(info, line);
	count_dir_duplicate(info, line);
	free(line);
	while (1)
	{
		i = get_next_line(fd, &line);
		if (*line != '\0' && is_map_in_line(line))
		{
			count_dir_duplicate(info, line);
			count_map_width_height(info, line);
		}
		else
		{
			if (read_map_end_line(fd, line, i) == 0)
				return (0);
			else
				return (-1);
		}
		free(line);
		if (i <= 0)
			break ;
	}
	return (0);
}
