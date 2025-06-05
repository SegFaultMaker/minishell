/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:09:12 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/05 17:56:46 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_shell(t_hash_table *environment)
{
	t_tokens	*cmd;
	int			stat;
	char		*input;
	int			check_status;

	stat = 0;
	input = NULL;
	while (1)
	{
		input = read_input();
		check_status = check_input(&input);
		if (check_status == BREAK_LOOP)
			break ;
		else if (check_status == CONTINUE_LOOP)
			continue ;
		cmd = parser(input);
		stat = handle_input(&cmd, environment, &input, stat);
		if (stat == INT_MIN)
			return ;
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
