/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:29:49 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/20 17:29:18 by armarake         ###   ########.fr       */
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

void	here_doc(t_tokens **current, t_tokens **executable)
{
	int		fd;
	char	*line;

	fd = open("here_doc_tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline(GREEN "> " RESET);
		if (!line || !ft_strcmp((*current)->next->token, line))
			break ;
		write(fd, line, safe_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	close(fd);
	(*executable)->input_is_heredoc = true;
	(*executable)->input = open("here_doc_tmp_file", O_RDONLY);
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
