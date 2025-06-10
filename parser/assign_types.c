/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:44:11 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/10 22:44:43 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_types	get_type(char *token)
{
	if (!ft_strcmp(token, "echo") || !ft_strcmp(token, "cd")
		|| !ft_strcmp(token, "pwd")
		|| !ft_strcmp(token, "export")
		|| !ft_strcmp(token, "unset")
		|| !ft_strcmp(token, "env")
		|| !ft_strcmp(token, "exit"))
		return (BUILTIN);
	else if ((ft_strlen(token) == 1 || ft_strlen(token) == 2))
	{
		if (!ft_strcmp(token, "\n"))
			return (NEWL);
		if (!ft_strcmp(token, "<"))
			return (INPUT);
		else if (!ft_strcmp(token, ">"))
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

static t_tokens	*handle_redirs(t_tokens **tokens)
{
	t_tokens	*tmp;
	int			is_file;

	tmp = *tokens;
	if (tmp->type == OUTPUT || tmp->type == INPUT || tmp->type == APPEND)
		is_file = 1;
	else if (tmp->type == HERE_DOC)
		is_file = 0;
	tmp = tmp->next;
	tmp->type = get_type(tmp->token);
	if (is_redir_pipe(tmp->type))
		return (tmp);
	if (tmp && tmp->next)
	{
		if (is_file)
			tmp->type = FILE_NAME;
		else
			tmp->type = LIMITER;
		tmp = tmp->next;
	}
	return (tmp);
}

static t_tokens	*handle_commands(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	tmp = tmp->next;
	while (tmp)
	{
		tmp->type = get_type(tmp->token);
		if (tmp->type == PIPE || tmp->type == NEWL)
			break ;
		else if (is_redir_pipe(tmp->type))
		{
			tmp = handle_redirs(&tmp);
			continue ;
		}
		tmp->type = ARGUMENT;
		tmp = tmp->next;
	}
	return (tmp);
}

void	assign_types(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		tmp->type = get_type(tmp->token);
		if (tmp->type == COMMAND || tmp->type == BUILTIN)
			tmp = handle_commands(&tmp);
		if (tmp->type == OUTPUT || tmp->type == INPUT
			|| tmp->type == APPEND || tmp->type == HERE_DOC)
			tmp = handle_redirs(&tmp);
		else if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			continue ;
		}
		else if (tmp->type == NEWL)
			break ;
		else
			tmp = tmp->next;
	}
}
