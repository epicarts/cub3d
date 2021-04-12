/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_identifier_fc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 03:09:39 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 03:15:04 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	rgb_to_int(int r, int g, int b)
{
	int	result;

	result = 0;
	result = result | (r << 16);
	result = result | (g << 8);
	result = result | (b);
	return (result);
}

int	set_color(t_info *info, t_color *c, char **list, char **c_list)
{
	if (c_list[0] == NULL || c_list[1] == NULL || c_list[2] == NULL
		|| !digit_in_str(c_list[0]) || !digit_in_str(c_list[1])
		|| !digit_in_str(c_list[2]))
		return (0);
	c->red = ft_atoi(c_list[0]);
	c->green = ft_atoi(c_list[1]);
	c->blue = ft_atoi(c_list[2]);
	if (0 <= c->red && c->red <= 255 && 0 <= c->green
		&& c->green <= 255 && 0 <= c->blue && c->blue <= 255)
	{
		if (!ft_strcmp(list[0], "F"))
		{
			info->floor_color = rgb_to_int(c->red, c->green, c->blue);
			info->read_check.f = 1;
		}
		else if (!ft_strcmp(list[0], "C"))
		{
			info->ceil_color = rgb_to_int(c->red, c->green, c->blue);
			info->read_check.c = 1;
		}
	}
	return (1);
}

void	identifier_fc_check(t_info *info, char **list)
{
	if (!ft_strcmp(list[0], "F"))
		info->read_check.f = 1;
	else if (!ft_strcmp(list[0], "c"))
		info->read_check.c = 1;
}

int	identifier_fc(t_info *info, char **list)
{
	t_color	color;
	char	**c_list;

	if (list[1] == NULL)
		return (0);
	c_list = ft_split(list[1], ',');
	if (set_color(info, &color, list, c_list))
	{
		free_2d_malloc(c_list);
		return (1);
	}
	free_2d_malloc(c_list);
	return (0);
}
