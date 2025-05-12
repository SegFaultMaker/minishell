/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:21:29 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/12 17:22:29 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**tokens_to_strings(t_tokens *cmd)
{
	char		**res;
	int			i;
	t_tokens	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp->type != NEWL)
	{
		i++;
		tmp = tmp->next;
	}
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
	{
		ft_putstr_fd("minishell: execution: malloc error\n", STDERR_FILENO);
		return (NULL);
	}
	res[i] = NULL;
	i = 0;
	while (tokens->type != NEWL)
	{
		res[i++] = tokens->token;
		tokens = token->next;
	}
	return (res);
}

int	execute(t_tokens *tokens, t_hash_table *env, int stat)
{
	t_tokens	*tmp;
	char		*argv[];
	int			pipes;

	tmp = tokens;
	pipes = check_pipes(tokens);
	if (pipes)
		stat = execute_with_pipes(tokens, env, pipes);
	else
		stat = execute_command_no_pipes(tokens, env);
	return (stat);
}

< input grep test > output
