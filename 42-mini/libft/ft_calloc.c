/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:52:15 by cduangpl          #+#    #+#             */
/*   Updated: 2025/10/02 22:51:51 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (count != 0 && size != 0)
	{
		total_size = count * size;
		if (total_size / count != size)
			return (NULL);
	}
	else
		total_size = 0;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}

// int main(void)
// {
//     int *arr;
//     int i;

//     // ขอ array int ขนาด 5 ตัว (ทุกตัวต้องเริ่มจาก 0)
//     arr = (int *)ft_calloc(5, sizeof(int));
//     if (!arr)
//     {
//         printf("Allocation failed!\n");
//         return (1);
//     }

//     printf("Test 1: Array of 5 integers\n");
//     for (i = 0; i < 5; i++)
//         printf("arr[%d] = %d\n", i, arr[i]); // ควรได้ 0 ทุกตัว

//     free(arr);

//     // Test overflow: count * size > SIZE_MAX
//     size_t big_count = (size_t)-1;
//     arr = ft_calloc(big_count, sizeof(int));
//     if (!arr)
//         printf("\nTest 2: Overflow check worked (NULL returned)\n");

//     return 0;
// }

// why need to change becuse it does not check for integer overflow 
// when multiplying count and size. A malicious count or 
// size value could cause the multiplication to wrap around,
// resulting in a much smaller allocation than intended
// >>> if (size != 0 && count > SIZE_MAX / size)
// Integer overflow check: The multiplication of two size_t 
// variables can overflow if the result exceeds SIZE_MAX. 
// The check if (size != 0 && count > SIZE_MAX / size) 
// correctly prevents this. If an overflow is detected, 
// the function returns NULL, just as malloc would on failure.
// >>> ft_memset(tmp, 0, total_size)
// Use of memset: For zeroing out the memory, 
// using the standard memset function is generally
// preferred over a manual while loop. Compilers and 
// standard libraries are highly optimized for memset, often 
// using hardware-specific instructions for maximum speed.