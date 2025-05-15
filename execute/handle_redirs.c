/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:29:49 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/15 17:17:50 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	open_outfile(char *filename, int mode)
{
	if (access(filename, F_OK) != 0)
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (access(filename, W_OK) != 0)
		return (quit_with_error("permission denied", -1));
	if (!access(filename, F_OK) && mode == APPEND)
		return (open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (open(filename, O_WRONLY | O_TRUNC));
}

int	do_redir(t_tokens *tokens, int *saved_fd)
{
	int	outfile;

	while (tokens)
	{
		if (tokens->type == OUTPUT || tokens->type == APPEND)
		{
			outfile = open_outfile(tokens->next->token, tokens->type);
			if (outfile == -1)
				return (outfile);
			*saved_fd = dup(STDOUT_FILENO);
			dup2(outfile, STDOUT_FILENO);
			close(outfile);
			break ;
		}
		tokens = tokens->next;
	}
	return (0);
}
