/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <nasargsy@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:27:47 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/07 16:34:59 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir_pipe(t_types type)
{
	if (type == INPUT || type == OUTPUT
		|| type == HERE_DOC || type == APPEND
		|| type == PIPE)
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	return (c == '\'' || c == '\"');
}

int	check_redir_pipe_operator(char *token, int regime)
{
	if (!ft_strncmp(token, "<<", 2)
		|| !ft_strncmp(token, ">>", 2)
		|| !ft_strncmp(token, "||", 2)
		|| !ft_strncmp(token, "&&", 2))
		return (2);
	else if (!ft_strncmp(token, "<", 1)
		|| !ft_strncmp(token, ">", 1)
		|| !ft_strncmp(token, "|", 1))
		return (1);
	if (regime == 2)
	{
		while (*token && !ft_isspace(*token))
			token++;
		token--;
		if (!ft_strncmp(token, "<<", 2)
			|| !ft_strncmp(token, ">>", 2)
			|| !ft_strncmp(token, "||", 2)
			|| !ft_strncmp(token, "&&", 2))
			return (-2);
		else if (!ft_strncmp(token, "<", 1)
			|| !ft_strncmp(token, ">", 1)
			|| !ft_strncmp(token, "|", 1))
			return (-1);
	}
	return (0);
}

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
