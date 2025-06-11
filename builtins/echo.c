/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:54:48 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/11 17:38:22 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_arg(t_tokens *tokens)
{
	t_tokens	*tmp;
	char		*arg;

	tmp = tokens;
	while (tmp->type != NEWL && tmp->type != ARGUMENT)
		tmp = tmp->next;
	if (*(tmp->token) != '-')
		return (1);
	arg = tmp->token;
	arg++;
	while (*arg && *arg == 'n')
		arg++;
	if (!*arg)
	{
		free(tmp->token);
		tmp->token = NULL;
		return (0);
	}
	return (1);
}

int	echo(t_tokens *tokens)
{
	int	nl;

	nl = check_arg(tokens);
	while (tokens->type != PIPE && tokens->type != NEWL)
	{
		if (tokens->type == ARGUMENT && tokens->token)
		{
			ft_putstr_fd(tokens->token, STDOUT_FILENO);
			if (tokens->next && tokens->next->type != NEWL
				&& tokens->next->type != PIPE)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		tokens = tokens->next;
	}
	if (nl == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
