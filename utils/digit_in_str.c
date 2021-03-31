
#include "../cub3d.h"

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
