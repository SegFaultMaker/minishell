/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:09:12 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/30 14:15:00 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tokens(t_tokens *tokens)   //FOR DEBUG ONLY
{
	int	i = 1;
	t_tokens	*tmp = tokens;
	if (!tmp)
		printf("No Tokens\n");
	else
	{
		while (tmp)
		{
			printf("Token %d: %s\n", i, tmp->token);
			i++;
			tmp = tmp->next;
		}
		free_tokens(&tokens);
	}
}

static int handle_input(char *str)
{
	t_tokens	*tokens;

	tokens = parser(str);
	if (!tokens)
		return (0);
	print_tokens(tokens);		// REMOVE AFTER DEBUG
	if (!syntax_check(tokens))
		return (0);
	if (!execute(tokens))
		return (0);
	return (1);
}

static void	start_shell(void)
{
	char	*input;

	input = readline(PROMPT);
	while (input)
	{
		add_history(input);
		if (!handle_input(input))
		{
			free(input);
			break ;
		}
		free(input);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_signals();
	start_shell();
}
