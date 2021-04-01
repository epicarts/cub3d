
#include "../cub3d.h"

int is_map(int c)
{
	if ((c == ' ') || (c == '0') || (c == '1') || (c == '2') ||
		(c == 'N') || (c == 'S') || (c == 'E') || (c == 'W'))
		return (1);
	return (0);
}

int is_map_in_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!is_map(line[i]))
			return (0);
		i++;
	}
	return (1);
}