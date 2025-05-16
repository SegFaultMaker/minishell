/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:54:48 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/16 12:58:16 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_arg(t_tokens *tokens)
{
	char	*tmp;

	tmp = tokens->token;
	tmp++;
	while (*tmp && *tmp == 'n')
		tmp++;
	if (tmp)
		return (0);
	return (1);
}

int	echo(t_tokens *tokens)
{
	int	nl;

	nl = 1;
	if (!tokens || tokens->type != ARGUMENT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	if (*(tokens->token) == '-' && check_arg(tokens))
	{
		nl = 0;
		tokens = tokens->next;
	}
	while (tokens && !is_redir_pipe(tokens->type) && tokens->type != NEWL)
	{
		ft_putstr_fd(tokens->token, STDOUT_FILENO);
		if (tokens->next && tokens->next->type == ARGUMENT)
			ft_putchar_fd(' ', STDOUT_FILENO);
		tokens = tokens->next;
	}
	if (nl == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

/*int	main()
 {
 	char	*line;
 	line = readline("$ ");
 	t_tokens	*tokens = parser(line);
 	echo(tokens->next);
 	free(line);
 	free_tokens(&tokens);
 }*/
