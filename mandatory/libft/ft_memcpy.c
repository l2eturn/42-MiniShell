/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 03:14:28 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/05 03:14:28 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	unsigned const char	*s;

	d = dest;
	s = src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i ++;
	}
	return (dest);
}
//#include <stdio.h>
//int main(void)
//{
//	char src[50] = "mahmudulhasanjony";
//	char dest[50];
//	char *ret;

//	ret = ft_memcpy(dest, src, 9);
//	printf("%s", ret);
//	return (0);
//}