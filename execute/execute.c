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

t_tokens	*find_executable(t_tokens *current)
{
	t_tokens	*tmp;

	tmp = current;
	while (tmp->type != NEWL && tmp->type != PIPE)
	{
		if (tmp->type == COMMAND || tmp->type == BUILTIN)
			return (tmp);
	}
	return (NULL);
}

void	do_redirections(t_tokens **tokens, int **pipe_fds)
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
			executable->input = open_infile(current->next->token);
			if (executable->input == -1)
			{
				executable->execute = false;
				while (1)
				{
					if (current->type == PIPE)
						break ;
					if (current->type == NEWL)
						return ;
					current = current->next;
				}
				executable = find_executable(current->next);
				current = executable;
				continue ;
			}
		}
		else if (current->type == OUTPUT || current->type == APPEND)
		{
			executable->output = open_outfile(current->next->token, current->type);
			if (executable->output == -1)
			{
				executable->execute = false;
				while (1)
				{
					if (current->type == PIPE)
						break ;
					if (current->type == NEWL)
						return ;
					current = current->next;
				}
				executable = find_executable(current->next);
				current = executable;
				continue ;
			}
			
		}
		else if (current->type == PIPE)
		{
			if (executable->output != STDIN_FILENO)
				close(pipe_fds[i][1]);
			else
			{
				executable->output = pipe_fds[i][1];
				executable->piped_out = true;
			}
			current = current->next;
			executable = find_executable(current);
			executable->input = pipe_fds[i][0];
			executable->piped_in = true;
			i++;
			continue ;
		}
		current = current->next;
	}
}

void	free_pipes(int ***array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return ;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
}

int	**allocate_pipe_fds(int pipe_count)
{
	int	i;
	int	**result;

	i = 0;
	result = malloc(sizeof(int *) * (pipe_count + 1));
	if (!result)
		return (NULL);
	while (i < pipe_count)
	{
		result[i] = malloc(sizeof(int) * 2);
		if (!result)
			return (free_pipes(&result), NULL);
		if (pipe(result[i]))
			return (free_pipes(&result), NULL);
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
		if (tokens->type == COMMAND && tokens->execute)
			stat = handle_binary(tokens, env);
		else if (tokens->type == BUILTIN && tokens->execute)
			stat = handle_builtin(tokens, env);
		tokens = tokens->next;
	}
	return (stat);
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
	stat = execute_all(tokens, env);
	free_pipes(&pipe_fds);
	return (stat);
}
