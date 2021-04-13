/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 01:52:27 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/14 05:41:03 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_cub(char *str)
{
	char	**list;
	int		i;
	char	*tmp;

	list = ft_split(str, '.');
	i = 0;
	while (list[i] != NULL)
	{
		tmp = list[i];
		i++;
	}
	if (ft_strcmp(tmp, "cub") || i < 2)
	{
		free_2d_malloc(list);
		return (0);
	}
	free_2d_malloc(list);
	return (1);
}

void	arg_parse(t_info *info, int argc, char *argv[])
{
	if (argc >= 3 && ft_strcmp(argv[2], "--save"))
		exit_all(info, "올바른 인자가 아님", ERROR);
	else if (argc == 2)
		info->screenshot_flag = 0;
	else
		info->screenshot_flag = 1;
	if (argc == 1)
		exit_all(info, "인자가 아무것도 없음. 맵을 넣어주세요.", ERROR);
	if (!check_cub(argv[1]))
		exit_all(info, "올바른 맵 파일이 아님.", ERROR);
	info->map_path = argv[1];
}
