/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:41:32 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/04 03:41:32 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i ++;
	}
	return (0);
}

//#include <stdio.h>
//#include <string.h>

//int main() {
//  char myStr1[] = "AB";
//  char myStr2[] = "ABCE";
//  int cmp = ft_strcmp(myStr1, myStr2);
//  if (cmp > 0) {
//    printf("%s is greater than %s\n", myStr1, myStr2);
//  } else if (cmp < 0) {
//    printf("%s is greater than %s\n", myStr2, myStr1);
//  } else {
//    printf("%s is equal to %s\n", myStr1, myStr2);
//  }
//  return 0;
//}