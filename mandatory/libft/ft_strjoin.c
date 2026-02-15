/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 03:01:13 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/07 03:01:13 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)(malloc(sizeof(char) * (ft_strlen((char *)s1)
					+ ft_strlen((char *)s2) + 1)));
	if (!str)
		return (NULL);
	i = 0;
	while (*s1)
	{
		str[i] = *s1;
		s1 ++;
		i ++;
	}
	while (*s2)
	{
		str[i] = *s2;
		s2 ++;
		i ++;
	}
	str[i] = '\0';
	return (str);
}
