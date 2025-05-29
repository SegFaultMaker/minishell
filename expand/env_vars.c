/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:19:40 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/30 00:12:36 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	needs_handling(char *str, int index)
{
	int	i;

	if (index == 0)
		i = index;
	else
		i = index + 1;
	while (i < safe_strlen(str))
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
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && str[i + 1])
			return (i);
	return (-1);
}

void	expand_tokens(t_tokens **tokens, t_hash_table *env, int stat)
{
	int			handle_status;
	int			handle_index;
	int			dollar_pos;
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp->type != NEWL)
	{
		handle_index = 0;
		while (1)
		{
			handle_status = needs_handling(tmp->token, handle_index);
			if (handle_status == QUOTE_HANDLE)
				handle_index = handle_token(&tmp, env, stat, handle_index);
			else if (handle_status == ENV_VAR_HANDLE)
			{
				dollar_pos = find_dollar(tmp->token);
				if (dollar_pos != -1  && tmp->token[dollar_pos + 1] != '?')
					regular(&tmp, env, dollar_pos);
				else if (dollar_pos != -1 && tmp->token[dollar_pos + 1] == '?')
					dollar_question_mark(&tmp, dollar_pos, stat);
			}
			if (!handle_status)
				break ;
		}
		tmp = tmp->next;
	}
}
