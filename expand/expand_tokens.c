/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:19:40 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/30 21:15:54 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	needs_handling(char *str, int index)
{
	int	i;
	int	len;

	if (index == 0)
		i = index;
	else
		i = index + 1;
	len = safe_strlen(str);
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (QUOTE_HANDLE);
		if (str[i] == '$' && str[i + 1])
			return (ENV_VAR_HANDLE);
		i++;
	}
	return (0);
}

static int	find_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && str[i + 1])
			return (i);
	return (-1);
}

static int	new_handle_index(char *str, int index)
{
	int	i;
	int	len;

	if (index == 0)
		i = index;
	else
		i = index + 1;
	len = safe_strlen(str);
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (index);
		if (str[i] == '$' && str[i + 1])
			return (index);
		i++;
	}
	return (index);
}

static int	env_var_handle(
	t_tokens **tokens, t_hash_table *env, int stat, int handle_index
)
{
	int	dollar_pos;

	dollar_pos = find_dollar((*tokens)->token);
	if (dollar_pos != -1 && (*tokens)->token[dollar_pos + 1] != '?')
		regular(tokens, env, dollar_pos);
	else if (dollar_pos != -1 && (*tokens)->token[dollar_pos + 1] == '?')
		dollar_question_mark(tokens, dollar_pos, stat);
	return (new_handle_index((*tokens)->token, handle_index));
}

void	expand_tokens(t_tokens **tokens, t_hash_table *env, int stat)
{
	int			handle_status;
	int			handle_index;
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp->type != NEWL)
	{
		handle_index = 0;
		while (1)
		{
			handle_status = needs_handling(tmp->token, handle_index);
			if (handle_status == QUOTE_HANDLE)
				handle_index = quote_handle(&tmp, env, stat, handle_index);
			else if (handle_status == ENV_VAR_HANDLE)
				handle_index = env_var_handle(&tmp, env, stat, handle_index);
			if (!handle_status)
				break ;
		}
		tmp = tmp->next;
	}
}
