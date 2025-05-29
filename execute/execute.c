/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:21:29 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/29 14:51:11 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute(t_tokens *tokens, t_hash_table *env, int stat)
{
//	int	pipes;

	expand_tokens(&tokens, env, stat);
/*	pipes = check_pipes(tokens);
	if (pipes)
		stat = execute_with_pipes(tokens, env);
	else*/
		stat = execute_no_pipes(tokens, env);
	return (stat);
}
