/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:26:10 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/02 17:06:43 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static t_tokens	*assign_as_arg(t_tokens	**tokens, int stat)
{
	t_tokens	*tmp;

	tmp = *tokens;
	if (!tmp)
		return (tmp);
	if (stat == 1)
		tmp->type = ARGUMENT;
	if (tmp->next)
		tmp = tmp->next;
	else
		return (tmp);
	if (tmp)
		tmp->type = get_type(tmp->token);
	while (tmp && !is_redir_pipe(tmp->type))
	{
		tmp->type = ARGUMENT;
		tmp = tmp->next;
		if (tmp)
			tmp->type = get_type(tmp->token);
	}
	return (tmp);
}

static t_tokens	*handle_redirs(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	if (tmp->type == HERE_DOC)
	{
		tmp = tmp->next;
		tmp->type = get_type(tmp->token);
		while (is_redir_pipe(tmp->type))
		{
			tmp = tmp->next;
			tmp->type = get_type(tmp->token);
		}
		tmp->type = LIMITER;
		return (tmp->next);
	}
	tmp = tmp->next;
	tmp->type = get_type(tmp->token);
	while (is_redir_pipe(tmp->type))
	{
		tmp = tmp->next;
		tmp->type = get_type(tmp->token);
	}
	tmp->type = FILE_NAME;
	return (tmp->next);
}

static t_tokens	*handle_redir_pipe(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	if (!(tmp->next))
		return (NULL);
	if (tmp->type == PIPE)
	{
		tmp = tmp->next;
		tmp->type = get_type(tmp->token);
	}
	else
		tmp = handle_redirs(&tmp);
	return (tmp);
}

void	assign_types(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		tmp->type = get_type(tmp->token);
		if (tmp->type == BUILTIN || tmp->type == COMMAND)
			tmp = assign_as_arg(&tmp, 0);
		if (!tmp)
			return ;
		else
		{
			tmp = handle_redir_pipe(&tmp);
			tmp = assign_as_arg(&tmp, 1);
		}
	}
}
