/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 03:35:20 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/07 03:35:20 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_incharset(char s, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s == set[i])
			return (1);
		i ++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*newstring;
	int		i;

	i = 0;
	start = 0;
	end = ft_strlen((char *)s1);
	while (is_incharset(s1[start], (char *)set))
		start ++;
	while (end > start && is_incharset(s1[end - 1], (char *)set))
		end --;
	newstring = (char *)(malloc(sizeof(char) * (end - start + 1)));
	if (!newstring)
		return (NULL);
	while (start < end)
	{
		newstring[i] = s1[start];
		start ++;
		i ++;
	}
	newstring[i] = '\0';
	return (newstring);
}
//#include <stdio.h>
//int main(void)
//{
//	char *a = ft_strtrim("Hello World Hi dojfsfolsnfojs");
//	printf("%s",a);

//}
