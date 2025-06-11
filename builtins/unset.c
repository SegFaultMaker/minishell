/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:16:46 by armarake          #+#    #+#             */
/*   Updated: 2025/06/11 17:46:03 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	unset(t_tokens *tokens, t_hash_table *ht)
{
	while (tokens->type != PIPE && tokens->type != NEWL)
	{
		if (tokens->type == ARGUMENT && tokens->token)
			ht_delete(ht, tokens->token);
		tokens = tokens->next;
	}
	return (0);
}
