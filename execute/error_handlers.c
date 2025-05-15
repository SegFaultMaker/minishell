/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <nasargsy@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:43:34 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/15 14:48:09 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	handle_access(char *cmd)
{
	(void)cmd;
	if (errno == EACCES)
		quit_with_error("access: Permission denied", errno);
	else if (errno == ELOOP)
		quit_with_error("access: Too many symbolic links", errno);
	else if (errno == EINVAL)
		quit_with_error("access: Invalid argument", errno);
	else if (errno == EIO)
		quit_with_error("access: I/O error", errno);
	else if (errno == ENAMETOOLONG)
		quit_with_error("access: File or path name too long", errno);
	else if (errno == ENOENT)
		quit_with_error("access: No such file or directory", errno);
	else if (errno == ENOMEM)
		quit_with_error("access: Not enough core", errno);
	else if (errno == ENOTDIR)
		quit_with_error("access: Not a directory", errno);
	else if (errno == EPERM)
		quit_with_error("access: Not super-user", errno);
	else if (errno = EROFS)
		quit_with_error("access: Read only file system", errno);
	else if (errno == ETXTBSY)
		quit_with_error("access: Text file busy", errno);
}

void	handle_execve(char *cmd)
{
	(void)cmd;
	if (errno == E2BIG)
		quit_with_error("Arg list too long", errno);
	else if (errno == EWOULDBLOCK)
		quit_with_error("Operation would block", errno);
	else if (errno == EFAULT)
		quit_with_error("Bad address", errno);
	else if (errno == EIO)
		quit_with_error("I/O error", errno);
	else if (errno == EISDIR)
		quit_with_error("Is a directory", errno);
	else if (errno == ELIBBAD)
		quit_with_error("Accessing a corrupted shared lib", errno);
	else if (errno == EMFILE)
		quit_with_error("Too many open files", errno);
	else if (errno == ENOEXEC)
		quit_with_error("Exec format error", errno);
	else if (errno == ENOMEM)
		quit_with_error("Not enough core", errno);
	else if (errno == ENOTDIR)
		quit_with_error("Not a directory", errno);
	else if (errno == EPERM)
		quit_with_error("Not super-user", errno);
	else if (errno == ETXTBSY)
		quit_with_error("Text file busy", errno);
}

void	handle_fork(void)
{
	if (errno == EAGAIN)
		quit_with_error("fork: retry: Resource temporarily unavailable", errno);
	else if (errno == ENOMEM)
		quit_with_error("fork: Cannot allocate memory", errno);
}
