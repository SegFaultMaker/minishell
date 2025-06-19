/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:19:40 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/19 16:55:51 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	calculate_final_len(char *token, t_hash_table *env, int stat)
{
	int	i;
	int	len;
	int	quote;
	int	final_len;

	len = initialize_vars(&i, &quote, &final_len, token);
	while (i < len)
	{
		if (quote_start(token, &quote, &i))
			continue ;
		else if (quote_end(token, &quote, &i))
			continue ;
		if (token[i] == '$' && token[i + 1] && (ft_isalnum(token[i + 1])
				|| token[i + 1] == '_' || token[i + 1] == '?') && quote != '\'')
		{
			if (token[i + 1] == '?')
				final_len += dollar_question_mark_len(&i, stat);
			else
				final_len += env_var_len(token, &i, env);
			continue ;
		}
		final_len++;
		i++;
	}
	return (final_len);
}

char	*remove_and_expand_quotes(char *token, t_hash_table *env, int stat)
{
	t_data	*data;
	char	*result;

	data = init_data(token, stat);
	result = malloc(calculate_final_len(token, env, stat) + 1);
	while (data->i < data->len)
	{
		if (quote_start(token, &(data->quote), &(data->i)))
			continue ;
		else if (quote_end(token, &(data->quote), &(data->i)))
			continue ;
		if (token[data->i] == '$' && token[data->i + 1]
			&& (ft_isalnum(token[data->i + 1]) || token[data->i + 1] == '_'
				|| token[data->i + 1] == '?') && data->quote != '\'')
		{
			if (token[data->i + 1] == '?')
				handle_dollar_question_mark(&result, &data->i, &data->j, stat);
			else
				handle_env_var(&result, data, env);
			continue ;
		}
		result[(data->j)++] = token[(data->i)++];
	}
	result[data->j] = '\0';
	return (free(data->token), free(data), result);
}

static void	re_assign(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp->type != NEWL)
	{
		if (tmp->type == COMMAND && get_type(tmp->token) == BUILTIN)
			tmp->type = BUILTIN;
		tmp = tmp->next;
	}
}

void	expand_tokens(t_tokens **tokens, t_hash_table *env, int stat)
{
	char		*new_token;
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp->type != NEWL)
	{
		new_token = remove_and_expand_quotes(tmp->token, env, stat);
		free(tmp->token);
		tmp->token = NULL;
		tmp->token = new_token;
		tmp = tmp->next;
	}
	re_assign(tokens);
}
