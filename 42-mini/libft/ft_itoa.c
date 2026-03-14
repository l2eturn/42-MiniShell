/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 22:35:44 by cduangpl          #+#    #+#             */
/*   Updated: 2025/08/30 15:11:40 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long nbr)
{
	int	len;

	if (nbr <= 0)
		len = 1;
	else
		len = 0;
	while (nbr != 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

static long	ft_absval(long nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		len;
	char	*result;

	nbr = n;
	len = ft_intlen(nbr);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (nbr == 0)
		result[0] = '0';
	if (nbr < 0)
		result[0] = '-';
	nbr = ft_absval(nbr);
	while (nbr > 0)
	{
		result[--len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (result);
}
