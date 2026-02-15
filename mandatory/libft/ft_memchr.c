/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:27:40 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/05 11:27:40 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ch;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	ch = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == ch)
			return (str + i);
		i++;
	}
	return (NULL);
}

//#include <stdio.h>
//#include <string.h>

//int main() {
//    char data[] = "Hello World!";
//    char *result;

//    // Search for 'o' in the first 12 bytes of 'data'
//    result = (char *)ft_memchr(data, 'o', 12);

//    if (result != NULL) {
//        printf("Character 'o' found at position: %ld\n", result - data);
//        printf("String from 'o': %s\n", result);
//    } else {
//        printf("Character 'o' not found.\n");
//    }

//    // Search for 'z' in the first 12 bytes of 'data'
//    result = (char *)ft_memchr(data, 'z', 12);

//    if (result != NULL) {
//        printf("Character 'z' found at position: %ld\n", result - data);
//    } else {
//        printf("Character 'z' not found.\n");
//    }

//    return 0;
//}