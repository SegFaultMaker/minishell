/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:05:41 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/08 12:25:24 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_arg(t_tokens *tokens)
{
	while (tokens && !is_redir_pipe(tokens->type))
	{
		if (!ft_strcmp(tokens->token, "-n"))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	echo(t_tokens *tokens)
{
	if (!tokens || tokens->type != ARGUMENT)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	if (check_arg(tokens))
	{
		while (tokens && !is_redir_pipe(tokens->type))
		{
			ft_putstr_fd(tokens->token, 1);
			ft_putchar_fd(' ', 1);
			tokens = tokens->next;
		}
	}
	else
	{
		while (tokens && !is_redir_pipe(tokens->type))
		{
			ft_putstr_fd(tokens->token, 1);
			ft_putchar_fd(' ', 1);
			tokens = tokens->next;
		}
		ft_putchar_fd('\n', 1);
	}
	return (0);
}
