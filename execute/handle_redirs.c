/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:29:49 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/20 15:36:12 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	undo_redir(int saved_in, int saved_out)
{
	if (saved_in != INT_MIN)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	if (saved_out != INT_MIN)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
}

int	except_here_doc(t_tokens *tokens, int *saved_in, int *saved_out)
{
	int	fd;

	if (tokens->type == INPUT)
	{
		fd = open_infile(tokens->next->token);
		if (fd == errno)
			return (errno);
		*saved_in = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (tokens->type == OUTPUT || tokens->type == APPEND)
	{
		fd = open_outfile(tokens->next->token, tokens->type);
		if (fd == errno)
			return (errno);
		*saved_out = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

void	here_doc(t_tokens *tokens)
{
	char	*input;
	char	*temp;
	char	*res;

	res = NULL;
	ft_putstr_fd("> ", STDIN_FILENO);
	input = get_next_line(STDIN_FILENO);
	while (input && ft_strcmp(input + 2, tokens->next->token))
	{
		temp = ft_strdup(res);
		free(res);
		res = ft_strjoin(temp, input);
		free(temp);
		free(input);
		ft_putstr_fd("> ", STDIN_FILENO);
		input = get_next_line(STDIN_FILENO);
	}
	ft_putstr_fd(res, STDIN_FILENO);
}

int	do_redir(t_tokens *tokens, int *saved_in, int *saved_out)
{
	while (tokens)
	{
		if (tokens->type == OUTPUT || tokens->type == APPEND
			|| tokens->type == INPUT)
		{
			errno = except_here_doc(tokens, saved_in, saved_out);
			if (errno)
				return (errno);
		}
		if (tokens->type == HERE_DOC)
			here_doc(tokens);
		tokens = tokens->next;
	}
	return (0);
}
