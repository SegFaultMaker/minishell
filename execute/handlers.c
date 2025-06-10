/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:23:18 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/10 12:39:16 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static pid_t	safe_execve(t_tokens *cmd, char *path, char **argv, char **envp)
{
	pid_t		pid;
	int			res;

	res = 0;
	pid = fork();
	if (pid == -1)
		return (quit_with_error(0, "fork", NULL, errno));
	if (pid == 0)
	{
		if (cmd->input != STDIN_FILENO)
		{
			dup2(cmd->input, STDIN_FILENO);
			close(cmd->input);
		}
		if (cmd->output != STDOUT_FILENO)
		{
			dup2(cmd->output, STDOUT_FILENO);
			close(cmd->output);
		}
		if (execve(path, argv, envp) == -1)
			quit_with_error(0, NULL, NULL, errno);
	}
	if (cmd->piped_out)
		close(cmd->output);
	return (pid);
}

static void	execute_functions(t_tokens *tokens, t_hash_table *envp,
				t_stat *stat_struct, int pipe_count)
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
		stat_struct->stat = exit_builtin(tokens->next, stat_struct, pipe_count);
}

void	handle_builtin(t_tokens *tokens, t_hash_table *envp,
			t_stat *stat_struct, int pipe_count)
{
	int			saved_in;
	int			saved_out;

	saved_in = INT_MIN;
	saved_out = INT_MIN;
	while (tokens->type != BUILTIN)
		tokens = tokens->next;
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
	execute_functions(tokens, envp, stat_struct, pipe_count);
	undo_builtin_redirs(saved_in, saved_out);
}

pid_t	handle_binary(t_tokens *cmd, t_hash_table *env, t_stat *stat_struct)
{
	char	**argv;
	char	**envp;
	char	*full_path;
	pid_t	pid;

	argv = tokens_to_strings(cmd);
	envp = ht_to_strings(env, 0);
	full_path = find_cmd(argv[0], envp);
	if (!argv || !envp)
	{
		stat_struct->stat = quit_with_error(1, "execution", "malloc error", 1);
		return (0);
	}
	if (!full_path)
	{
		free_matrix(argv);
		free_matrix(envp);
		stat_struct->stat = 127;
		return (0);
	}
	pid = safe_execve(cmd, full_path, argv, envp);
	free_matrix(argv);
	free_matrix(envp);
	if (full_path)
		free(full_path);
	return(pid);
}
