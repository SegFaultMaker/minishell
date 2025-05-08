/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:13:41 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/08 13:59:26 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	generate_error(t_tokens *tmp)
{
	ft_putstr_fd(SYNTAX_ERR, 2);
	ft_putchar_fd('`', 2);
	if (tmp->next->type == NEWL)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(tmp->next->token, 2);
	ft_putstr_fd("\'\n", 2);
}

int	syntax_check(t_tokens *tmp)
{
	if (tmp->type == PIPE
		|| tmp->type == OPERATOR)
	{
		generate_error(tmp);
		return (0);
	}
	while (tmp)
	{
		if (is_redir_pipe(tmp->type) || tmp->type == OPERATOR)
		{
			if (is_redir_pipe(tmp->next->type))
			{
				if (is_redir_pipe(tmp->next->next->type))
					generate_error(tmp->next);
				else
					generate_error(tmp);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
