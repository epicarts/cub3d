/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychoi <ychoi@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 00:25:20 by ychoi             #+#    #+#             */
/*   Updated: 2021/04/13 05:13:27 by ychoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t			dst_len;
	size_t			src_len;
	size_t			copy_len;
	char			*p_src;

	dst_len = 0;
	src_len = 0;
	p_src = src;
	while (*(src++) != '\0')
		src_len++;
	while (*(dst++) != '\0')
		dst_len++;
	dst--;
	copy_len = size - dst_len - 1;
	if (size <= dst_len)
		return (src_len + size);
	while (copy_len && *p_src != '\0')
	{
		*(dst++) = *(p_src++);
		copy_len--;
	}
	*dst = '\0';
	return (dst_len + src_len);
}

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char			*p_dst;
	const unsigned char		*p_src;
	size_t					i;

	i = 0;
	p_dst = dst;
	p_src = src;
	while (i < n)
	{
		*p_dst = *p_src;
		if (*p_dst == (unsigned char)c)
			return (p_dst + 1);
		p_src++;
		p_dst++;
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*s;
	char	*p_s;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (s == NULL)
		return (NULL);
	p_s = ft_memccpy(s, s1, '\0', s1_len + 1);
	ft_strlcat(p_s - 1, (char *)s2, s2_len + 1);
	return (s);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*d1;

	d1 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (d1 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		d1[i] = s1[i];
		i++;
	}
	d1[i] = '\0';
	return (d1);
}
