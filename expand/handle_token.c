/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:24:49 by armarake          #+#    #+#             */
/*   Updated: 2025/05/30 14:51:54 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	must_expand(char *str, int start, int end, int *doll_pos)
{
	int i;

	if (str[start] == '\'')
		return (0);
	i = start - 1;
	while (str[++i] && i < end)
		if (str[i] == '$' && str[i + 1])
		{
			*doll_pos = i;
			return (1);
		}
	return (0);
}

static void	check_positions(char *str, int *quote_start, int *quote_end, char *quote)
{
	if (*quote_start == -1 && *quote_end == -1)
	{
		*quote_start = 0;
		*quote_end = ft_strlen(str) - 1;
		*quote = '\0';
	}
}

static void	find_positions(char *str, int *quote_start, int *quote_end, char *quote)
{
	int		i;
	int		stop;

	i = -1;
	stop = 0;
	*quote_start = -1;
	*quote_end = -1;
	*quote = '\0';
	while (str[++i])
	{
		if (stop)
			break ;
		if (!(*quote) && (str[i] == '\'' || str[i] == '\"'))
		{
			*quote = str[i];
			*quote_start = i;
			while (str[++i])
				if (str[i] == *quote)
				{
					*quote_end = i;
					stop = 1;
					break ;
				}
		}
	}
	check_positions(str, quote_start, quote_end, quote);
}

static int	find_new_end(char *str, int start, char quote)
{
	int	i;

	i = start + 1;
	while (str[i])
	{
		if (str[i] == quote)
			break ;
		i++;
	}
	return (i);
}

static void	remove_quotes(t_tokens **tokens, char quote)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = -1;
	j = 0;
	len = ft_strlen((*tokens)->token) - 2;
	new = malloc(len + 1);
	while ((*tokens)->token[++i])
		if ((*tokens)->token[i] != quote)
			new[j++] = (*tokens)->token[i];
	new[len] = '\0';
	free((*tokens)->token);
	(*tokens)->token = new;
}

int	handle_token(t_tokens **tokens, t_hash_table *env, int stat, int index)
{
	int		quote_start;
	int		quote_end;
	int		dollar_pos;
	int		expand_status;
	char	quote;

	dollar_pos = -1;
	find_positions((*tokens)->token + index, &quote_start, &quote_end, &quote);
	expand_status = must_expand((*tokens)->token + index, quote_start, quote_end, &dollar_pos);
	if (expand_status)
	{
		if (dollar_pos != -1  && (*tokens)->token[dollar_pos + 1] != '?')
			regular(tokens, env, dollar_pos);
		else if (dollar_pos != -1 && (*tokens)->token[dollar_pos + 1] == '?')
			dollar_question_mark(tokens, dollar_pos, stat);
		quote_end = find_new_end((*tokens)->token, quote_start, quote);
	}
	if (quote && (*tokens)->token[quote_start] == quote && (*tokens)->token[quote_end] == quote)
	{
		remove_quotes(tokens, quote);
		quote_end -= 2;
	}
	return (quote_end);
}
