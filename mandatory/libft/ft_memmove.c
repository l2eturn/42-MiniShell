/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 06:11:53 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/05 06:11:53 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	if (d < s)
	{
		while (i < n)
		{
			d[i] = s[i];
			i ++;
		}
	}
	else if (d > s)
	{
		while (n--)
			d[n] = s[n];
	}
	return (dest);
}

//#include <stdio.h>
//#include <string.h>

//int main()
//{
//    char str1[] = "GeeksABCDEFG"; // Array of size 100
//    char str2[] = "Quiz"; // Array of size 5

//    puts("str1 before memmove ");
//    puts(str1);

//    ft_memmove(str1 + 3, str2, sizeof(str2));

//    puts("\nstr1 after memmove ");
//    puts(str1);

//    return 0;
//}