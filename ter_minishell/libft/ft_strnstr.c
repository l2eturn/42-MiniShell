/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:38:48 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/04 12:38:48 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *substr, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*substr)
		return ((char *)str);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while ((i + j) < len && str[i + j] && str[i + j] == substr[j])
		{
			if (substr[j + 1] == '\0')
				return ((char *)str + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

//#include <stdio.h>
//int	main(void)
//{
//	char	str[] = "Hello World!";
//	char	to_find[] = "o";
//	printf("%s", ft_strnstr(str, to_find,8));
//	return (0);
//}