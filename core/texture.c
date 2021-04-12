
#include "../cub3d.h"

int	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int y;
	int x;

	if (!(img->img_ptr = mlx_xpm_file_to_image(info->mlx_ptr, path, &img->width, &img->height)))
		return (-1);
	if (!(img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian)))
		return (-1);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			texture[img->width * y + x] = img->data[img->width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx_ptr, img->img_ptr); // 배열에 저장했으므로 포인터 제거.
	return (0);
}

int		load_textures(t_info *info)
{
	t_img	img;

	if(load_image(info, info->texture[EA].texture, info->texture[EA].texture_path, &img))
		return (0);
	if(load_image(info, info->texture[SO].texture, info->texture[SO].texture_path, &img))
		return (0);
	if(load_image(info, info->texture[WE].texture, info->texture[WE].texture_path, &img))
		return (0);
	if(load_image(info, info->texture[NO].texture, info->texture[NO].texture_path, &img))
		return (0);
	if(load_image(info, info->texture[S].texture, info->texture[S].texture_path, &img))
		return (0);
	return (1);
}
