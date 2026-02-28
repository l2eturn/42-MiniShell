/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:14:51 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/04 04:14:51 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	int		sign;
	long	res;
	int		i;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i ++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i ++;
	}
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i ++;
	}
	return ((sign) * (res));
}

//#include <stdio.h>
//int	main(int ac , char **av)
//{
//	ac = ac - 1;
//	//char arr[] = " 						-1321AAAAAAAB";
//	int a = ft_atoi(av[1]);
//	printf("%d",a);
//}
////2147483647
////-2147483648