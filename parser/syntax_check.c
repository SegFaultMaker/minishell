/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 syntax_check.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: armarake <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/04/30 14:13:41 by nasargsy		   #+#	  #+#			  */
/*	 Updated: 2025/06/05 14:21:57 by nasargsy		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "parser.h"

static int	generate_error(t_tokens *tmp)
{
	ft_putstr_fd(SYNTAX_ERR, 2);
	ft_putchar_fd('`', 2);
	if (tmp->type == NEWL)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(tmp->token, 2);
	ft_putstr_fd("\'\n", 2);
	errno = 2;
	return (0);
}

static int	check_quotes(char *str)
{
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	while (*str)
	{
		if (*str == '\"' && !dquote && !squote)
			dquote = 1;
		else if (*str == '\"' && dquote && !squote)
			dquote = 0;
		else if (*str == '\'' && !squote && !dquote)
			squote = 1;
		else if (*str == '\'' && squote && !dquote)
			squote = 0;
		str++;
	}
	if (dquote || squote)
	{
		ft_putendl_fd("minishell: syntax: Invalid quotes", 2);
		return (0);
	}
	return (1);
}

int	syntax_check(t_tokens *tmp)
{
	if (tmp->type == PIPE)
		return (generate_error(tmp));
	while (tmp && tmp->type != NEWL)
	{
		if (!check_quotes(tmp->token))
			return (0);
		if (is_redir_pipe(tmp->type))
		{
			if (tmp->type == tmp->next->type)
				return (generate_error(tmp));
			else if (tmp->next->type == NEWL)
				return (generate_error(tmp->next));
			else if (is_redir_pipe(tmp->type) && tmp->next->type == PIPE)
				return (generate_error(tmp->next));
		}
		tmp = tmp->next;
	}
	return (1);
}
