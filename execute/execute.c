/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:21:29 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/21 19:21:07 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	actual_len(char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (arg[i])
	{
		if (arg[i] != '\'' && arg[i] != '\"')
			len++;
		i++;
	}
	return (len);
}

static void	allocate_new(t_tokens **tokens)
{
	int		i;
	int		j;
	int		len;
	char	*new_token;

	i = -1;
	j = 0;
	len = actual_len((*tokens)->token);
	new_token = malloc(len + 1);
	while ((*tokens)->token[++i])
		if ((*tokens)->token[i] != '\'' && (*tokens)->token[i] != '\"')
			new_token[j++] = (*tokens)->token[i];
	new_token[j] = '\0';
	free((*tokens)->token);
	(*tokens)->token = new_token;
}

void	remove_quotes(t_tokens **tokens)
{
	int			i;
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp->type != NEWL)
	{
		i = 0;
		while (tmp->token[i])
		{
			if (tmp->token[i] != '\'' && tmp->token[i] != '\"')
				allocate_new(&tmp);
			i++;
		}
		tmp = tmp->next;
	}
}

int	execute(t_tokens *tokens, t_hash_table *env, int stat)
{
/*	int	pipes;

	pipes = check_pipes(tokens);
	if (pipes)
		 stat = execute_with_pipes(tokens, env, pipes);
	else*/
	env_vars(&tokens, env);
	remove_quotes(&tokens);
	stat = execute_no_pipes(tokens, env);
	return (stat);
}
