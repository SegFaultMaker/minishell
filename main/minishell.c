/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:09:12 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/09 14:24:25 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_shell(t_hash_table *environment, t_stat *stat_struct)
{
	t_tokens		*cmd;
	char			*input;
	int				check_status;
	struct termios	termios;

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
		handle_input(&cmd, environment, &input, stat_struct);
		tcsetattr(STDOUT_FILENO, 0, &termios);
		if (stat_struct->must_exit)
			return ;
	}
}

static	t_stat	*create_stat_struct(void)
{
	t_stat			*stat_struct;

	stat_struct = malloc(sizeof(t_stat));
	stat_struct->must_exit = false;
	stat_struct->stat = 0;
	return (stat_struct);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_hash_table	*environment;
	t_stat			*stat_struct;
	int				stat;

	init_signals();
	environment = init_environment(envp);
	stat_struct = create_stat_struct();
	start_shell(environment, stat_struct);
	del_hash_table(environment);
	rl_clear_history();
	(void)argc;
	(void)argv;
	stat = stat_struct->stat;
	free(stat_struct);
	printf("exit\n");
	return (stat);
}
