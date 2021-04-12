/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 01:58:20 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 05:34:31 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	screen_check(t_info *info)
{
	int	max_x;
	int	max_y;

	if (info->screenshot_flag == 1)
		return ;
	mlx_get_screen_size(info->mlx_ptr, &max_x, &max_y);
	if (max_x < info->win_x)
		info->win_x = max_x;
	if (max_y < info->win_y)
		info->win_y = max_y;
}

void	init_malloc_flag(t_info *info)
{
	info->malloc.f_texture_path = 0;
	info->malloc.f_map = 0;
	info->malloc.f_mlx = 0;
	info->malloc.f_sprite = 0;
	info->malloc.f_buf = 0;
	info->malloc.f_z_buf = 0;
	info->malloc.f_texture = 0;
}

void	init_info(t_info *info)
{
	info->mlx_ptr = mlx_init();
	info->win = mlx_new_window(
			info->mlx_ptr, info->win_x, info->win_y, "cub3D");
	if (!(info->mlx_ptr) || !(info->win))
		exit_all(info, "mlx 초기화 실패", ERROR);
	info->malloc.f_mlx = MALLOC;
	set_xy(&info->move, 0, 0);
	info->move_speed = 0.05;
	info->rotate_speed = 0.05;
	info->key.w = 0;
	info->key.a = 0;
	info->key.s = 0;
	info->key.d = 0;
	info->key.l = 0;
	info->key.r = 0;
	if (!malloc_sprite(info))
		exit_all(info, "sprite 할당 실패", ERROR);
	if (!malloc_buf(info))
		exit_all(info, "buf 할당 실패", ERROR);
	if (!malloc_z_buf(info))
		exit_all(info, "z_buf 할당 실패", ERROR);
	if (!malloc_texture(info))
		exit_all(info, "texture 초기화 실패", ERROR);
	if (!load_textures(info))
		exit_all(info, "texture 로드 실패", ERROR);
}

void	read_map(t_info *info, char *map_path)
{
	int		fd;
	char	*line;

	check_list_init(info);
	init_dir_duplicate(info);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		exit_all(info, "파일 열기 실패", ERROR);
	if (init_identifier(info, fd))
	{
		close(fd);
		exit_all(info, "identifier 읽기 실패", ERROR);
	}
	line = move_map_line(fd);
	if (!(line) || read_map_line(info, fd, line) || check_dir_duplicate(info)
		|| info->map_height < 3 || info->map_width < 3)
	{
		close(fd);
		exit_all(info, "맵 읽기 실패", ERROR);
	}
	close(fd);
	fd = open(map_path, O_RDONLY);
	if (init_map(info, fd))
		exit_all(info, "맵 검증 실패", ERROR);
	close(fd);
}
