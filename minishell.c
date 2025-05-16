/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:09:12 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/16 16:50:37 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_shell(t_hash_table *environment)
{
	t_tokens	*cmd;
	int			stat;
	char		*input;

	cmd = NULL;
	input = NULL;
	stat = 0;
	while (!input || !*input)
	{
		input = readline(BLUE "→  " RESET);
		add_history(input);
		if (!input)
			break ;
		else if (!*input)
		{
			free(input);
			input = NULL;
			continue ;
		}
		cmd = parser(input);
		if (cmd)
			stat = execute(cmd, environment, stat);
		free(input);
		free_tokens(&cmd);
		input = NULL;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_hash_table	*environment;

	init_signals();
	environment = init_environment(envp);
	start_shell(environment);
	del_hash_table(environment);
	rl_clear_history();
	(void)argc;
	(void)argv;
}
