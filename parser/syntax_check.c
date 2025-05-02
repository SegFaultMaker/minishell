/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:13:41 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/02 17:01:27 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_type_num(t_types type)
{
	if (type == PIPE)
		return (3);
	else if (type == INPUT)
		return (4);
	else if (type == OUTPUT)
		return (5);
	return (0);
}

int	syntax_check(t_tokens *tmp)
{
	if (tmp->type == PIPE)
		return (0);
	while (tmp)
	{
		if (is_redir_pipe(tmp->type))
		{
			if (!tmp->next)
				return (0);
			if (tmp->type == tmp->next->type)
				return (get_type_num(tmp->type));
		}
		tmp = tmp->next;
	}
	return (1);
}
