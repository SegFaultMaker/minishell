/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:24:49 by armarake          #+#    #+#             */
/*   Updated: 2025/05/30 21:59:55 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static void	remove_quotes(t_tokens **tokens, char quote)
{
	int		len;
	char	*new;

	len = ft_strlen((*tokens)->token) - 2;
	new = malloc(len + 1);
	remove_quote_helper((*tokens)->token, quote, &new, len);
	free((*tokens)->token);
	(*tokens)->token = new;
}

void	find_positions(
	char *str, int *quote_start, int *quote_end, char *quote
)
{
	int		i;
	int		len;

	i = *quote_start;
	*quote = '\0';
	len = ft_strlen(str);
	while (i < len)
	{
		if (!(*quote) && (str[i] == '\'' || str[i] == '\"'))
		{
			*quote = str[i];
			*quote_start = i;
			while (str[++i])
			{
				if (str[i] == *quote)
				{
					*quote_end = i;
					return ;
				}
			}
		}
		i++;
	}
}

int	quote_handle(t_tokens **tokens, t_hash_table *env, int stat, int index)
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
		if (dollar_pos != -1 && (*tokens)->token[dollar_pos + 1] != '?')
			regular(tokens, env, dollar_pos);
		else if (dollar_pos != -1 && (*tokens)->token[dollar_pos + 1] == '?')
			dollar_question_mark(tokens, dollar_pos, stat);
		quote_end = find_new_end((*tokens)->token, quote_start, quote);
	}
	if (quote && (*tokens)->token[quote_start] == quote
		&& (*tokens)->token[quote_end] == quote)
	{
		remove_quotes(tokens, quote);
		quote_end -= 2;
	}
	return (quote_end);
}
