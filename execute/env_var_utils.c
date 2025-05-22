/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:23:10 by armarake          #+#    #+#             */
/*   Updated: 2025/05/22 17:55:14 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	find_quote_after_env(char *old_token, int doll_pos)
{
	int	i;

	i = doll_pos;
	while (old_token[i])
	{
		if (old_token[i] == '\'' || old_token[i] == '\"')
			return (i);
		i++;
	}
	return (INT_MIN);
}

static int	the_rest_len(t_tokens **tokens, int quote_pos)
{
	int	i;
	int	len;
	
	len = 0;
	i = quote_pos - 1;
	while ((*tokens)->token[i])
	{
		i++;
		len++;
	}
	return (len);
}

void	add_the_rest(t_tokens **tokens, int doll_pos, char **new, int start)
{
	int		len;
	int		quote_pos;

	quote_pos = find_quote_after_env((*tokens)->token, doll_pos);
	len = the_rest_len(tokens, quote_pos);
	if (quote_pos != INT_MIN)
		ft_memmove(*new + start, (*tokens)->token + quote_pos, len);
}