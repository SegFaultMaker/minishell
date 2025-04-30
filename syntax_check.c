/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:13:41 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/30 14:31:49 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*

int	syntax_check(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	if (!check_builtin(tmp->token)
		&& !check_redirs(tmp->token))
		tmp->type = COMMAND;
	tmp = tmp->next;
	while (tmp)
	{
		
	}
}	
