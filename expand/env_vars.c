/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:19:40 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/29 15:23:49 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

// static int	needs_handling(char *str)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 		if ((str[i] == '\'' || str[i] == '\"') || (str[i] == '$' && str[i + 1]))
// 			return (1);
// 	return (0);
// }

void	expand_tokens(t_tokens **tokens, t_hash_table *env, int stat)
{
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp->type != NEWL)
	{
		// while (needs_handling(tmp->token))
			handle_token(&tmp, env, stat);
		tmp = tmp->next;
	}
}
