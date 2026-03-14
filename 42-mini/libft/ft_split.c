/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:51:23 by cduangpl          #+#    #+#             */
/*   Updated: 2025/10/02 22:42:42 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *str, char c)
{
	int	count;
	int	x;

	count = 0;
	x = 0;
	while (*str)
	{
		if (*str != c && x == 0)
		{
			x = 1;
			count++;
		}
		else if (*str == c)
			x = 0;
		str++;
	}
	return (count);
}

static char	*fill_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(strs[i++]);
	free(strs);
	return (NULL);
}

static int	split_loop(const char *s, char c, char **res)
{
	size_t	i;
	int		j;
	int		s_word;

	i = 0;
	j = 0;
	s_word = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && s_word < 0)
			s_word = i;
		else if ((s[i] == c || i == ft_strlen(s)) && s_word >= 0)
		{
			res[j] = fill_word(s, s_word, i);
			if (!res[j])
				return (j);
			s_word = -1;
			j++;
		}
		i++;
	}
	return (-1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		err_idx;

	if (!s)
		return (NULL);
	res = ft_calloc((word_count(s, c) + 1), sizeof(char *));
	if (!res)
		return (NULL);
	err_idx = split_loop(s, c, res);
	if (err_idx != -1)
	{
		ft_free(res, err_idx);
		return (NULL);
	}
	return (res);
}

// int main(void)
// {
//     char **arr;
//     int i;

//     arr = ft_split("Hello World 42Bangkok", ' ');
//     printf("Test 1:\n");
//     for (i = 0; arr[i]; i++)
//         printf("[%s]\n", arr[i]);

//     arr = ft_split(",,A,,B,,C,,", ',');
//     printf("\nTest 2:\n");
//     for (i = 0; arr[i]; i++)
//         printf("[%s]\n", arr[i]);

//     arr = ft_split("Split|||This|||Now", '|');
//     printf("\nTest 3:\n");
//     for (i = 0; arr[i]; i++)
//         printf("[%s]\n", arr[i]);

//     return (0);
// }
