/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:29:49 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/21 02:08:02 by armarake         ###   ########.fr       */
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

static int	stop_here_doc(char *line, char *limit, int line_number)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document at line ",
			STDOUT_FILENO);
		ft_putnbr_fd(line_number, STDOUT_FILENO);
		ft_putstr_fd(" delimited by end-of-file (wanted `",
			STDOUT_FILENO);
		ft_putstr_fd(limit, STDOUT_FILENO);
		ft_putendl_fd("')", STDOUT_FILENO);
		return (1);
	}
	if (ft_strcmp(limit, line) == 0)
		return (1);
	return (0);
}

void	here_doc(t_tokens **current, t_tokens **executable)
{
	int			i;
	int			fd;
	char		*line;
	static int	index;

	i = 1;
	if ((*executable)->type != NEWL && (*executable)->type != PIPE)
	{
		(*executable)->here_doc_file = ft_itoa(index++);
		fd = open((*executable)->here_doc_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	while (1)
	{
		line = readline(GREEN "> " RESET);
		if (stop_here_doc(line, (*current)->next->token, i++))
			break ;
		if ((*executable)->type != NEWL && (*executable)->type != PIPE)
		{
			write(fd, line, safe_strlen(line));
			write(fd, "\n", 1);
		}
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	if ((*executable)->type != NEWL && (*executable)->type != PIPE)
	{
		close(fd);
		(*executable)->input_is_heredoc = true;
		(*executable)->input = open((*executable)->here_doc_file, O_RDONLY);
	}
}

int	get_last_stat(t_stat *stat_struct)
{
	int	res;
	int	count;

	res = stat_struct->stat;
	count = stat_struct->pipe_count;
	if (stat_struct->last_in_fork && stat_struct->pid)
		waitpid(stat_struct->pid, &res, 0);
	while (count)
	{
		wait(NULL);
		count--;
	}
	if (res >= 256)
		res /= 256;
	return (res);
}

void	dup_and_close(t_tokens *tokens, t_stat *stat_struct)
{
	int	i;

	if (tokens->input != STDIN_FILENO)
	{
		dup2(tokens->input, STDIN_FILENO);
		close(tokens->input);
	}
	if (tokens->output != STDOUT_FILENO)
	{
		dup2(tokens->output, STDOUT_FILENO);
		close(tokens->output);
	}
	i = 0;
	while (stat_struct->pipe_fds[i])
	{
		if (stat_struct->pipe_fds[i][0] != tokens->input)
			close(stat_struct->pipe_fds[i][0]);
		if (stat_struct->pipe_fds[i][1] != tokens->output)
			close(stat_struct->pipe_fds[i][1]);
		i++;
	}
}
