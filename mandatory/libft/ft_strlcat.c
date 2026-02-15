/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 07:04:59 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/04 07:04:59 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;
	size_t	i;

	len_d = 0;
	while (dest[len_d] && len_d < size)
		len_d++;
	len_s = 0;
	while (src[len_s])
		len_s++;
	if (len_d == size)
		return (size + len_s);
	i = 0;
	while (src[i] && (len_d + i + 1 < size))
	{
		dest[len_d + i] = src[i];
		i++;
	}
	if (len_d + i < size)
		dest[len_d + i] = '\0';
	return (len_d + len_s);
}
