/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 05:03:37 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/04 05:03:37 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

//#include <stdio.h>
//int main()
//{
//    char ch;

//    ch = 'g';
//    printf("%c in uppercase is represented as  %c\n",ch, ft_toupper(ch));

//    return 0;
//}