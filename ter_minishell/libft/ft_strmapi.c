/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:00:36 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/07 02:00:36 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	str = (char *)(malloc(sizeof(char) * (ft_strlen((char *)s) + 1)));
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i ++;
	}
	str[i] = '\0';
	return (str);
}
