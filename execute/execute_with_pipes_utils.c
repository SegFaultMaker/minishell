/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_pipes_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:09:22 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/29 14:20:59 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	get_commands(t_tokens *tokens)
{
	int	res;

	res = 0;
	while (tokens)
	{
		if (tokens->type == COMMAND)
			res++;
		tokens = tokens->next;
	}
	return (res);
}

char	***get_argvs(t_tokens *tokens, int i)
{
	char	***res;
	int		i;

	res = malloc(sizeof(char **) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (tokens->type == COMMAND)
		{
			res[i] = tokens_to_strings(tokens);
			i++;
		}
		tokens = tokens->next;
	}
	res[i] = NULL;
	return (res);
}
