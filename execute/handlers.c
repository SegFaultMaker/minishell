/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:23:18 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/17 16:01:20 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static pid_t	safe_execve(t_tokens *tokens, t_stat *stat_struct)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		return (quit_with_error(0, "fork", NULL, errno));
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		dup_and_close(tokens, stat_struct);
		if (execve(stat_struct->path, stat_struct->argv, stat_struct->envp))
			quit_with_error(0, NULL, NULL, errno);
	}
	if (tokens->input != STDIN_FILENO)
		close(tokens->input);
	if (tokens->output != STDOUT_FILENO)
		close(tokens->output);
	return (pid);
}

static void	execute_functions(t_tokens *tokens, t_hash_table *envp,
	t_stat *stat_struct, bool in_fork)
{
	if (!ft_strcmp(tokens->token, "cd"))
		stat_struct->stat = cd(tokens->next, envp);
	else if (!ft_strcmp(tokens->token, "pwd"))
		stat_struct->stat = pwd(envp);
	else if (!ft_strcmp(tokens->token, "echo"))
		stat_struct->stat = echo(tokens->next);
	else if (!ft_strcmp(tokens->token, "env"))
		stat_struct->stat = env(envp, 0);
	else if (!ft_strcmp(tokens->token, "export"))
		stat_struct->stat = export(tokens->next, envp);
	else if (!ft_strcmp(tokens->token, "unset"))
		stat_struct->stat = unset(tokens->next, envp);
	else if (!ft_strcmp(tokens->token, "exit"))
		stat_struct->stat = exit_builtin(tokens->next, stat_struct, in_fork);
}

pid_t	builtin_in_fork(t_tokens *tokens, t_hash_table *envp,
	t_stat *stat_struct)
{
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		return (quit_with_error(0, "fork", NULL, errno));
	if (pid == 0)
	{
		dup_and_close(tokens, stat_struct);
		execute_functions(tokens, envp, stat_struct, true);
		exit(stat_struct->stat);
	}
	if (tokens->input != STDIN_FILENO)
		close(tokens->input);
	if (tokens->output != STDOUT_FILENO)
		close(tokens->output);
	return (pid);
}

void	handle_builtin(t_tokens *tokens, t_hash_table *envp,
			t_stat *stat_struct)
{
	int			saved_in;
	int			saved_out;

	saved_in = INT_MIN;
	saved_out = INT_MIN;
	if (tokens->input != STDIN_FILENO)
	{
		saved_in = dup(STDIN_FILENO);
		dup2(tokens->input, STDIN_FILENO);
		close(tokens->input);
	}
	if (tokens->output != STDOUT_FILENO)
	{
		saved_out = dup(STDOUT_FILENO);
		dup2(tokens->output, STDOUT_FILENO);
		close(tokens->output);
	}
	execute_functions(tokens, envp, stat_struct, false);
	undo_builtin_redirs(saved_in, saved_out);
}

pid_t	handle_binary(t_tokens *cmd, t_hash_table *env, t_stat *stat)
{
	pid_t	pid;

	stat->argv = tokens_to_strings(cmd);
	stat->envp = ht_to_strings(env, 0);
	stat->path = find_cmd(stat->argv[0], stat->envp);
	if (!stat->argv || !stat->envp)
	{
		stat->stat = quit_with_error(1, "execution", "malloc error", 1);
		return (-1);
	}
	if (!stat->path)
	{
		if (cmd->output != STDOUT_FILENO)
			close(cmd->output);
		stat->stat = 127;
		free_matrix(stat->argv);
		free_result(stat->envp);
		return (stat->argv = NULL, stat->envp = NULL, -1);
	}
	pid = safe_execve(cmd, stat);
	free_matrix(stat->argv);
	free_matrix(stat->envp);
	if (stat->path)
		free(stat->path);
	return (stat->argv = NULL, stat->envp = NULL, stat->path = NULL, pid);
}
