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
	while (ft_isspace(**str))
		(*str)++;
	if (**str == '\'')
		len = single_quotes(str, &start);
/*	else if (**str == '\"')										TODO
		len = double_quotes(&str, &start);*/
	else
		len = regular(str, &start);
	while (ft_isquote(**str))
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
	assign_types(&head);
	return (head);
}

int	main()
{
	char	*line;
	t_tokens	*tokens;
	t_tokens	*tmp;
	int	i = 1;

	line = readline("$ ");
	tokens = parser(line);
	tmp = tokens;
	while (tmp)
	{
		ft_printf("Tokem %d: %s ", i, tmp->token);
		if (tmp->type == BUILTIN)
			ft_printf("BUILTIN\n");
		else if (tmp->type == COMMAND)
			ft_printf("COMMAND\n");
		else if (tmp->type == ARGUMENT)
			ft_printf("ARGUMENT\n");
		else if (tmp->type == PIPE)
			ft_printf("PIPE\n");
		else if (tmp->type == INPUT)
			ft_printf("INPUT\n");
		else if (tmp->type == OUTPUT)
			ft_printf("OUTPUT\n");
		else if (tmp->type == HERE_DOC)
			ft_printf("HERE_DOC\n");
		else if (tmp->type == APPEND)
			ft_printf("APPPEND\n");
		else if (tmp->type == FILE_NAME)
			ft_printf("FILE_NAME\n");
		else
			ft_printf("LIMITER\n");
		i++;
		tmp = tmp->next;
	}
	free(line);
	free_tokens(&tokens);
}
