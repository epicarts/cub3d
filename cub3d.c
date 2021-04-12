/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 05:24:15 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 05:34:17 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_all(t_info *info, char *msg, int status)
{
	if (info->malloc.f_texture_path == MALLOC)
		free_texture_path(info);
	if (info->malloc.f_map == MALLOC)
		free_map(info);
	if (info->malloc.f_mlx == MALLOC)
		mlx_destroy_window(info->mlx_ptr, info->win);
	if (info->malloc.f_sprite == MALLOC)
		free_sprite(info);
	if (info->malloc.f_buf == MALLOC)
		free_buf(info);
	if (info->malloc.f_z_buf == MALLOC)
		free(info->z_buf);
	if (info->malloc.f_texture == MALLOC)
		free_texture(info);
	if (status == ERROR)
	{
		printf("%s\n", msg);
		exit(EXIT_FAILURE);
	}
	printf("%s\n", msg);
	exit(EXIT_SUCCESS);
}

void	put_draw(t_info *info)
{
	int	y;
	int	x;

	y = 0;
	while (y < info->win_y)
	{
		x = 0;
		while (x < info->win_x)
		{
			info->img.data[y * info->win_x + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx_ptr, info->win, info->img.img_ptr, 0, 0);
}

int	main_loop(t_info *info)
{
	t_ray	ray;
	int		x;

	if (info->key.w || info->key.s)
		move_front_back(info);
	else if (info->key.a || info->key.d)
		move_left_right(info);
	if (info->key.r || info->key.l)
		rotate(info);
	x = -1;
	while (++x < info->win_x)
	{
		calc_ray(info, &ray, x);
		draw_wall(info, &ray, x);
	}
	draw_sprites(info);
	if (info->screenshot_flag == 1)
		screenshot(info);
	put_draw(info);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info	info;

	init_malloc_flag(&info);
	arg_parse(&info, argc, argv);
	read_map(&info, info.map_path);
	screen_check(&info);
	init_info(&info);
	info.img.img_ptr = mlx_new_image(info.mlx_ptr, info.win_x, info.win_y);
	info.img.data = (int *)mlx_get_data_addr(info.img.img_ptr,
			&info.img.bpp, &info.img.size_line, &info.img.endian);
	if (info.screenshot_flag == 1)
		main_loop(&info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);
	mlx_hook(info.win, X_EVENT_EXIT, 0, &exit_all, &info);
	mlx_loop_hook(info.mlx_ptr, &main_loop, &info);
	mlx_loop(info.mlx_ptr);
	return (0);
}
