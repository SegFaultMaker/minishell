/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:05:27 by armarake          #+#    #+#             */
/*   Updated: 2025/05/16 13:41:16 by armarake         ###   ########.fr       */
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
	while (tmp->type != NEWL)
	{
		i++;
		tmp = tmp->next;
	}
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
	{
		ft_putstr_fd("minishell: execution: malloc error\n", STDERR_FILENO);
		return (NULL);
	}
	res[i] = NULL;
	i = 0;
	while (cmd->type != NEWL)
	{
		res[i++] = cmd->token;
		cmd = cmd->next;
	}
	return (res);
}

int check_pipes(t_tokens *tokens)
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

int	quit_with_error(int flag, char *target, int stat)
{
	if (flag)
		ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (target)
	{
		ft_putstr_fd(target, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(strerror(stat), STDERR_FILENO);
	return (stat);
}

void	free_matrix(char ***matrix)
{
	int		i;
	char	**s;

	if (matrix == NULL || *matrix == NULL)
		return ;
	s = *matrix;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	*matrix = NULL;
}
