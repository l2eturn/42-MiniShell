/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:02:39 by cduangpl          #+#    #+#             */
/*   Updated: 2025/08/28 23:59:07 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)dst;
	while (n > 0)
	{
		*(ptr++) = (unsigned char)c;
		n--;
	}
	return (dst);
}
