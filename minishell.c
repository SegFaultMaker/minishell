/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:09:12 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/26 16:16:34 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_input(void)
{
	char	*input;

	input = readline(BLUE "→  " RESET);
	if (input && *input)
		add_history(input);
	add_history(input);
	return (input);
}

static int	only_spaces(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (input[i] != ' ')
			return (0);
	return (1);
}

static int	check_input(char **input)
{
	if (!*input)
		return (BREAK_LOOP);
	else if (!**input || only_spaces(*input))
	{
		free(*input);
		*input = NULL;
		return (CONTINUE_LOOP);
	}
	return (0);
}

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
		if (cmd)
			stat = execute(cmd, environment, stat);
		else
			stat = errno;
		free(input);
		free_tokens(&cmd);
		input = NULL;
	}
	if (input)
		free(input);
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
