/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_no_pipes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:23:18 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/12 17:28:34 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	handle_builtin(t_tokens *cmd, t_hash_table *env)
{

}

static int	handle_binary(t_tokens *cmd, t_hash_table *env)
{
	char	*argv[];
	char	*envp[];
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

}

int	execute_command_no_pipes(t_tokens *cmd, t_hash_table *env)
{
	int		stat;

	if (cmd->type == BUILTIN)
		stat = handle_builtin(cmd, env);
	else
		stat = handle_binary(cmd, env);
	return (stat);
}

