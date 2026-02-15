/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 07:57:48 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/07 07:57:48 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	size_nb(long int nb)
{
	int	count;

	count = 0;
	if (nb < 0)
		nb *= -1;
	while (nb != 0)
	{
		nb /= 10;
		count ++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*res;
	int			count;
	int			i;
	long int	nb;

	nb = n;
	count = size_nb(nb);
	i = 0;
	if (nb < 0 || nb == 0)
		count ++;
	res = (char *)(malloc(sizeof(char) * (count + 1)));
	if (nb < 0)
	{
		nb *= -1;
		res[0] = '-';
		i ++;
	}
	res[count] = '\0';
	while (count > i)
	{
		count --;
		res[count] = (nb % 10) + '0';
		nb /= 10;
	}
	return (res);
}

// #include <stdio.h>
// int main() 
// {
// 	char * a = ft_itoa(-2147483648LL);
// 	printf("%s\n",a);
// 	free(a);
// 	return 0;
// }
