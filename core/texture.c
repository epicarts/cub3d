
#include "../cub3d.h"

int init_texture(t_info *info)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		if (!(info->texture[i].texture = (int *)malloc(sizeof(int) * (TEX_WIDTH * TEX_HEIGHT)))) //todo free 동적 할당.
			return (-1);
		while (++j < (TEX_HEIGHT * TEX_WIDTH)) //0으로 패딩.
			info->texture[i].texture[j] = 0;
	}
	return (0);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int y;
	int x;

	img->img_ptr = mlx_xpm_file_to_image(info->mlx_ptr, path, &img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
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
}

void	load_textures(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[EA].texture, info->texture[EA].texture_path, &img); //동
	load_image(info, info->texture[SO].texture, info->texture[SO].texture_path, &img); //서
	load_image(info, info->texture[WE].texture, info->texture[WE].texture_path, &img); //남
	load_image(info, info->texture[NO].texture, info->texture[NO].texture_path, &img); //북
}