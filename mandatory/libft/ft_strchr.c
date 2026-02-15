/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 02:36:47 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/04 02:36:47 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

//#include <stdio.h>
//#include <string.h>
//int main () 
//{
//   const char str[] = "Tutorialspoint";
//   // "ch" is search string
//   const char ch = 's';
//   char *ret;
//   ret = ft_strchr(str, ch);
//   printf("%s\n",ret);
//   return(0);
//}
