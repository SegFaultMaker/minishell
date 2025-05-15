/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_no_pipes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:23:18 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/15 16:17:24 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	open_outfile(char *filename, int mode)
{
	if (access(filename, F_OK) != 0)
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (access(filename, W_OK) != 0)
		return (quit_with_error("permission denied", -1));
	if (!access(filename, F_OK) && mode == APPEND)
		return (open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (open(filename, O_WRONLY | O_TRUNC));
}

static int	do_redir(t_tokens *tokens, int *saved_fd)
{
	int	outfile;

	while (tokens)
	{
		if (tokens->type == OUTPUT || tokens->type == APPEND)
		{
			outfile = open_outfile(tokens->next->token, tokens->type);
			if (outfile == -1)
				return (outfile);
			*saved_fd = dup(STDOUT_FILENO);
			dup2(outfile, STDOUT_FILENO);
			close(outfile);
			break ;
		}
		tokens = tokens->next;
	}
	return (0);
}

static int	handle_builtin(t_tokens *tokens, t_hash_table *envp)
{
	int			stat;
	int			saved_fd;

	saved_fd = INT_MIN;
	if (do_redir(tokens, &saved_fd))
		return (-1);
	while (tokens->type != BUILTIN)
		tokens = tokens->next;
	if (!ft_strcmp(tokens->token, "cd"))
		stat = cd(tokens->next->token);
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
	if (saved_fd != INT_MIN)
	{
		dup2(saved_fd, STDOUT_FILENO);
		close(saved_fd);
	}
	return (stat);
}

/*static int	handle_binary(t_tokens *cmd, t_hash_table *env)
{
	char	**argv;
	char	**envp;
	char	*full_path;
	pid_t	pid;

	argv = tokens_to_strings(cmd);
	envp = ht_to_strings(env, 0);
	if (!argv)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("minishell: fork: Cannot allocate memory\n", STDERR_FILENO);
		return (-1);
	}
	if (pid == 0)
	{
		if ()
		if (execve(argv[0], argv, envp))
		{
			
		}
	}
	else
		wait(&stat);

}*/

int	execute_command_no_pipes(t_tokens *tokens, t_hash_table *env)
{
	int		stat;

	stat = 0;
	if (define_type(tokens) == BUILTIN)
		return (handle_builtin(tokens, env));
	/*else
		stat = handle_binary(cmd, env);*/
	return (stat);
}

