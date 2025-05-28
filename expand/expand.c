/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:22:15 by armarake          #+#    #+#             */
/*   Updated: 2025/05/28 15:38:29 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	expand_tokens(t_tokens **tokens, t_hash_table *env, int stat)
{
	env_vars(tokens, env, stat);
	remove_quotes(tokens);
}
