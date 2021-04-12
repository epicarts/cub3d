/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 04:43:08 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 04:47:23 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	int_to_char(unsigned char *str, int value)
{
	str[0] = (unsigned char)(value);
	str[1] = (unsigned char)(value >> 8);
	str[2] = (unsigned char)(value >> 16);
	str[3] = (unsigned char)(value >> 24);
}

int	write_bmp_header(int fd, int file_size, t_info *info)
{
	unsigned char	bmp_header[54];

	ft_bzero(bmp_header, 54);
	bmp_header[0] = (unsigned char)('B');
	bmp_header[1] = (unsigned char)('M');
	int_to_char(bmp_header + 2, file_size);
	bmp_header[10] = (unsigned char)(54);
	bmp_header[14] = (unsigned char)(40);
	int_to_char(bmp_header + 18, info->win_x);
	int_to_char(bmp_header + 22, info->win_y);
	bmp_header[26] = (unsigned char)(1);
	bmp_header[28] = (unsigned char)(32);
	if (write(fd, bmp_header, 54) < 0)
		return (0);
	return (1);
}

int	write_bmp_data(int fd, t_info *info)
{
	int	y;
	int	x;

	y = info->win_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < info->win_x)
		{
			if (write(fd, &(info->buf[y][x]), 4) < 0)
				return (0);
			x++;
		}
		y--;
	}
	return (1);
}

int	save_bmp(t_info *info)
{
	int	file_size;
	int	fd;

	fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (!(fd))
		return (0);
	file_size = 54 + (4 * info->win_x * info->win_y);
	if (!write_bmp_header(fd, file_size, info))
		return (0);
	if (!write_bmp_data(fd, info))
		return (0);
	close(fd);
	return (1);
}

void	screenshot(t_info *info)
{
	if (!save_bmp(info))
		exit_all(info, "스크린샷 세이브 실패", ERROR);
	exit_all(info, "스크린샷 세이브 성공", ERROR);
}
