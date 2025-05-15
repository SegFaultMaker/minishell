/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:09:12 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/15 22:54:07 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(t_hash_table *environment)
{
	char	*dir;
	char	*login;
	char	*result;

	dir = ht_search(environment, "PWD");
	login = ht_search(environment, "LOGNAME");
	if (!dir || ! login)
		return (NULL);
	result = ft_strdup("");
	result = ft_strjoin(result, PURPLE);
	result = ft_strjoin(result, "→ ");
	result = ft_strjoin(result, RESET);
	result = ft_strjoin(result, login);
	result = ft_strjoin(result, " ");
	result = ft_strjoin(result, BLUE);
	result = ft_strjoin(result, dir);
	result = ft_strjoin(result, RESET);
	result = ft_strjoin(result, " $ ");
	return (result);
}

void	start_shell(t_hash_table *environment)
{
	t_tokens	*cmd;
	int			stat;
	char		*input;
	char		*prompt;

	cmd = NULL;
	input = NULL;
	stat = 0;
	while (!input || !*input)
	{
		prompt = get_prompt(environment);
		input = readline(prompt);
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
		free(prompt);
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
