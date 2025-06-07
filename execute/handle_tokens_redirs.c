/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens_redirs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:48:53 by armarake          #+#    #+#             */
/*   Updated: 2025/06/07 14:24:47 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	handle_input_redir(t_tokens **current, t_tokens **executable)
{
	if ((*executable)->type == NEWL)
		return ((*current) = (*executable), CONTINUE_THE_LOOP);
	if ((*executable)->type == PIPE)
	{
		(*current) = (*executable);
		(*executable) = NULL;
		return (CONTINUE_THE_LOOP);
	}
	(*executable)->input = open_infile((*current)->next->token);
	if ((*executable)->input == -1)
	{
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
		(*current) = (*executable);
		return (CONTINUE_THE_LOOP);
	}
	return (0);
}

int	handle_output_redir(t_tokens **current, t_tokens **executable)
{
	if ((*executable)->type == NEWL)
		return ((*current) = (*executable), CONTINUE_THE_LOOP);
	if ((*executable)->type == PIPE)
	{
		(*current) = (*executable);
		(*executable) = NULL;
		return (CONTINUE_THE_LOOP);
	}
	(*executable)->output = open_outfile((*current)->next->token,
			(*current)->type);
	if ((*executable)->output == -1)
	{
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
		(*current) = (*executable);
		return (CONTINUE_THE_LOOP);
	}
	return (0);
}

void	handle_pipe_redir(t_tokens **current, t_tokens **executable,
	int **pipe_fds, int *i)
{
	if (!(*executable) || (*executable)->output != STDOUT_FILENO)
		close(pipe_fds[(*i)][1]);
	else
	{
		(*executable)->output = pipe_fds[(*i)][1];
		(*executable)->piped_out = true;
	}
	(*executable) = find_executable((*current)->next);
	(*executable)->input = pipe_fds[(*i)][0];
	(*executable)->piped_in = true;
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
