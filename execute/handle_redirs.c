/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:29:49 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/13 15:59:17 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	open_outfile(char *filename)
{
	if (access(filename, F_OK) != 0)
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC));
	if (access(filename, W_OK) != 0)
		return (quit_with_error("permission denied", -1));
	return (open(filename, O_WRONLY | O_TRUNC));
}

static int	handle_outfile(t_tokens *outfile, int *saved_fd)
{
	int	outfile_fd;

	outfile_fd = open_outfile(outfile->token);
	if (outfile_fd == -1)
		return (-1);
	*saved_fd = dup(STDOUT_FILENO);
	if (*saved_fd == -1)
	{
		close(outfile_fd);
		return (-1);
	}
	*saved_fd = outfile_fd;
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	return (0);
}

int	do_redirs(t_tokens *tokens, int *saved_fd)
{
	int	stat;

	stat = 0;
	while (tokens)
	{
		if (tokens->type == OUTPUT)
		{
			stat = handle_outfile(tokens->next, saved_fd);
			return (stat);
		}
		tokens = tokens->next;
	}
	return (stat);
}

void	undo_redirs(t_tokens *tokens, int saved_fd)
{
	while (tokens)
	{
		if (tokens->type == OUTPUT)
		{
			dup2(saved_fd, STDOUT_FILENO);
			close(saved_fd);
			return ;
		}
		tokens = tokens->next;
	}
}
