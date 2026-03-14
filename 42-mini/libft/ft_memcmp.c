/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:02:39 by cduangpl          #+#    #+#             */
/*   Updated: 2025/10/02 23:09:46 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	i = 0;
	str1 = (const unsigned char *) s1;
	str2 = (const unsigned char *) s2;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

// int main(void)
// {
//     char a1[] = "Hello";
//     char a2[] = "Hello";
//     char b1[] = "Hello";
//     char b2[] = "Hella";
//     char c1[] = "ABC";
//     char c2[] = "ABD";

//     // Case 1: เหมือนกันทุก byte
//     printf("Test 1 (same): %d\n", ft_memcmp(a1, a2, 5));

//     // Case 2: ต่างกันตัวท้าย
//     printf("Test 2 (diff at end): %d\n", ft_memcmp(b1, b2, 5));

//     // Case 3: ต่างกันที่ตัว 3
//     printf("Test 3 (diff at 3rd): %d\n", ft_memcmp(c1, c2, 3));

//     // Case 4: เปรียบเทียบแค่บางส่วน
//     printf("Test 4 (partial compare): %d\n", ft_memcmp(c1, c2, 2));

//     return 0;
// }