/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:42:15 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/30 18:00:25 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*static void	handle_pipe(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	if (tmp->next)
	{
		tmp = tmp->next;
		tmp->type = COMMAND;
	}
	tmp = tmp->next;
}*/

/*static void	handle_redir(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	if (tmp->type == HERE_DOC)
	{
		if (tmp->next)
		{
			tmp = tmp->next;
			tmp->type = ARGUMENT;
		}
	}
	else
	{
		if (tmp->next)
		{
			tmp = tmp->next;
			tmp->type = FILE_NAME;
		}
	}
	tmp = tmp->next;
}*/

t_tokens	*handle_redir_pipe(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	if (!(tmp->next))
		return (NULL);
	if (tmp->type == PIPE)
	{
		tmp = tmp->next;
		tmp->type = COMMAND;
	}
	else
	{
		tmp = tmp->next;
		if (tmp->type == HERE_DOC)
			tmp->type = ARGUMENT;
		else
			tmp->type = FILE_NAME;
	}
	return (tmp);
}
