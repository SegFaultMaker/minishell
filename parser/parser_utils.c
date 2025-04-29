/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <nasargsy@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:27:47 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/29 13:37:11 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_tokens **tokens)
{
	t_tokens	*temp;
	t_tokens	*next;

	if (!tokens)
		return ;
	temp = *tokens;
	while (temp)
	{
		next = temp->next;
		free(temp->token);
		free(temp);
		temp = next;
	}
	*tokens = NULL;
}

t_tokens	*new_token(char *content)
{
	t_tokens	*node;

	node = (t_tokens *)malloc(sizeof(t_tokens));
	if (!node)
		return (NULL);
	node->token = content;
	node->next = NULL;
	return (node);
}
