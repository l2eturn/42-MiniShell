/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 02:06:21 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/05 02:06:21 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *) s;
	while (n > 0)
	{
		*p = '\0';
		p ++;
		n --;
	}
}

//#include <stdio.h>
//#include <strings.h> // For bzero
//int main() {
//    char buffer[20];
//    // Initialize the buffer with some data
//    sprintf(buffer, "Hello, World!");
//    printf("Before bzero: %s\n", buffer);
//    // Set the first 5 bytes of the buffer to zero
//    ft_bzero(buffer, 5);
//    printf("After bzero: %s\n", buffer); 
//    return 0;
//}