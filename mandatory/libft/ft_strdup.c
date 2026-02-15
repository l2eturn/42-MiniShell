/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:02:32 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/04 01:02:32 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	int		len;
	int		i;
	char	*arr;

	i = 0;
	len = ft_strlen(str);
	arr = (char *)(malloc(sizeof(char) * (len + 1)));
	while (str[i])
	{
		arr[i] = str[i];
		i ++;
	}
	arr[i] = '\0';
	return (arr);
}

// #include <stdio.h>
// int main(void)
// {
//     char *arr;
//     char test[20] = "HElloWOrld";

//     arr = ft_strdup(test);
//     printf("%s\n",arr);
// }