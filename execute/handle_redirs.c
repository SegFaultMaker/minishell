/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:29:49 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/17 14:11:39 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	open_infile(char *filename)
{
	if (access(filename, F_OK) != 0)
		return (quit_with_error(1, filename, errno));
	if (access(filename, R_OK) != 0)
		return (quit_with_error(1, filename, errno));
	return (open(filename, O_RDONLY));
}

int	open_outfile(char *filename, int mode)
{
	if (access(filename, F_OK) != 0)
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (access(filename, W_OK) != 0)
		return (quit_with_error(1, filename, errno));
	if (!access(filename, F_OK) && mode == OUTPUT)
	{
		errno = EPERM;
		return (quit_with_error(1, filename, errno));
	}
	if (!access(filename, F_OK) && mode == APPEND)
		return (open(filename, O_WRONLY | O_APPEND, 0644));
	return (open(filename, O_WRONLY | O_TRUNC));
}

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

int	do_redir(t_tokens *tokens, int *saved_in, int *saved_out)
{
	int	fd;

	while (tokens)
	{
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
		tokens = tokens->next;
	}
	return (0);
}
