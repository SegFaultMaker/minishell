/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 03:04:48 by armarake          #+#    #+#             */
/*   Updated: 2025/06/22 19:28:06 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

static void	setup_heredoc(t_tokens **executable,
	int *index, int *fd, int *line_num)
{
	*line_num = 1;
	if ((*executable)->type != NEWL && (*executable)->type != PIPE)
	{
		(*executable)->here_doc_file = ft_itoa((*index)++);
		*fd = open((*executable)->here_doc_file,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
		*fd = -1;
}

static void	finish_heredoc(t_tokens **executable, pid_t pid, int fd)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	init_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		if (fd != -1)
			close(fd);
		unlink((*executable)->here_doc_file);
		(*executable)->input_is_heredoc = false;
		(*executable)->input = STDIN_FILENO;
	}
	else
	{
		if (fd != -1)
		{
			close(fd);
			(*executable)->input_is_heredoc = true;
			(*executable)->input = open((*executable)->here_doc_file, O_RDONLY);
		}
	}
}

void	here_doc_loop(t_tokens **current, t_tokens **executable,
	int *line_num, int fd)
{
	char	*line;

	while (1)
	{
		line = readline(GREEN "> " RESET);
		if (stop_here_doc(line, (*current)->next->token, (*line_num)++))
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
}

void	here_doc(t_tokens **current, t_tokens **executable)
	{
	int			fd;
	int			line_num;
	static int	index;
	pid_t		pid;

	setup_heredoc(executable, &index, &fd, &line_num);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_heredoc);
		rl_catch_signals = 0;
		here_doc_loop(current, executable, &line_num, fd);
		if (fd != -1)
			close(fd);
		exit(0);
	}
	finish_heredoc(executable, pid, fd);
}
