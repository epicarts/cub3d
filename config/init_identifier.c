
#include "../cub3d.h"

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
		identifier_texture_check(info, list);
	else if(!ft_strcmp(list[0], "R") && identifier_r(info, list)) //R
		info->read_check.r = 1;
	else if((!ft_strcmp(list[0], "F") || !ft_strcmp(list[0], "C")) && identifier_fc(info, list)) //F, C, 벽, 천장
		identifier_fc_check(info, list);
	else // 잘못된 맵파일.
		result = 0;
	free_2d_malloc(list);
	return (result);
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

int init_identifier(t_info *info, int fd)
{
	int i;
	char *line;

	while ((i = get_next_line(fd, &line)) > 0)
	{
		//라인인지 파악.
		if (*line == '\0' || is_identifier_in_line(info, line))
			;
		else
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
