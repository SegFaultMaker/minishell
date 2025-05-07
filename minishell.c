/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:09:12 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/07 13:42:53 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_shell(void)
{
	t_tokens	*cmd;
	char		*input;

	cmd = NULL;
	input = NULL;
	while (!input || !*input)
	{
		input = readline("minishell $ ");
		if (!input)
			break ;
		else if (!*input)
		{
			free(input);
			input = NULL;
			continue ;
		}
		cmd = parser(input);
	/*	if (cmds)
			execute(cmds); */
		free(input);
		free_tokens(&cmd);
		input = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	init_signals();
	start_shell();
}
