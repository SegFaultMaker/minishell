/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:29:49 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/12 15:40:28 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redir_pipe(t_types type)
{
	if (type == INPUT || type == OUTPUT
		|| type == HERE_DOC || type == APPEND
		return (1);
	return (0);
}

int handle_redirs(t_tokens *tmp, int *stat)
{
	while (tmp)
	{
		if (!)
	}
}

