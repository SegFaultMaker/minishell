/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:09:12 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/09 13:25:59 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	start_shell(t_hash_table *environment, int stat)
{
	t_tokens		*cmd;
	char			*input;
	int				check_status;
	struct termios	termios;
	bool			must_exit;

	must_exit = false;
	input = NULL;
	while (1)
	{
		tcgetattr(STDOUT_FILENO, &termios);
		input = read_input();
		check_status = check_input(&input);
		if (check_status == BREAK_LOOP)
			break ;
		else if (check_status == CONTINUE_LOOP)
			continue ;
		cmd = parser(input);
		stat = handle_input(&cmd, environment, &input, &must_exit);
		tcsetattr(STDOUT_FILENO, 0, &termios);
		if (must_exit)
			return (stat);
	}
	return (stat);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_hash_table	*environment;
	int				stat;

	stat = 0;
	init_signals();
	environment = init_environment(envp);
	stat = start_shell(environment, stat);
	del_hash_table(environment);
	rl_clear_history();
	(void)argc;
	(void)argv;
	printf("exit\n");
	return (stat);
}
