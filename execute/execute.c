/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 execute.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: armarake <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/05/12 15:21:29 by nasargsy		   #+#	  #+#			  */
/*	 Updated: 2025/06/06 16:06:15 by nasargsy		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "execute.h"

static void	do_redirections(t_tokens **tokens, int **pipe_fds)
{
	t_tokens	*current;
	t_tokens	*executable;
	int			i;

	i = 0;
	current = *tokens;
	executable = find_executable(current);
	while (current->type != NEWL)
	{
		if (current->type == INPUT)
		{
			if (handle_input_redir(&current, &executable) == CONTINUE_REDIR_LOOP)
				continue ;
		}
		else if ((current->type == OUTPUT) || (current->type == APPEND))
		{
			if (handle_output_redir(&current, &executable) == CONTINUE_REDIR_LOOP)
				continue ;
		}
		else if (current->type == PIPE)
			handle_pipe_redir(&current, &executable, pipe_fds, &i);
		current = current->next;
	}
}

int	execute(t_tokens *tokens, t_hash_table *env, int stat)
{
	int	**pipe_fds;
	int	pipe_count;

	expand_tokens(&tokens, env, stat);
	pipe_count = check_pipes(tokens);
	pipe_fds = allocate_pipe_fds(pipe_count);
	if (!pipe_fds)
		return (quit_with_error(1, "pipes", "pipe allocation error", 1));
	do_redirections(&tokens, pipe_fds);
	stat = 0;
	while (tokens)
	{
		if (tokens->type == COMMAND && tokens->execute)
			stat = handle_binary(tokens, env);
		else if (tokens->type == BUILTIN && tokens->execute)
			stat = handle_builtin(tokens, env);
		tokens = tokens->next;
	}
	free_pipes(&pipe_fds);
	return (stat);
}
