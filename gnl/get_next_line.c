/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 00:24:50 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 03:00:27 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*p_s;

	p_s = s;
	while (*p_s != '\0')
	{
		if (*p_s == (char)c)
			return ((char *)p_s);
		p_s++;
	}
	if (c == '\0')
		return ((char *)p_s);
	return (NULL);
}

int	split_line(char **dst, char **line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(*dst);
	if (!(tmp))
		return (-1);
	while (tmp[i] != '\n')
		i++;
	tmp[i] = '\0';
	*line = ft_strdup(tmp);
	free(*dst);
	*dst = ft_strdup(tmp + i + 1);
	free(tmp);
	if (*dst == NULL || *line == NULL)
		return (-1);
	return (0);
}

int	return_fun(int s, char **saves, char **line)
{
	if (s == 0)
	{
		*line = ft_strdup(*saves);
		if (!(*line))
			return (-1);
		free(*saves);
		*saves = NULL;
		return (0);
	}
	if (s == -1)
		return (-1);
	if (split_line(saves, line) == -1)
		return (-1);
	return (1);
}

void	null_check(char **save)
{
	if (*save == NULL)
	{
		*save = (char *)malloc(sizeof(char) * 1);
		*save[0] = '\0';
	}
}

int	get_next_line(int fd, char **line)
{
	char			*buf;
	char			*tmp;
	static char		*saves[OPEN_MAX];
	int				s;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0 || OPEN_MAX <= fd)
		return (-1);
	s = -2;
	null_check(&saves[fd]);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!ft_strchr(saves[fd], '\n'))
	{
		s = read(fd, buf, BUFFER_SIZE);
		if (0 >= s)
			break ;
		buf[s] = '\0';
		tmp = ft_strjoin(saves[fd], buf);
		if (!(tmp))
			return (-1);
		free(saves[fd]);
		saves[fd] = tmp;
	}
	free(buf);
	return (return_fun(s, &saves[fd], line));
}
