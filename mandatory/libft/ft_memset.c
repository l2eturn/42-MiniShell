/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:41:41 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/05 01:41:41 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)(s);
	while (i < n)
	{
		*p = (unsigned char )c;
		p ++;
		i ++;
	}
	return (s);
}

//#include <stdio.h>
//#include <string.h>
//int main(void)
//{
//	char str[50];
//	strcpy(str, "This is string.h library function");
//	puts(str);
//	ft_memset(str, '$', 5);
//	puts(str);
//	return (0);
//}