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

static int	single_quotes(char **str, char **start)
{
	int	len;
	int	in_quote;

	len = 1;
	in_quote = 1;
	*start = *str;
	(*str)++;
	while (**str)
	{
		if (ft_isspace(**str) && !in_quote)
			break ;
		if (**str == '\'' && in_quote)
			in_quote = 0;
		else if (**str == '\'' && !in_quote)
			in_quote = 1;
		len++;
		(*str)++;
	}
	return (len);
}

static int	double_quotes(char **str, char **start)
{
	int	len;
	int	in_quote;

	len = 1;
	in_quote = 1;
	*start = *str;
	(*str)++;
	while (**str)
	{
		if (ft_isspace(**str) && !in_quote)
			break ;
		if (**str == '\"' && in_quote)
			in_quote = 0;
		else if (**str == '\"' && !in_quote)
			in_quote = 1;
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
		if (check_redir_pipe_operator(*str, 1)
			|| (ft_isspace(**str) && !in_quote))
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
	if (**str == '\'')
		len = single_quotes(str, &start);
	else if (**str == '\"')
		len = double_quotes(str, &start);
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
	{
		free_tokens(&head);
		return (NULL);
	}
	return (head);
}

// int	main()
// {
// 	char		*line;
// 	int	i = 1;
// 	t_tokens	*tokens;
// 	t_tokens	*tmp;

// 	line = NULL;
// 	line = readline("$ ");
// 	if (!line)
// 		return (0);
// 	tokens = parser(line);
// 	tmp = tokens;
// 	if (!tmp)
// 	{
// 		free(line);
// 		return (0);
// 	}
// 	ft_printf("==== Commands ====\n");
// 	i = 1;
// 	while (tmp)
// 	{
// 		ft_printf("Token %d: %s ", i, tmp->token);
// 		if (tmp->type == BUILTIN)
// 			ft_printf("BUILTIN\n");
// 		else if (tmp->type == COMMAND)
// 			ft_printf("COMMAND\n");
// 		else if (tmp->type == ARGUMENT)
// 			ft_printf("ARGUMENT\n");
// 		else if (tmp->type == PIPE)
// 			ft_printf("PIPE\n");
// 		else if (tmp->type == INPUT)
// 			ft_printf("INPUT\n");
// 		else if (tmp->type == OUTPUT)
// 			ft_printf("OUTPUT\n");
// 		else if (tmp->type == HERE_DOC)
// 			ft_printf("HERE_DOC\n");
// 		else if (tmp->type == APPEND)
// 			ft_printf("APPPEND\n");
// 		else if (tmp->type == FILE_NAME)
// 			ft_printf("FILE_NAME\n");
// 		else if (tmp->type == LIMITER)
// 			ft_printf("LIMITER\n");
// 		else if (tmp->type == OPERATOR)
// 			ft_printf("OPERATOR\n");
// 		else if (tmp->type == NONE)
// 			ft_printf("NONE\n");
// 		else
// 			ft_printf("NEWL");
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	free(line);
// 	free_tokens(&tokens);
// }
