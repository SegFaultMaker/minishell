/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:23:10 by armarake          #+#    #+#             */
/*   Updated: 2025/05/28 15:19:36 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	calculate_len(char *old, int doll_pos, char *env_var, int *flag)
{
	int	i;
	int	len;

	i = doll_pos + 1;
	*flag = 0;
	len = doll_pos + safe_strlen(env_var);
	while (old[i] && old[i] != '\"' && old[i] != '\''
		&& old[i] != '+' && old[i] != '=' && old[i] != '$')
		i++;
	if (!old[i])
		return (len);
	if (old[i] != '\"' && old[i] != '\'' && old[i] != '+'
		&& old[i] != '=' && old[i] != '$')
		return (len);
	*flag = 1;
	while (old[i])
	{
		i++;
		len++;
	}
	return (len);
}

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

int	the_rest_len(char *old_token, int start)
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
