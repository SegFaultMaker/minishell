/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_no_pipes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:23:18 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/13 16:47:48 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// < input echo "hello world" > output

static int	handle_builtin(t_tokens *tokens, t_hash_table *envp)
{
	int			stat;
	int			saved_fd;
	t_tokens	*tmp;
	t_tokens	*tmp2;

	tmp = tokens;
	tmp2 = tokens;
	if (stat)
		return (stat);
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

