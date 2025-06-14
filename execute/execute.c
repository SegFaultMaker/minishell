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
	while (current && current->type != NEWL)
	{
		if (current->type == INPUT)
		{
			if (handle_input_redir(&current, &executable) == CONTINUE_THE_LOOP)
				continue ;
		}
		else if ((current->type == OUTPUT) || (current->type == APPEND))
		{
			if (handle_output_redir(&current, &executable) == CONTINUE_THE_LOOP)
				continue ;
		}
		else if (current->type == PIPE)
			handle_pipe_redir(&current, &executable, pipe_fds, &i);
		current = current->next;
	}
}

static void	execute_all(t_tokens *tokens, t_hash_table *env,
			t_stat *stat_struct)
{
	while (tokens)
	{
		if (tokens->type == COMMAND && tokens->execute)
		{
			stat_struct->pid = handle_binary(tokens, env, stat_struct);
			stat_struct->last_in_fork = true;
		}
		else if (tokens->type == BUILTIN && tokens->execute)
		{
			if (stat_struct->pipe_count > 0)
			{
				stat_struct->pid = builtin_in_fork(tokens, env, stat_struct);
				stat_struct->last_in_fork = false;
			}
			else
				handle_builtin(tokens, env, stat_struct);
		}
		tokens = tokens->next;
	}
}

void	execute(t_tokens *tokens, t_hash_table *env, t_stat *stat_struct)
{
	expand_tokens(&tokens, env, stat_struct->stat);
	stat_struct->pipe_count = check_pipes(tokens);
	stat_struct->pipe_fds = allocate_pipe_fds(stat_struct->pipe_count);
	if (!stat_struct->pipe_fds)
	{
		stat_struct->stat = quit_with_error(1, "pipes",
				"pipe allocation error", 1);
		return ;
	}
	do_redirections(&tokens, stat_struct->pipe_fds);
	execute_all(tokens, env, stat_struct);
	free_pipes(&stat_struct->pipe_fds);
	if (stat_struct->pipe_count > 0)
		stat_struct->last_in_fork = true;
	stat_struct->stat = get_last_stat(stat_struct);
}
