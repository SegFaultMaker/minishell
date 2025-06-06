/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens_redirs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:48:53 by armarake          #+#    #+#             */
/*   Updated: 2025/06/06 23:37:51 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	handle_input_redir(t_tokens **current, t_tokens **executable)
{
	(*executable)->input = open_infile((*current)->next->token);
	if ((*executable)->input == -1)
	{
		(*executable)->execute = false;
		while (1)
		{
			if ((*current)->type == PIPE)
				return (BREAK_REDIR_LOOP);
			if ((*current)->type == NEWL)
				return (RETURN_FROM_FUNCTION);
			(*current) = (*current)->next;
		}
		(*executable) = find_executable((*current)->next);
		(*current) = (*executable);
		return (CONTINUE_REDIR_LOOP);
	}
	return (0);
}

int	handle_output_redir(t_tokens **current, t_tokens **executable)
{
	(*executable)->output = open_outfile((*current)->next->token, (*current)->type);
	if ((*executable)->output == -1)
	{
		(*executable)->execute = false;
		while (1)
		{
			if ((*current)->type == PIPE)
				return (BREAK_REDIR_LOOP);
			if ((*current)->type == NEWL)
				return (RETURN_FROM_FUNCTION);
			(*current) = (*current)->next;
		}
		(*executable) = find_executable((*current)->next);
		(*current) = (*executable);
		return (CONTINUE_REDIR_LOOP);
	}
	return (0);
}

void	handle_pipe_redir
(t_tokens **current, t_tokens **executable, int **pipe_fds, int *i)
{
	if ((*executable)->output != STDOUT_FILENO)
		close(pipe_fds[(*i)][1]);
	else
	{
		(*executable)->output = pipe_fds[(*i)][1];
		(*executable)->piped_out = true;
	}
	(*current) = (*current)->next;
	(*executable) = find_executable((*current));
	(*executable)->input = pipe_fds[(*i)][0];
	(*executable)->piped_in = true;
	(*i)++;
}
