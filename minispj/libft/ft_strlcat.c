/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 00:57:13 by cduangpl          #+#    #+#             */
/*   Updated: 2025/08/30 16:17:50 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	copy_len;

	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	if (dlen >= dstsize)
		return (dstsize + slen);
	copy_len = dstsize - dlen - 1;
	if (copy_len > 0)
	{
		if (slen < copy_len)
			ft_memcpy(dst + dlen, src, slen + 1);
		else
		{
			ft_memcpy(dst + dlen, src, copy_len);
			dst[dstsize - 1] = '\0';
		}
	}
	else
	{
		if (dstsize > 0)
			dst[dlen] = '\0';
	}
	return (dlen + slen);
}
