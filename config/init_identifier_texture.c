
#include "../cub3d.h"

void identifier_texture_check(t_info *info, char** list)
{
	if (!ft_strcmp(list[0], "NO"))
		info->read_check.no = 1;
	else if (!ft_strcmp(list[0], "SO"))
		info->read_check.so = 1;
	else if (!ft_strcmp(list[0], "WE"))
		info->read_check.we = 1;
	else if (!ft_strcmp(list[0], "EA"))
		info->read_check.ea = 1;
	else if (!ft_strcmp(list[0], "S"))
		info->read_check.s = 1;
}

int identifier_texture(t_info *info, char** list)
{
	if (list[1] == NULL)
		return (0);
	if (!ft_strcmp(list[0], "NO"))
		info->texture[NO].texture_path = ft_strdup(list[1]); //todo 텍스쳐 로드시 지우기. free
	else if (!ft_strcmp(list[0], "SO"))
		info->texture[SO].texture_path = ft_strdup(list[1]);
	else if (!ft_strcmp(list[0], "WE"))
		info->texture[WE].texture_path = ft_strdup(list[1]);
	else if (!ft_strcmp(list[0], "EA"))
		info->texture[EA].texture_path = ft_strdup(list[1]);
	else if (!ft_strcmp(list[0], "S"))
		info->texture[S].texture_path = ft_strdup(list[1]);
	return (1);
}