
#include "../cub3d.h"
// map only  0, 1, 2, N,S,E,W

int ** malloc_map(t_info *info)
{
	int **map;
	int i;
	int j;

	if (!(map = (int**)malloc(sizeof(int*) * info->map_height)))
		return (NULL);
	i = 0;
	while (i < info->map_height)
	{
		j = 0;
		map[i] = (int*)malloc(sizeof(int) * info->map_width);
		while (j < info->map_width)
		{
			map[i][j] = 0;
			j++;
		}
		i++;
	}
	return map;
}

void init_dir(t_info *info, char c)
{
	if (c == 'N')
	{
		set_xy(&info->dir, -1.0, 0.0);
		set_xy(&info->plane, 0.0, 0.66);
	}
	if (c == 'S')
	{
		set_xy(&info->dir, 1.0, 0.0);
		set_xy(&info->plane, 0.0, -0.66);
	}
	if (c == 'E')
	{
		set_xy(&info->dir, 0.0, 1.0);
		set_xy(&info->plane, 0.66, 0.0);
	}
	if (c == 'W')
	{
		set_xy(&info->dir, 0.0, -1.0);
		set_xy(&info->plane, -0.66, 0.0);
	}
}

void add_array_map(t_info *info, const char *line, int height)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == ' ')
			info->world_map[height][i] = 0;
		else if (line[i] == '1')
			info->world_map[height][i] = 1;
		else if (line[i] == '2')
			info->world_map[height][i] = 2;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			init_dir(info, line[i]); //사용자 방향 초기화.
			set_xy(&info->pos, i + 0.5, height + 0.5);
			info->world_map[height][i] = 0;
		}
		i++;
	}
}


int init_map(t_info *info, int fd)
{
	int i;
	int height;
	char *line;

	if (!(info->world_map = malloc_map(info)))
		return (0);
	height = 0;
	while (1)
	{
		i = get_next_line(fd, &line);
		if (*line != '\0' && is_map_in_line(line)) //맵라인이 나온다면
		{
			//printf("%s\n", line);
			add_array_map(info, line, height);
			height++;
		}
		free(line);
		if (i <= 0)
			break;
	}
	return (0);
}


// 맵 체크. 리턴 1
int map_check()
{

	//# define IN_MAP(p, c)		(CHECK_TOP(p) && CHECK_BOT(p, c))

	//# define CHECK_TOP(p)		(FINT(p.x) >= 0 && FINT(p.y) >= 0)
	//# define CHECK_BOT(p, c)	(FINT(p.x) < (c).columns && FINT(p.y) < (c).rows)

	// # define FINT(x)			((int)floor(x))

	//# define MAP(p, c) 			(c).map[(FINT(p.y) * (c).columns) + FINT(p.x)]
	//# define MAP_XY(x, y, c) 	(c).map[(FINT(y) * (c).columns) + FINT(x)]
}