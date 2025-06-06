/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:12:08 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/06 22:38:43 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	open_infile(char *filename)
{
	if (access(filename, F_OK) != 0)
		return (quit_with_error(1, filename, NULL, errno), -1);
	if (access(filename, R_OK) != 0)
		return (quit_with_error(1, filename, NULL, errno), -1);
	return (open(filename, O_RDONLY));
}

int	open_outfile(char *filename, int mode)
{
	if (access(filename, F_OK) != 0)
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (access(filename, W_OK) != 0)
		return (quit_with_error(1, filename, NULL, errno), -1);
	if (!access(filename, F_OK) && mode == OUTPUT)
	{
		return (quit_with_error(1, filename,
				"cannot overwrite existing file", 1), -1);
	}
	if (!access(filename, F_OK) && mode == APPEND)
		return (open(filename, O_WRONLY | O_APPEND, 0644));
	return (open(filename, O_WRONLY | O_TRUNC));
}
