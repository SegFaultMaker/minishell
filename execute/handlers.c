/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:23:18 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/05 19:10:22 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	safe_execve(t_tokens *cmd, char *path, char **argv, char **envp)
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
	wait(&res);
	return (res);
}

static void	execute_functions(t_tokens *tokens, t_hash_table *envp, int *stat)
{
	if (!ft_strcmp(tokens->token, "cd"))
		*stat = cd(tokens->next, envp);
	else if (!ft_strcmp(tokens->token, "pwd"))
		*stat = pwd(envp);
	else if (!ft_strcmp(tokens->token, "echo"))
		*stat = echo(tokens->next);
	else if (!ft_strcmp(tokens->token, "env"))
		*stat = env(envp, 0);
	else if (!ft_strcmp(tokens->token, "export"))
		*stat = export(tokens->next, envp);
	else if (!ft_strcmp(tokens->token, "unset"))
		*stat = unset(tokens->next, envp);
	else if (!ft_strcmp(tokens->token, "exit"))
		*stat = -1;
}

int	handle_builtin(t_tokens *tokens, t_hash_table *envp)
{
	int			stat;
	t_tokens	*temp;

	stat = 0;
	temp = tokens;
	while (tokens->type != BUILTIN)
		tokens = tokens->next;
	execute_functions(tokens, envp, &stat);
	return (stat);
}

int	handle_binary(t_tokens *cmd, t_hash_table *env)
{
	char	**argv;
	char	**envp;
	char	*full_path;
	int		res;

	argv = tokens_to_strings(cmd);
	envp = ht_to_strings(env, 0);
	full_path = find_cmd(argv[0], envp);
	if (!argv || !envp)
		return (quit_with_error(1, "execution", "malloc error", 1));
	if (!full_path)
	{
		free_matrix(argv);
		free_matrix(envp);
		return (127);
	}
	res = safe_execve(cmd, full_path, argv, envp);
	free_matrix(argv);
	free_matrix(envp);
	if (full_path)
		free(full_path);
	return (res);
}