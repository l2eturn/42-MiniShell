/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 03:57:24 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/04 03:57:24 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && (i < n))
	{
		if (s1[i] != s2[i] || (s1[i] == '\0'))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i ++;
	}
	return (0);
}

//#include <stdio.h>
//#include <string.h>

//int main() {
//  char myStr1[] = "ABCD";
//  char myStr2[] = "ABCE";
//  int cmp = strncmp(myStr1, myStr2, 3);
//  if (cmp > 0) {
//    printf("%s is greater than %s\n", myStr1, myStr2);
//  } else if (cmp < 0) {
//    printf("%s is greater than %s\n", myStr2, myStr1);
//  } else {
//    printf("%s is equal to %s\n", myStr1, myStr2);
//  }
//  return 0;
//}