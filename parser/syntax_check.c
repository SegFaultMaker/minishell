/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:13:41 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/03 14:57:26 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	generate_error(t_tokens *tmp)
{
	ft_putstr_fd(SYNTAX_ERR, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(tmp->token, 2);
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
			if (!tmp->next)
			{
				generate_error(tmp);
				return (0);
			}
			if (tmp->type == tmp->next->type)
			{
				generate_error(tmp);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
