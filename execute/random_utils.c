/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:29:49 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/26 13:37:45 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	check_dir(char *cmd)
{
	struct stat	s;

	if (stat(cmd, &s) == 0)
	{
		if (s.st_mode & S_IFDIR)
			return (quit_with_error(1, cmd, "Is a directory", 126));
	}
	return (0);
}

int	input_redir_checks(t_tokens **current, t_tokens **executable,
	t_hash_table *env, t_stat *stat)
{
	if ((*executable)->type == NEWL && (*current)->type != HERE_DOC)
	{
		open_infile((*current)->next->token);
		(*current) = (*executable);
		return (1);
	}
	if ((*executable)->type == PIPE)
	{
		(*current) = (*executable);
		(*executable) = NULL;
		return (1);
	}
	if ((*current)->type == HERE_DOC)
		return (here_doc(current, executable, env, stat), 0);
	return (2);
}

void	undo_builtin_redirs(int saved_in, int saved_out)
{
	if (saved_in != INT_MIN)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	if (saved_out != INT_MIN)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
}

int	get_last_stat(t_stat *stat_struct)
{
	int	res;
	int	count;

	res = stat_struct->stat;
	count = stat_struct->pipe_count;
	if (stat_struct->last_in_fork && stat_struct->pid)
		waitpid(stat_struct->pid, &res, 0);
	while (count)
	{
		wait(NULL);
		count--;
	}
	if (res >= 256)
		res /= 256;
	if (res == SIGPIPE)
		res = 1;
	return (res);
}

void	dup_and_close(t_tokens *tokens, t_stat *stat_struct)
{
	int	i;

	if (tokens->input != STDIN_FILENO)
	{
		dup2(tokens->input, STDIN_FILENO);
		close(tokens->input);
	}
	if (tokens->output != STDOUT_FILENO)
	{
		dup2(tokens->output, STDOUT_FILENO);
		close(tokens->output);
	}
	i = 0;
	while (stat_struct->pipe_fds[i])
	{
		if (stat_struct->pipe_fds[i][0] != tokens->input)
			close(stat_struct->pipe_fds[i][0]);
		if (stat_struct->pipe_fds[i][1] != tokens->output)
			close(stat_struct->pipe_fds[i][1]);
		i++;
	}
}
