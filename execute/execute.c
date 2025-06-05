/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:21:29 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/05 14:02:03 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"


void	do_redirections(t_tokens *tokens)
{
	while (tokens->type != NEWL)
	{
		
		tokens = tokens->next;
	}
	
}

int	execute(t_tokens *tokens, t_hash_table *env, int stat)
{
	expand_tokens(&tokens, env, stat);
	// stat = execute_no_pipes(tokens, env);
	return (stat);
}
