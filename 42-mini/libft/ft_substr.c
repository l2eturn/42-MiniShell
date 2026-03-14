/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 10:43:13 by cduangpl          #+#    #+#             */
/*   Updated: 2025/08/29 16:25:50 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	copy_len;

	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= s_len)
		copy_len = 0;
	else if (len > s_len - start)
		copy_len = s_len - start;
	else
		copy_len = len;
	sub = (char *)malloc(sizeof(char) * (copy_len + 1));
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, copy_len);
	sub[copy_len] = '\0';
	return (sub);
}

// ft_substr -- extract a substring from a string 
// // 1. Handle invalid input.
//    if (!s)
//    return (NULL);
// // 2. Adjust len if start is out of bounds or len is too long.
// if (start >= s_len)
//    copy_len = 0;
// else if (len > s_len - start)
//    copy_len = s_len - start;
// else
//    copy_len = len;
// // 3. Allocate memory for the substring.
// // Use malloc to avoid redundant zeroing by calloc,
// // and explicitly add the null-terminator.
// sub = (char *)malloc(sizeof(char) * (copy_len + 1));
// if (!sub)
//    return (NULL);
// // 4. Copy the characters into the new memory.
// ft_memcpy(sub, s + start, copy_len);
