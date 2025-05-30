/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:14:00 by armarake          #+#    #+#             */
/*   Updated: 2025/05/29 13:29:15 by nasargsy         ###   ########.fr       */
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

int	handle_input(t_tokens **cmd, t_hash_table *envp, char **input, int stat)
{
	if (*cmd)
	{
		stat = execute(*cmd, envp, stat);
		if (stat == -1)
		{
			free_values(cmd, input);
			return (INT_MIN);
		}
	}
	else
		stat = 2;
	free_values(cmd, input);
	return (stat);
}
