/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:21:29 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/04 19:14:51 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// static int	execute_all(t_commands *commands, t_tokens *tokens, t_hash_table *env)
// {
// 	(void)commands;
// 	(void)tokens;
// 	(void)env;
// 	return (0);
// }

int	execute(t_tokens *tokens, t_hash_table *env, int stat)
{
	// t_commands	*commands;

	expand_tokens(&tokens, env, stat);
	// commands = tokens_to_commands(tokens);
	// stat = execute_all(commands, tokens, env);
	stat = execute_no_pipes(tokens, env);
	return (stat);
}
