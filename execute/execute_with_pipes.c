/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:58:01 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/29 15:04:02 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	handle_binary(char **argv, char **envp)
{
	char	*path;
	pid_t	pid;

	path = find_cmd(argv[0], envp);
	if (!argv || !envp)
		return (quit_with_error(1, "execution", "malloc error", 1));
	if (!path)
	{
		free_matrix(argv);
		free_matrix(envp);
		return (127);
	}
	pid = fork();
	if (pid == -1)
		return (quit_with_error(0, "fork", NULL, errno));
	if (pid == 0)
	{
		if (do_redir(tmp, &saved_in, &saved_out) != 0)
			return (errno);
		if (execve(path, argv, envp) == -1)
			return (quit_with_error(0, NULL, NULL, errno));
	}
	free(path);
	return (0);
}

int	execute_with_pipes(t_tokens *tokens, t_hash_table *envp)
{
	char	***argv_container;
	char	**envp_strings;
	int		stat;
	int		i;

	i = get_commands(tokens);
	argv_container = get_argvs(tokens, i);
	envp_strings = ht_to_strings(envp, 0);
	stat = 0;
	i = 0;
	while (tokens)
	{
		while (tokens && tokens->type != BUILTIN && tokens->type != COMMAND)
			tokens = tokens->next;
		if (tokens->type == COMMAND)
		{
			stat = handle_binary(argv_container[i], envp_strings);
			i++;
		}
		else
			stat = handle_builtin(tokens);
	}
}
