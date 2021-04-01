
#include "../cub3d.h"

char *move_map_line(t_info *info, int fd)
{
	char *line;
	int i;

	//맵 라인이 나올떄까지 읽음.
	while ((i = get_next_line(fd, &line)) > 0) {
		if (*line != '\0' && is_map_in_line(line))
			break;
		else if (*line == '\0')
			;
		else // 그 밖이 나올경우
		{
			free(line);
			return (NULL);
		}
		free(line);
	}
	if (i <= 0) //마지막 줄이 끝난거면 종료.
	{
		free(line);
		return (NULL);
	}
	return line;
}

int read_map_end_line(t_info *info, int fd, char *line, int i)
{
	while (1) //다른게 나왔을경우 파일 끝까지 엔터밖에 없는가?
	{
		if (*line == '\0') {
			free(line);
		}
		else //다른게 나오면 -1 리턴
		{
			free(line);
			return (-1);
		}
		if (i <= 0)
			return (0);
		i = get_next_line(fd, &line);
	}
}

int read_map_line(t_info *info, int fd, char *line)
{
	int i;

	//맵 시작부터 맵이 끝날때 까지 읽음.
	count_map_width_height(info, line); //첫번쨰 맵 라인을 읽음.
	count_dir_duplicate(info, line);
	free(line);
	while (1)
	{
		i = get_next_line(fd, &line);
		if (*line != '\0' && is_map_in_line(line))
		{
			count_dir_duplicate(info, line);
			count_map_width_height(info, line);
		}
		else
		{
			if (read_map_end_line(info, fd, line, i) == 0)
				return (0);
			else
				return (-1);
		}
		free(line);
		if (i <= 0)
			break;
	}
	return (0);
}