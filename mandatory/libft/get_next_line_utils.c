/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 03:22:17 by slimvutt          #+#    #+#             */
/*   Updated: 2025/09/07 03:22:17 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char		*res;
	size_t		i;
	size_t		j;
	size_t		totlen;

	totlen = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	res = ft_calloc_gnl(sizeof(char), (totlen + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i ++;
	}
	j = 0;
	while (s2 && s2[j])
		res[i++] = s2[j++];
	free(s1);
	return (res);
}

int	ft_strchr_gnl(char *s, char c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	if (c == *s)
		return (1);
	return (0);
}

size_t	ft_strlen_gnl(char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len ++;
	return (len);
}

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	unsigned char	*p;
	size_t			i;
	size_t			n;

	n = nmemb * size;
	p = malloc(n);
	if (!p)
		return (NULL);
	i = 0;
	while (i < n)
		p[i++] = 0;
	return (p);
}
