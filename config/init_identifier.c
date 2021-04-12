/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_identifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:36:23 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 03:42:08 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_identifier_in_line(t_info *info, char *line)
{
	char	**list;
	int		result;

	list = ft_split(line, ' ');
	if (!(list))
		return (0);
	result = 1;
	if ((!ft_strcmp(list[0], "NO") || !ft_strcmp(list[0], "SO")
			|| !ft_strcmp(list[0], "WE") || !ft_strcmp(list[0], "EA")
			|| !ft_strcmp(list[0], "S")) && identifier_texture(info, list))
		identifier_texture_check(info, list);
	else if (!ft_strcmp(list[0], "R") && identifier_r(info, list))
		info->read_check.r = 1;
	else if ((!ft_strcmp(list[0], "F") || !ft_strcmp(list[0], "C"))
		&& identifier_fc(info, list))
		identifier_fc_check(info, list);
	else
		result = 0;
	free_2d_malloc(list);
	return (result);
}

int	identifier_check(t_info	*info)
{
	if (!info->read_check.r)
		return (0);
	if (!info->read_check.no)
		return (0);
	if (!info->read_check.so)
		return (0);
	if (!info->read_check.we)
		return (0);
	if (!info->read_check.ea)
		return (0);
	if (!info->read_check.s)
		return (0);
	if (!info->read_check.f)
		return (0);
	if (!info->read_check.c)
		return (0);
	return (1);
}

int	init_identifier(t_info *info, int fd)
{
	int		i;
	char	*line;

	while (1)
	{
		i = get_next_line(fd, &line);
		if (i <= 0)
			break ;
		if (*line == '\0' || is_identifier_in_line(info, line))
			;
		else
		{
			free(line);
			return (-1);
		}
		if (identifier_check(info))
			break ;
		free(line);
	}
	free(line);
	if (i <= 0)
		return (-1);
	return (0);
}
