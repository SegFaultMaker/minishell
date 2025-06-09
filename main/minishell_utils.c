/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:14:00 by armarake          #+#    #+#             */
/*   Updated: 2025/06/09 13:22:46 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_input(void)
{
	char	*input;

	input = readline(BLUE "→  " RESET);
	if (input && *input)
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

int	check_input(char **input)
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

static void	free_values(t_tokens **cmd, char **input)
{
	free(*input);
	free_tokens(cmd);
	input = NULL;
}

int	handle_input(t_tokens **cmd, t_hash_table *envp, char **input, bool *must_exit)
{
	int	stat;

	stat = 0;
	if (*cmd)
	{
		stat = execute(*cmd, envp, stat, must_exit);
		if (must_exit)
		{
			free_values(cmd, input);
			return (stat);
		}
	}
	else
		stat = 2;
	free_values(cmd, input);
	return (stat);
}
