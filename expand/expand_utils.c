/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:23:10 by armarake          #+#    #+#             */
/*   Updated: 2025/06/24 14:35:29 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*find_var(char *str, t_hash_table *env)
{
	int		i;
	char	*var;
	char	*res;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (NULL);
	var[i] = '\0';
	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		var[i] = str[i];
		i++;
	}
	res = ht_search(env, var);
	free(var);
	return (res);
}

int	quote_start(char *token, int *quote, int *i)
{
	if (!(*quote) && (token[*i] == '\'' || token[*i] == '"'))
	{
		*quote = token[*i];
		(*i)++;
		return (1);
	}
	return (0);
}

int	quote_end(char *token, int *quote, int *i)
{
	if (*quote && token[*i] == *quote)
	{
		*quote = 0;
		(*i)++;
		return (1);
	}
	return (0);
}
