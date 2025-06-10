/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:14:00 by armarake          #+#    #+#             */
/*   Updated: 2025/06/10 22:40:42 by nasargsy         ###   ########.fr       */
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

void	handle_input(t_tokens **cmd, t_hash_table *envp,
			char **input, t_stat *stat_struct)
{
	if (*cmd)
	{
		execute(*cmd, envp, stat_struct);
		if (stat_struct->must_exit)
		{
			free_values(cmd, input);
			return ;
		}
	}
	else
		stat_struct->stat = 2;
	free_values(cmd, input);
}
