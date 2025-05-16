/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:21:29 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/16 22:27:23 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute(t_tokens *tokens, t_hash_table *env, int stat)
{
/*	int	pipes;

	pipes = check_pipes(tokens);
	if (pipes)
		 stat = execute_with_pipes(tokens, env, pipes);
	else*/
	stat = execute_no_pipes(tokens, env);
	return (stat);
}
