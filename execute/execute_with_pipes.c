/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:58:01 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/29 12:54:34 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	get_commands(t_tokens *tokens)
{
	int	res;

	res = 0;
	while (tokens)
	{
		if (tokens->type == COMMAND)
			res++;
		tokens = tokens->next;
	}
	return (res);
}

static char	***get_argvs(t_tokens *tokens)
{
	char	***res;
	int		i;

	i = get_commands(tokens);
	res = malloc(sizeof(char **) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (tokens)
	{
		while (tokens && tokens->type != COMMAND)
			tokens = tokens->next;
		res[i] = tokens_to_strings(tokens);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	execute_with_pipes(t_tokens *tokens, t_hash_table *envp)
{
	char	***argv_container;
	int		stat;
	int		i;

	argv_container = get_argvs(tokens, pipes);
	stat = 0;
	i = 0;
	while (tokens)
	{
		while (tokens && tokens->type != BUILTIN && tokens->type != COMMAND)
			tokens = tokens->next;
		if (tokens->type == COMMAND)
		{
			stat = handle_binary(argv_container[i]);
			i++;
		}
		else
			stat = handle_builti(tokens);
	}
}
