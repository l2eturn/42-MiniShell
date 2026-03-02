/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 22:35:44 by cduangpl          #+#    #+#             */
/*   Updated: 2025/10/02 23:11:43 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		uc;
	size_t				i;

	i = 0;
	str = (const unsigned char *)s;
	uc = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == uc)
		{
			return ((void *)&str[i]);
		}
		i++;
	}
	return (NULL);
}

// int main(void)
// {
//     char str[] = "Hello, 42 Network!";
//     char *ptr;
//     ptr = ft_memchr(str, '4', sizeof(str));
//     if (ptr)
//         printf("Found '4' at position: %ld -> \"%s\"\n", ptr - str, ptr);
//     else
//         printf("'4' not found\n");
//     ptr = ft_memchr(str, 'H', sizeof(str));
//     if (ptr)
//         printf("Found 'H' at position: %ld -> \"%s\"\n", ptr - str, ptr);
//     else
//         printf("'H' not found\n");
//     ptr = ft_memchr(str, 'z', sizeof(str));
//     if (ptr)
//         printf("Found 'z' at position: %ld -> \"%s\"\n", ptr - str, ptr);
//     else
//         printf("'z' not found\n");
//     unsigned char data[] = {0x10, 0x20, 0x30, 0x40};
//     unsigned char *found = ft_memchr(data, 0x30, sizeof(data));
//     if (found)
//         printf("Found byte 0x30 at index: %ld\n", found - data);
//     else
//         printf("0x30 not found\n");
//     return (0);
// }

// int main(void)
// {
//     char str[] = "Hello World!";
//     char *res;

//     // Case 1: เจอตัวอักษร 'o'
//     res = (char *)ft_memchr(str, 'o', 12);
//     if (res)
//         printf("Found 'o' at position: %ld\n", res - str);
//     else
//         printf("'o' not found\n");

//     // Case 2: เจอตัวอักษร 'z' → ไม่มี
//     res = (char *)ft_memchr(str, 'z', 12);
//     if (res)
//         printf("Found 'z' at position: %ld\n", res - str);
//     else
//         printf("'z' not found\n");

//     // Case 3: จำกัดจำนวนค้นหา n=5 (ไม่เจอ 'W')
//     res = (char *)ft_memchr(str, 'W', 5);
//     if (res)
//         printf("Found 'W' at position: %ld\n", res - str);
//     else
//         printf("'W' not found in first 5 bytes\n");

//     return 0;
// }