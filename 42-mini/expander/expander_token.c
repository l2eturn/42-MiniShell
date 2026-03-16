/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/16 14:40:30 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_quote_status(char c, bool *in_single, bool *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	if (c == '\"' && !(*in_single))
		*in_double = !(*in_double);
}

static char	*handle_dollar_sign(char *token, int *i, char ***env_ptr,
	t_exp_tmp params)
{
	char	*addition;
	char	*tmp;
 
	if (!is_expandable_char(token[*i + 1]))
	{
		tmp = ft_strdup("");
		addition = ft_strjoin_char1(tmp, token[(*i)++]);
		free(tmp);
		return (addition);
	}
	(*i)++;
	addition = expand_variable(token, i, env_ptr, params);
	return (addition);
}

static char	*process_char(char *expanded, char *token, int *i,
	t_exp_tmp params)
{
	char	*addition;
	char	*tmp;
 
	update_quote_status(token[*i], params.in_single, params.in_double);
	if (token[*i] != '$')
	{
		tmp = ft_strjoin_char1(expanded, token[(*i)++]);
		free(expanded);
		return (tmp);
	}
	addition = handle_dollar_sign(token, i, params.env_ptr, params);
	if (addition == NULL)
		return (NULL);
	tmp = ft_strjoin(expanded, addition);
	free(expanded);
	free(addition);
	return (tmp);
}

char	*expand_token(char *token, char ***env_ptr, int *exit_status)
{
	char		*expanded;
	int			i;
	bool		in_single;
	bool		in_double;
	t_exp_tmp	params;
 
	expanded = ft_strdup("");
	i = 0;
	in_single = false;
	in_double = false;
	params.in_single = &in_single;
	params.in_double = &in_double;
	params.exit_status = exit_status;
	params.env_ptr = env_ptr;
	while (token[i] != '\0')
	{
		expanded = process_char(expanded, token, &i, params);
		if (expanded == NULL)
			return (NULL);
	}
	return (expanded);
}

// #include "minishell.h"

// static void	update_quote_status(char c, bool *in_single, bool *in_double)
// {
// 	if (c == '\'' && !(*in_double))
// 		*in_single = !(*in_single);
// 	if (c == '\"' && !(*in_single))
// 		*in_double = !(*in_double);
// }

// static char	*handle_dollar_sign(char *token, int *i, char ***env_ptr,
// 	t_exp_tmp params)
// {
// 	char	*addition;

// 	if (!is_expandable_char(token[*i + 1]))
// 		return (ft_strjoin_char1(ft_strdup(""), token[(*i)++]));
// 	(*i)++;
// 	addition = expand_variable(token, i, env_ptr, params);
// 	return (addition);
// }

// static char	*process_char(char *expanded, char *token, int *i,
// 	t_exp_tmp params)
// {
// 	char	*addition;
// 	char	*tmp;

// 	update_quote_status(token[*i], params.in_single, params.in_double);
// 	if (token[*i] != '$')
// 	{
// 		tmp = ft_strjoin_char1(expanded, token[(*i)++]);
// 		free(expanded);
// 		return (tmp);
// 	}
// 	addition = handle_dollar_sign(token, i, params.env_ptr, params);
// 	if (addition == NULL)
// 		return (NULL);
// 	tmp = ft_strjoin(expanded, addition);
// 	free(expanded);
// 	free(addition);
// 	return (tmp);
// }

// char	*expand_token(char *token, char ***env_ptr, int *exit_status)
// {
// 	char		*expanded;
// 	int			i;
// 	bool		in_single;
// 	bool		in_double;
// 	t_exp_tmp	params;

// 	expanded = ft_strdup("");
// 	i = 0;
// 	in_single = false;
// 	in_double = false;
// 	params.in_single = &in_single;
// 	params.in_double = &in_double;
// 	params.exit_status = exit_status;
// 	params.env_ptr = env_ptr;
// 	while (token[i] != '\0')
// 	{
// 		expanded = process_char(expanded, token, &i, params);
// 		if (expanded == NULL)
// 			return (NULL);
// 	}
// 	return (expanded);
// }
