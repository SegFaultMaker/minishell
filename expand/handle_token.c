/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:24:49 by armarake          #+#    #+#             */
/*   Updated: 2025/05/30 20:46:28 by armarake         ###   ########.fr       */
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

static void	find_positions(char *str, int *quote_start, int *quote_end, char *quote)
{
	int		i;
	int		len;
	int		stop;

	i = *quote_start;
	stop = 0;
	*quote = '\0';
	len = ft_strlen(str);
	while (i < len)
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
		i++;
	}
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
	int		count;
	char	*new;

	i = 0;
	j = 0;
	count = 0;
	len = ft_strlen((*tokens)->token) - 2;
	new = malloc(len + 1);
	while ((*tokens)->token[i] && j < len)
	{
		if ((*tokens)->token[i] == quote)
			count++;
		if ((*tokens)->token[i] == quote && count > 2)
		{
			new[j] = (*tokens)->token[i];
			j++;
		}
		else if ((*tokens)->token[i] != quote)
		{
			new[j] = (*tokens)->token[i];
			j++;
		}
		i++;
	}
	new[len] = '\0';
	free((*tokens)->token);
	(*tokens)->token = new;
}

int	handle_token(t_tokens **tokens, t_hash_table *env, int stat, int index)
{
	int		quote_start;
	int		quote_end;
	int		dollar_pos;
	char	quote;

	quote_start = index;
	quote_end = index;
	dollar_pos = -1;
	find_positions((*tokens)->token, &quote_start, &quote_end, &quote);
	while (must_expand((*tokens)->token, quote_start, quote_end, &dollar_pos))
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
