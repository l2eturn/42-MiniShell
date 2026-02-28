/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 04:49:29 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/04 04:49:29 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

//#include <stdio.h>
//#include <ctype.h>

//int main() {
//  char c = 'A';
//  if (isalnum(c)) {
//    printf("%c is alphanumeric", c);
//  } else {
//    printf("%c is not alphanumeric", c);
//  }
//  return 0;
//}