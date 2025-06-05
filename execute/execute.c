/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:21:29 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/05 16:53:24 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void do_redirections(t_tokens **tokens, int **pipe_fds)
{
	t_tokens	*tmp;
	t_tokens	*cmd;
	t_tokens	*start;
	
	int i;

	tmp = *tokens;
	i = 0;
	cmd = NULL;
	while (tmp->type != NEWL)
	{
		if (!cmd)
		{
			start = tmp;
			while (tmp->type != PIPE && (tmp->type != COMMAND && tmp->type != BUILTIN))
				tmp = tmp->next;
			cmd = tmp;
			tmp = start;
		}
		if (tmp->type == OUTPUT || tmp->type == APPEND)
		{
			if (cmd->output != STDOUT_FILENO)
				close(cmd->output);
			cmd->output = open_outfile(tmp->next->token, tmp->type);
		}
		else if (tmp->type == INPUT)
		{
			if (cmd->input != STDIN_FILENO)
				close(cmd->input);
			cmd->input = open_infile(tmp->next->token);
		}
		else if (tmp->type == PIPE)
		{
			if (cmd->input != STDIN_FILENO)
				dup2(pipe_fds[i][0], cmd->input);
			if (cmd->output != STDOUT_FILENO)
				dup2(pipe_fds[i][1], cmd->output);
			close(pipe_fds[i][0]);
			close(pipe_fds[i][1]);
			i++;
			tmp = tmp->next;
			cmd = NULL;
			continue ;
		}
		else if (tmp->type == HERE_DOC)
			here_doc(tmp, cmd->input);
		tmp = tmp->next;
	}
}

void free_pipes(int **array)
{
	int i;

	i = 0;
	if (!array || !*array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int **allocate_pipe_fds(int pipe_count)
{
	int i;
	int **result;

	i = 0;
	result = malloc(sizeof(int *) * (pipe_count + 1));
	if (!result)
		return (NULL);
	while (i < pipe_count)
	{
		result[i] = malloc(sizeof(int) * 2);
		if (!result)
			return (free_pipes(result), NULL);
		if (pipe(result[i]))
			return (free_pipes(result), NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	execute_all(t_tokens *tokens, t_hash_table *env)
{
	int	stat;

	stat = 0;
	while (tokens)
	{
		if (define_type(tokens) == COMMAND)
			stat = handle_binary(tokens, env);
		else if (define_type(tokens) == BUILTIN)
			stat = handle_builtin(tokens, env);
		tokens = tokens->next;
	}
	return (stat);
}

int execute(t_tokens *tokens, t_hash_table *env, int stat)
{
	int **pipe_fds;
	int pipe_count;

	expand_tokens(&tokens, env, stat);
	pipe_count = check_pipes(tokens);
	pipe_fds = allocate_pipe_fds(pipe_count);
	if (!pipe_fds)
		return (quit_with_error(1, "pipes", "pipe allocation error", 1));
	do_redirections(&tokens, pipe_fds);
	stat = execute_all(tokens, env);
	free_pipes(pipe_fds);
	return (stat);
}
