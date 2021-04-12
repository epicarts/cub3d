/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 01:52:27 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 03:00:19 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	info->map_path = argv[1];
}
