/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:05:27 by armarake          #+#    #+#             */
/*   Updated: 2025/05/29 12:15:33 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	**tokens_to_strings(t_tokens *cmd)
{
	char		**res;
	int			i;
	t_tokens	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp->type != NEWL && tmp->type != PIPE)
	{
		if (tmp->type == ARGUMENT || tmp->type == COMMAND)
			i++;
		tmp = tmp->next;
	}
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	res[i] = NULL;
	i = 0;
	while (cmd->type != NEWL && tmp->type != PIPE)
	{
		if (cmd->type == ARGUMENT || cmd->type == COMMAND)
			res[i++] = ft_strdup(cmd->token);
		cmd = cmd->next;
	}
	return (res);
}

int	check_pipes(t_tokens *tokens)
{
	int	pipe_count;

	pipe_count = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			pipe_count++;
		tokens = tokens->next;
	}
	return (pipe_count);
}

int	define_type(t_tokens *tokens)
{
	while (tokens)
	{
		if (tokens->type == BUILTIN)
			return (BUILTIN);
		if (tokens->type == COMMAND)
			return (COMMAND);
		tokens = tokens->next;
	}
	return (NONE);
}

int	quit_with_error(int flag, char *target, char *description, int stat)
{
	char	*err_msg;

	if (flag)
		ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (target)
	{
		ft_putstr_fd(target, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (description)
		err_msg = description;
	else
		err_msg = strerror(stat);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	return (stat);
}

void	free_matrix(char **matrix)
{
	int		i;

	if (matrix == NULL || *matrix == NULL)
		return ;
	i = 0;
	while (matrix[i])
	{
		if (matrix[i])
			free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}
