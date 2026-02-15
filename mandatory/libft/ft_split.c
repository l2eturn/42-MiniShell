/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 04:10:46 by slimvutt          #+#    #+#             */
/*   Updated: 2025/08/07 04:10:46 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(const char *s, char c)
{
	int	i;
	int	flag;
	int	count;

	i = 0;
	flag = 1;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && flag)
		{
			count++;
			flag = 0;
		}
		else if (s[i] == c)
			flag = 1;
		i++;
	}
	return (count);
}

static int	word_len(const char *s, char c)
{
	int	count;

	count = 0;
	while (s[count] && s[count] != c)
		count++;
	return (count);
}

static char	*create_word(const char *s, char c)
{
	char	*str;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = word_len(s, c);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	*free_all(char **res, int last)
{
	while (last >= 0)
		free(res[last--]);
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;

	if (!s)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			res[i] = create_word(s, c);
			if (!res[i])
				return (free_all(res, i - 1));
			i++;
			s += word_len(s, c);
		}
	}
	res[i] = NULL;
	return (res);
}

// #include <stdio.h>
// int main(void)
// {
// 	char **a = ft_split("sfsdfsdfssfdsfsffsfsfds",'s');
// 	while (*a)
// 	{
// 		printf("%s, ",*a);
// 		free(*a);
// 		a ++;
// 	}
// }
