/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:24:49 by armarake          #+#    #+#             */
/*   Updated: 2025/05/28 15:25:00 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static int	actual_len(char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (arg[i])
	{
		if (arg[i] != '\'' && arg[i] != '\"')
			len++;
		i++;
	}
	return (len);
}

static void	allocate_new(t_tokens **tokens)
{
	int		i;
	int		j;
	int		len;
	char	*new_token;

	i = -1;
	j = 0;
	len = actual_len((*tokens)->token);
	new_token = malloc(len + 1);
	while ((*tokens)->token[++i])
		if ((*tokens)->token[i] != '\'' && (*tokens)->token[i] != '\"')
			new_token[j++] = (*tokens)->token[i];
	new_token[j] = '\0';
	free((*tokens)->token);
	(*tokens)->token = new_token;
}

void	remove_quotes(t_tokens **tokens)
{
	int			i;
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp->type != NEWL)
	{
		i = 0;
		while (tmp->token[i])
		{
			if (tmp->token[i] != '\'' && tmp->token[i] != '\"')
				allocate_new(&tmp);
			i++;
		}
		tmp = tmp->next;
	}
}
