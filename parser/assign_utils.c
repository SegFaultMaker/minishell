/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:29:51 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/05 13:48:06 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tokens	*handle_first(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	tmp->type = get_type(tmp->token);
	if (!(tmp->next))
		return (tmp);
	if (tmp->type == INPUT || tmp->type == OUTPUT
		|| tmp->type == APPEND)
	{
		tmp->next->type = FILE_NAME;
		tmp = tmp->next->next;
	}
	else if (tmp->type == HERE_DOC)
	{
		tmp->next->type = LIMITER;
		tmp = tmp->next->next;
	}
	else if (tmp->type == PIPE)
		tmp = tmp->next;
	return (tmp);
}
