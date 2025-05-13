/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:05:27 by armarake          #+#    #+#             */
/*   Updated: 2025/05/13 14:45:57 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	**tokens_to_strings(t_tokens *cmd)
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
	while (cmd->type != NEWL)
	{
		res[i++] = cmd->token;
		cmd = cmd->next;
	}
	return (res);
}

int check_pipes(t_tokens *tokens)
{
	int	pipe_count;

	pipe_count = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			pipe_count++;
		tokens = tokens->next;
	}
	return (pipe_count);
}

int	define_type(t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->type == BUILTIN)
			return (BUILTIN);
		if (tokens->type == COMMAND)
			return (COMMAND);
		tokens = tokens->next;
	}
	return (NONE);
}

int	quit_with_error(char *msg, int stat)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (stat);
}
