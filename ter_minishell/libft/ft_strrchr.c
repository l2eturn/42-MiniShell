/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 11:44:24 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/04 11:44:24 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;

	len = ft_strlen((char *)s);
	while (len >= 0)
	{
		if ((char)c == *(s + len))
			return ((char *)(s + len));
		--len;
	}
	return (NULL);
}

//#include <stdio.h>
//int main(void)
//{
//	char c[] = "Hello World";
//	char *ptr = ft_strrchr(c,'o');
//	printf("%s",ptr);	
//}