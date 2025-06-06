/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:29:49 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/06 16:19:24 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	undo_builtin_redirs(int saved_in, int saved_out)
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

static void	free_values(char *temp, char *input)
{
	free(temp);
	free(input);
	temp = NULL;
	input = NULL;
}

void	here_doc(t_tokens *tokens, int fd)
{
	char	*input;
	char	*temp;
	char	*res;

	input = NULL;
	res = ft_strdup("");
	if (!res)
		return ;
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		input = get_next_line(STDIN_FILENO);
		if (!input || !ft_strncmp(input,
				tokens->next->token, ft_strlen(tokens->next->token)))
			break ;
		temp = res;
		res = ft_strjoin(res, input);
		free_values(temp, input);
	}
	if (input)
		free(input);
	get_next_line(-1);
	write(fd, res, ft_strlen(res));
	free(res);
}
