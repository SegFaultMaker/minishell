/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_no_pipes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:23:18 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/16 17:39:51 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	safe_execve(char *full_path, char **argv, char **envp)
{
	pid_t	pid;
	int		res;

	res = 0;
	pid = fork();
	if (pid == -1)
		return (quit_with_error(0, "fork", errno));
	if (pid == 0)
	{
		if (execve(full_path, argv, envp) == -1)
			quit_with_error(0, NULL, errno);
	}
	wait(&res);
	return (res);
}

static int	handle_builtin(t_tokens *tokens, t_hash_table *envp)
{
	int			stat;
	int			saved_in;
	int			saved_out;
	t_tokens	*temp;

	saved_in = INT_MIN;
	saved_out = INT_MIN;
	stat = 0;
	temp = tokens;
	if (do_redir(temp, &saved_in, &saved_out) != 0)
		return (errno);
	while (tokens->type != BUILTIN)
		tokens = tokens->next;
	if (!ft_strcmp(tokens->token, "cd"))
		stat = cd(tokens->next, envp);
	else if (!ft_strcmp(tokens->token, "pwd"))
		stat = pwd();
	else if (!ft_strcmp(tokens->token, "echo"))
		stat = echo(tokens->next);
	else if (!ft_strcmp(tokens->token, "env"))
		stat = env(envp, 0);
	else if (!ft_strcmp(tokens->token, "export"))
		stat = export(tokens->next, envp);
	else if (!ft_strcmp(tokens->token, "unset"))
		stat = unset(tokens->next, envp);
	undo_redir(saved_in, saved_out);
	return (stat);
}

static int	handle_binary(t_tokens *cmd, t_hash_table *env)
{
	char	**argv;
	char	**envp;
	char	*full_path;
	int		res;

	argv = tokens_to_strings(cmd);
	envp = ht_to_strings(env, 0);
	full_path = find_cmd(argv[0], envp);
	if (!argv || !envp)
		return (1);
	if (!full_path)
		return (errno);
	res = safe_execve(full_path, argv, envp);
	if (full_path)
		free(full_path);
	free_matrix(argv);
	free_matrix(envp);
	return (res);
}

int	execute_command_no_pipes(t_tokens *tokens, t_hash_table *env)
{
	if (define_type(tokens) == BUILTIN)
		return (handle_builtin(tokens, env));
	return (handle_binary(tokens, env));
}

