/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 23:52:15 by cduangpl          #+#    #+#             */
/*   Updated: 2026/02/27 14:20:37 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static int	handle_overflow(long long int result, int sign)
{
	if (sign == -1 && result > 2147483648LL)
		return (-2147483648);
	if (sign == 1 && result > 2147483647LL)
		return (2147483647);
	return ((int)(result * sign));
}

int	ft_atoi(const char *str)
{
	long long int	result;
	int				sign;
	int				i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (handle_overflow(result, sign));
}

// The atoi() function converts a string to its int representation.
// 1. The string passed as parameter may begin with an 
// arbitrary number of whitespaces as determined by isspace(3)
// 2. After the arbitrary number of whitespaces,
// there can be one single optional '+' or '-' sign
// 3. The remainder of the string will be converted to an int,
// stopping at the first character which is not a 
// valid digit in the given base (in our case we only need to manage 
// base 10, so the valid digits are 0-9)
// **isspace(3)***
// \t => tabulation
// \n => new line
// \v => vertical tabulation
// \f => form feed
// \r => carriage return
// ' ' => space
