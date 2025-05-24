/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:23:10 by armarake          #+#    #+#             */
/*   Updated: 2025/05/24 22:15:25 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	find_start_index(char *old_token, int doll_pos)
{
	int	i;

	i = doll_pos + 1;
	while (old_token[i])
	{
		if (old_token[i] == '\'' || old_token[i] == '\"'
			|| old_token[i] == '+' || old_token[i] == '='
			|| old_token[i] == '$')
			return (i);
		i++;
	}
	return (INT_MIN);
}

static int	the_rest_len(char *old_token, int start)
{
	int	i;
	int	len;

	len = 0;
	i = start;
	while (old_token[i])
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
	if (start_index != INT_MIN)
	{
		len = the_rest_len((*tokens)->token, start_index);
		ft_memmove(*new + start, (*tokens)->token + start_index, len);
	}
}

int	safe_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
