/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nasargsy <nasargsy@student.42yerevan.am>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/04/28 13:35:04 by nasargsy		   #+#	  #+#			  */
/*	 Updated: 2025/04/28 14:08:39 by nasargsy		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "parser.h"

static int	quotes(char **str, char **start)
{
	int		len;
	int		in_quote;
	char	last_quote;

	len = 1;
	in_quote = 1;
	last_quote = **str;
	*start = *str;
	(*str)++;
	while (**str)
	{
		if (ft_isspace(**str) && !in_quote)
			break ;
		if ((**str == '\"' || **str == '\'') && in_quote && **str == last_quote)
			in_quote = 0;
		else if ((**str == '\"' || **str == '\'') && !in_quote)
		{
			in_quote = 1;
			last_quote = **str;
		}
		len++;
		(*str)++;
	}
	return (len);
}

static int	regular(char **str, char **start)
{
	int	len;
	int	in_quote;

	len = check_redir_pipe_operator(*str, 2);
	in_quote = 0;
	*start = *str;
	if (len > 0)
	{
		(*str) += len;
		return (len);
	}
	while (**str)
	{
		if ((ft_isquote(**str) && !in_quote)
			|| (ft_isquote(**str) && in_quote))
			in_quote = !in_quote;
		if ((check_redir_pipe_operator(*str, 1) || ft_isspace(**str))
			&& !in_quote)
			break ;
		len++;
		(*str)++;
	}
	return (len);
}

static t_tokens	*get_token(char **str)
{
	char	*start;
	char	*token;
	int		len;

	len = 0;
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '\"' || **str == '\'')
		len = quotes(str, &start);
	else
		len = regular(str, &start);
	if (len == 0)
		return (NULL);
	token = ft_substr(start, 0, len);
	if (!token)
		return (NULL);
	return (new_token(token));
}

t_tokens	*parser(char *str)
{
	t_tokens	*head;
	t_tokens	*current;
	t_tokens	*new;

	head = NULL;
	while (*str)
	{
		new = get_token(&str);
		if (!new)
			continue ;
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
	}
	current->next = new_token(ft_strdup("\n"));
	current->next->type = NEWL;
	assign_types(&head);
	if (!syntax_check(head))
		return (free_tokens(&head), NULL);
	return (head);
}
