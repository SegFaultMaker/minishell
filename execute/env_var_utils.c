/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:23:10 by armarake          #+#    #+#             */
/*   Updated: 2025/05/23 15:14:50 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	find_start_index(char *old_token, int doll_pos)
{
	int	i;

	i = doll_pos;
	while (old_token[i])
	{
		if (old_token[i] == '\'' || old_token[i] == '\"'
			|| old_token[i] == '+' || old_token[i] == '=')
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
	int		start_index;

	start_index = find_start_index((*tokens)->token, doll_pos);
	len = the_rest_len(tokens, start_index);
	if (start_index != INT_MIN)
		ft_memmove(*new + start, (*tokens)->token + start_index, len);
}
