/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <nasargsy@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:12:48 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/03 15:09:10 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_for_operators(t_tokens *tmp)
{
	while (tmp)
	{
		if (tmp->type == OPERATOR)
			return (1);
		tmp = tmp->next;
	}
	return (1);
}

static t_commands	*commands_new(t_tokens *first, t_tokens *second)
{
	t_commands	*res;

	res = malloc(sizeof(t_commands));
	if (!res)
	{
		ft_putstr_fd("minishell: malloc in get_commands\n", 2);
		return (NULL);
	}
	res->first = first;
	res->second = second;
	res->next = NULL;
	return (res);
}

static int	split_commands(t_commands **res)
{
	t_commands	*tmp;
	t_tokens	*tokens;

	tmp = *res;
	tokens = tmp->first;
	while (tokens)
	{
		if (tokens->type == OPERATOR && !tmp->second)
		{
			tmp->second = tokens->next;
			tokens->next = NULL;
			tokens = tmp->second;
		}
		else if (tokens->type == OPERATOR && tmp->second)
		{
			tmp->next = commands_new(tokens->next, NULL);
			if (!tmp->next)
				return (0);
			tmp = tmp->next;
			tokens->next = NULL;
			tokens = tmp->first;
		}
		tokens = tokens->next;
	}
	return (1);
}

t_commands	*get_commands(char *str)
{
	t_commands	*res;

	res = commands_new(NULL, NULL);
	if (!res)
		return (NULL);
	res->first = parser(str);
	if (!res->first)
	{
		clean_commands(&res);
		return (NULL);
	}
	if (!check_for_operators(res->first))
	{
		res->second = NULL;
		res->next = NULL;
	}
	else
	{
		if (!split_commands(&res))
		{
			clean_commands(&res);
			return (NULL);
		}
	}
	return (res);
}

/*int	main()
{
	char	*line;
	int	i = 1;
	int cmd_index = 1;
	t_commands	*commands;
	t_commands	*tmp;
	t_tokens	*first;
	t_tokens	*second;

	line = readline("$ ");
	commands = get_commands(line);
	if (!commands)
	{
		free(line);
		return (1);
	}
	tmp = commands;
	while (tmp)
	{
		first = tmp->first;
		second = tmp->second;
		ft_printf("==== Command %d ====\n", cmd_index);
		i = 1;
		while (first)
		{
			ft_printf("Token %d: %s ", i, first->token);
			if (first->type == BUILTIN)
				ft_printf("BUILTIN\n");
			else if (first->type == COMMAND)
				ft_printf("COMMAND\n");
			else if (first->type == ARGUMENT)
				ft_printf("ARGUMENT\n");
			else if (first->type == PIPE)
				ft_printf("PIPE\n");
			else if (first->type == INPUT)
				ft_printf("INPUT\n");
			else if (first->type == OUTPUT)
				ft_printf("OUTPUT\n");
			else if (first->type == HERE_DOC)
				ft_printf("HERE_DOC\n");
			else if (first->type == APPEND)
				ft_printf("APPPEND\n");
			else if (first->type == FILE_NAME)
				ft_printf("FILE_NAME\n");
			else if (first->type == LIMITER)
				ft_printf("LIMITER\n");
			else if (first->type == OPERATOR)
				ft_printf("OPERATOR\n");
			i++;
			first = first->next;
		}
		if (second)
		{
			cmd_index++;
			ft_printf("==== Command %d ====\n", cmd_index);
			i = 1;
		}
		while (second)
		{
			ft_printf("Token %d: %s ", i, second->token);
			if (second->type == BUILTIN)
				ft_printf("BUILTIN\n");
			else if (second->type == COMMAND)
				ft_printf("COMMAND\n");
			else if (second->type == ARGUMENT)
				ft_printf("ARGUMENT\n");
			else if (second->type == PIPE)
				ft_printf("PIPE\n");
			else if (second->type == INPUT)
				ft_printf("INPUT\n");
			else if (second->type == OUTPUT)
				ft_printf("OUTPUT\n");
			else if (second->type == HERE_DOC)
				ft_printf("HERE_DOC\n");
			else if (second->type == APPEND)
				ft_printf("APPPEND\n");
			else if (second->type == FILE_NAME)
				ft_printf("FILE_NAME\n");
			else if (second->type == LIMITER)
				ft_printf("LIMITER\n");
			else if (second->type == OPERATOR)
				ft_printf("OPERATOR\n");
			i++;
			second = second->next;
		}
		tmp = tmp->next;
		if (tmp)
			cmd_index++;
	}
	free(line);
	clean_commands(&commands);
}*/
