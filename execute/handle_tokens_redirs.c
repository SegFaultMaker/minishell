/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens_redirs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:48:53 by armarake          #+#    #+#             */
/*   Updated: 2025/06/24 13:40:06 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	handle_input_redir(t_tokens **current, t_tokens **executable,
	t_hash_table *env, t_stat *stat)
{
	int	check_status;

	check_status = input_redir_checks(current, executable, env, stat);
	if (check_status != 2)
		return (check_status);
	(*executable)->input = open_infile((*current)->next->token);
	if ((*executable)->input == -1)
	{
		stat->stat = 1;
		(*executable)->execute = false;
		while (1)
		{
			if ((*current)->type == PIPE)
				break ;
			if ((*current)->type == NEWL)
				return (0);
			(*current) = (*current)->next;
		}
		(*executable) = find_executable((*current)->next);
		(*executable)->input = open("/dev/null", O_RDWR);
		(*current) = (*executable);
		return (1);
	}
	return (0);
}

int	handle_output_redir(t_tokens **current, t_tokens **executable, t_stat *stat)
{
	if ((*executable)->type == NEWL)
		return (open_outfile((*current)->next->token, (*current)->type),
			(*current) = (*executable), 1);
	if ((*executable)->type == PIPE)
		return ((*current) = (*executable),
			(*executable) = NULL, 1);
	(*executable)->output = open_outfile((*current)->next->token,
			(*current)->type);
	if ((*executable)->output == -1)
	{
		stat->stat = 1;
		(*executable)->execute = false;
		while (1)
		{
			if ((*current)->type == PIPE)
				break ;
			if ((*current)->type == NEWL)
				return (0);
			(*current) = (*current)->next;
		}
		(*executable) = find_executable((*current)->next);
		(*executable)->input = open("/dev/null", O_RDWR);
		return ((*current) = (*executable), 1);
	}
	return (0);
}

void	handle_pipe_redir(t_tokens **current, t_tokens **executable,
	int **pipe_fds, int *i)
{
	if (!(*executable) || (*executable)->output != STDOUT_FILENO)
		close(pipe_fds[(*i)][1]);
	else
		(*executable)->output = pipe_fds[(*i)][1];
	(*executable) = find_executable((*current)->next);
	(*executable)->input = pipe_fds[(*i)][0];
	(*i)++;
}

void	free_pipes(int ***array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return ;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
}

int	**allocate_pipe_fds(int pipe_count)
{
	int	i;
	int	**result;

	i = 0;
	result = malloc(sizeof(int *) * (pipe_count + 1));
	if (!result)
		return (NULL);
	while (i < pipe_count)
	{
		result[i] = malloc(sizeof(int) * 2);
		if (!result)
			return (free_pipes(&result), NULL);
		if (pipe(result[i]))
			return (free_pipes(&result), NULL);
		i++;
	}
	result[i] = NULL;
	return (result);
}
