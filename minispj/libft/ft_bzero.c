/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:52:15 by cduangpl          #+#    #+#             */
/*   Updated: 2025/10/02 22:44:21 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*(ptr++) = 0;
}

// int main(void)
// {
//     char buffer[20];

//     // Fill buffer with 'A'
//     memset(buffer, 'A', sizeof(buffer));
//     printf("Before bzero: ");
//     for (int i = 0; i < 10; i++)
//         printf("%d ", buffer[i]);
//     printf("\n");

//     // Apply ft_bzero
//     ft_bzero(buffer, 5);
//     printf("After bzero (first 5 bytes): ");
//     for (int i = 0; i < 10; i++)
//         printf("%d ", buffer[i]);
//     printf("\n");

//     return 0;
// }