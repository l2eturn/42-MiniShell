/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:53:59 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/04 04:53:59 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

//#include <stdio.h>

//int main() {
//  int c1 = 65; // 'A'
//  int c2 = 128; // Not an ASCII character
//  int c3 = 0;   // Null character

//  if (ft_isascii(c1)) {
//    printf("%d is an ASCII character\n", c1);
//  }
//  if (ft_isascii(c2)) {
//    printf("%d is an ASCII character\n", c2);
//  } else {
//    printf("%d is not an ASCII character\n", c2);
//  }
//  if (ft_isascii(c3)) {
//      printf("%d is an ASCII character\n", c3);
//  }
//  return 0;
//}