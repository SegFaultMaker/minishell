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

#include "../minishell.h"

static int	ft_isquote(char c)
{
	return (c == '\'' || c == '\"');
}

static int	single_quotes(char **str, char **start)
{
	int	len;

	len = 0;
	if (**str == '\'')
	{
		if (*(*str + 1) == '\'')
			return (0);
		(*str)++;
	}
	*start = *str;
	while (*str && **str != '\'')
	{
		len++;
		(*str)++;
	}
	(*str)++;
	return (len);
}

static int	regular(char **str, char **start)
{
	int	len;

	len = 0;
	*start = *str;
	while (**str && !ft_isspace(**str) && !ft_isquote(**str))
	{
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
	if (**str == '\'')
		len = single_quotes(str, &start);
/*	else if (**str == '\"')										TODO
		len = double_quotes(&str, &start);*/
	else
		len = regular(str, &start);
	while (ft_isspace(**str) || ft_isquote(**str))
		(*str)++;
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
	return (head);
}
