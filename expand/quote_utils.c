/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:20:41 by armarake          #+#    #+#             */
/*   Updated: 2025/05/30 21:57:47 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	must_expand(char *str, int start, int end, int *doll_pos)
{
	int	i;

	if (str[start] == '\'')
		return (0);
	i = start - 1;
	while (str[++i] && i < end)
	{
		if (str[i] == '$' && str[i + 1])
		{
			*doll_pos = i;
			return (1);
		}
	}
	return (0);
}

int	find_new_end(char *str, int start, char quote)
{
	int	i;

	i = start + 1;
	while (str[i])
	{
		if (str[i] == quote)
			break ;
		i++;
	}
	return (i);
}

void	remove_quote_helper(char *str, char quote, char **new, int len)
{
	int		i;
	int		j;
	int		count;

	i = -1;
	j = 0;
	count = 0;
	while (str[++i] && j < len)
	{
		if (str[i] == quote)
			count++;
		if (str[i] == quote && count > 2)
		{
			(*new)[j] = str[i];
			j++;
		}
		else if (str[i] != quote)
		{
			(*new)[j] = str[i];
			j++;
		}
	}
	(*new)[len] = '\0';
}
