
#include "../cub3d.h"
// map only  0, 1, 2, N,S,E,W
int is_map_in_line(int c)
{
	if ((c == ' ') || (c == 0) || (c == 1) || (c == 2) ||
		(c == 'N') || (c == 'S') || (c == 'E') || (c == 'W'))
		return (1);
	return (0);
}


int init_map(t_info *info, int fd)
{
	return 0;
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