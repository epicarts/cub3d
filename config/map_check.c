
#include "../cub3d.h"


int **copy_map(int **src_map, int y, int x)
{
	int **dst_map;
	int i;
	int j;

	if (!(dst_map = (int**)malloc(sizeof(int*) * y)))
		return (NULL);
	i = 0;
	while (i < y)
	{
		j = 0;
		dst_map[i] = (int*)malloc(sizeof(int) * x);
		while (j < x)
		{
			if (src_map[i][j] == 2 || src_map[i][j] == 0)
				dst_map[i][j] = 0;
			else
				dst_map[i][j] = 1;
			j++;
		}
		i++;
	}
	return dst_map;
}

void free_copy_map(int **map, int y)
{
	int i;

	i = 0;
	while (i < y)
	{
		free(map[i]);
		i++;
	}
	free(map);
}


int is_in_map(t_map_check *m, int y, int x)
{
	if (y > m->map_size.y - 1 || x > m->map_size.x - 1)
		return (0);
	return (1);
}

int is_visited(t_map_check *m, int y, int x)
{
	if (m->map[y][x] == 0)
		return (0);
	return (1);
}

// visited = -1
int dfs(t_map_check *m, int y, int x)
{
	int i;

	if (m->result == -1)
		return (-1);
	m->map[y][x] = VISITED; //방문하면
	i = -1;
	while (++i < 4)
	{
		//방문한 곳이 아니어야 하고, 맵밖이 아니야한다.
		//방문한 곳이 아닌것은 괜찮지만, 맵밖으로 나가면 안댐. 즉 out이면 안댐.
		if (is_in_map(m, y + m->dir[i].y, x + m->dir[i].x)) //맵 안인가?
		{
			if (!is_visited(m, y + m->dir[i].y, x + m->dir[i].x)) //방문했으면 ? 들어가기.
				dfs(m, y + m->dir[i].y, x + m->dir[i].x);
		}
		else //맵 밖이 절대 나오면 안댐.
			m->result = -1;
	}
	return (1);
}

// 맵 체크. 리턴 1
int map_check(int **src_map, t_xy pos, int map_y, int map_x)
{
	t_map_check map_info;

	set_int_xy(&map_info.dir[0], 1, 0);
	set_int_xy(&map_info.dir[1], 0, 1);
	set_int_xy(&map_info.dir[2], -1, 0);
	set_int_xy(&map_info.dir[3], 0, -1);
	map_info.map_size.y = map_y;
	map_info.map_size.x = map_x;
	if (!(map_info.map = copy_map(src_map, map_y, map_x)))
		return (-1); //실패.
	map_info.result = 1;
	dfs(&map_info, (int)pos.x, (int)pos.y);
	for (int i = 0; i<map_y; i++) {
		for (int j = 0; j < map_x; j++)
			printf("%d ", map_info.map[i][j]);
		printf("\n");
	}
	free_copy_map(map_info.map, map_y);
	if (map_info.result == -1)
		return (-1);
	printf("==========================\n\n");
	return (0);
}

