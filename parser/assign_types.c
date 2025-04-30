/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:26:10 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/30 17:59:24 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redir_pipe(t_types type)
{
	if (type == INPUT || type == OUTPUT
		|| type == HERE_DOC || type == APPEND
		|| type == PIPE)
		return (1);
	return (0);
}

static t_types	get_type(char *token)
{
	if (!ft_strcmp(token, "echo")
		|| !ft_strcmp(token, "cd")
		|| !ft_strcmp(token, "pwd")
		|| !ft_strcmp(token, "export")
		|| !ft_strcmp(token, "unset")
		|| !ft_strcmp(token, "env")
		|| !ft_strcmp(token, "exit"))
		return (BUILTIN);
	else if ((ft_strlen(token) == 1
				|| ft_strlen(token) == 2))
	{
		if (*token == '<')
			return (INPUT);
		else if (*token == '>')
			return (OUTPUT);
		else if (!ft_strcmp(token, "<<"))
			return (HERE_DOC);
		else if (!ft_strcmp(token, ">>"))
			return (APPEND);
		else if (!ft_strcmp(token, "|"))
			return (PIPE);
	}
	return (COMMAND);
}

void	assign_types(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	if (!tmp || !tmp->token || !*(tmp->token))
		return ;
	while (tmp)
	{
		tmp->type = get_type(tmp->token);
		if (tmp->type == BUILTIN || tmp->type == COMMAND)
		{
			tmp = tmp->next;
			while (tmp && !is_redir_pipe(tmp->type))
			{
				tmp->type = ARGUMENT;
				tmp = tmp->next;
				if (tmp)
					tmp->type = get_type(tmp->token);
			}
		}
		if (!tmp)
			return ;
		else
			tmp = handle_redir_pipe(&tmp);
	}
}
