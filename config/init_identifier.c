
#include <stdbool.h>
#include "../cub3d.h"

int identifier_check(t_info *info);

void free_2d_malloc(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}


int identifier_texture(t_info *info, char** list)
{
	if (list[1] == NULL)
		return (0);
	if (!ft_strcmp(list[0], "NO"))
	{
		info->texture[NO].texture_path = ft_strdup(list[1]); //todo 텍스쳐 로드시 지우기. free
		info->read_check.no = 1;
	}
	else if (!ft_strcmp(list[0], "SO"))
	{
		info->texture[SO].texture_path = ft_strdup(list[1]);
		info->read_check.so = 1;
	}
	else if (!ft_strcmp(list[0], "WE"))
	{
		info->texture[WE].texture_path = ft_strdup(list[1]);
		info->read_check.we = 1;
	}
	else if (!ft_strcmp(list[0], "EA"))
	{
		info->texture[EA].texture_path = ft_strdup(list[1]);
		info->read_check.ea = 1;
	}
	else if (!ft_strcmp(list[0], "S"))
	{
		info->s_texture.texture_path = ft_strdup(list[1]);
		info->read_check.s = 1;
 	}
	return (1);
}

int digit_in_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if(!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}


int identifier_r(t_info *info, char** list)
{
	if (list[1] == NULL || list[2] == NULL )
		return (0);
	if (!(digit_in_str(list[1]) || digit_in_str(list[2])))
		return (0);
	info->win_x = ft_atoi(list[1]);
	info->win_y = ft_atoi(list[2]);
	if (0 < info->win_x && 0 < info->win_y) //음수거나 0이면 안댐.
	{
		info->read_check.r = 1;
		return (1);
	}
	return (0);
}

int rgb_to_int(int r, int g, int b)
{
	int result;

	result = 0;
	result = result | (r << 16);
	result = result | (g << 8);
	result = result | (b);

	return result;
}


int set_color(t_info *info, t_color *color, char **list, char **c_list)
{
	if (c_list[0] == NULL || c_list[1] == NULL || c_list[2] == NULL ||
		!digit_in_str(c_list[0]) || !digit_in_str(c_list[1]) || !digit_in_str(c_list[2]))
		return (0);
	color->red = ft_atoi(c_list[0]);
	color->green = ft_atoi(c_list[1]);
	color->blue = ft_atoi(c_list[2]);
	if (0 <= color->red && color->red <= 255 && 0 <= color->green && color->green <= 255 &&
		0 <= color->blue && color->blue <= 255)
	{
		if (!ft_strcmp(list[0], "F"))
		{
			info->floor_color = rgb_to_int(color->red,color->green,color->blue);
			info->read_check.f = 1;
		}
		else if (!ft_strcmp(list[0], "C"))
		{
			info->ceil_color = rgb_to_int(color->red,color->green,color->blue);
			info->read_check.c = 1;
		}
	}
	return (1);
}

int identifier_fc(t_info *info, char** list)
{
	t_color	color;
	char **c_list;

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

// key, value. => key 가 있는지 찾음.
int is_identifier_in_line(t_info *info, char *line)
{
	char **list;
	int result;
	// 라인을 읽었을떄 split이 안되면 리턴,
	if (!(list = ft_split(line, ' ')))
		return (0);
	//벽인가?
	result = 1;

	if ((!ft_strcmp(list[0], "NO") || !ft_strcmp(list[0], "SO") || !ft_strcmp(list[0], "WE") || !ft_strcmp(list[0], "EA") || !ft_strcmp(list[0], "S"))
		&& identifier_texture(info, list))
		;
	else if(!ft_strcmp(list[0], "R") && identifier_r(info, list)) //R
		;
	else if((!ft_strcmp(list[0], "F") || !ft_strcmp(list[0], "C")) && identifier_fc(info, list)) //F, C, 벽, 천장
		;
	else // 잘못된 맵파일.
		result = 0;
	// todo leak check
	free_2d_malloc(list);
	return (result);
}



//맵이 나올떄 까지 값을 읽어야함.
int init_identifier(t_info *info, int fd)
{
	int i;
	char *line;

	while ((i = get_next_line(fd, &line)) > 0)
	{
		//라인인지 파악.
		if (*line == '\0' || is_identifier_in_line(info, line))
			;
		else //올바르지 않음.
		{
			free(line);
			return (-1);
		}
		if (identifier_check(info))
			break;
		free(line);
	}
	free(line);
	if (i <= 0) // 파일이 끝나면 안댐.
		return (-1); // 오류, 프로그램 종료.
	return (0); //초기화 성공.
}

int identifier_check(t_info *info) {
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
