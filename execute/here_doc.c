/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 03:04:48 by armarake          #+#    #+#             */
/*   Updated: 2025/06/25 21:04:25 by armarake         ###   ########.fr       */
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

static int	setup_heredoc(t_tokens **executable, t_stat *stat)
{
	char	*temp;

	stat->line_num = 1;
	if ((*executable)->type != NEWL && (*executable)->type != PIPE)
	{
		temp = ft_itoa(stat->here_doc_index);
		(*executable)->here_doc_file = ft_strjoin("./temp/here_doc_", temp);
		free(temp);
		stat->here_doc_index++;
		stat->here_doc_fd = open((*executable)->here_doc_file,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (stat->here_doc_fd == -1)
		{
			(*executable)->execute = false;
			ft_putendl_fd("minishell: heredoc error", STDERR_FILENO);
			return (0);
		}
	}
	else
		stat->here_doc_fd = -1;
	(*executable)->sigint_heredoc = false;
	return (1);
}

static void	finish_heredoc(t_tokens **executable, pid_t pid, t_stat *stat)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	init_signals();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		if (stat->here_doc_fd != -1)
			close(stat->here_doc_fd);
		unlink((*executable)->here_doc_file);
		(*executable)->input_is_heredoc = false;
		(*executable)->execute = false;
		(*executable)->sigint_heredoc = true;
		(*executable)->input = STDIN_FILENO;
	}
	else
	{
		if (stat->here_doc_fd != -1)
		{
			close(stat->here_doc_fd);
			(*executable)->input_is_heredoc = true;
			(*executable)->input = open((*executable)->here_doc_file, O_RDONLY);
		}
	}
}

void	here_doc_loop(t_tokens **current, t_tokens **executable,
	t_hash_table *env, t_stat *stat)
{
	char	*expanded;
	char	*line;

	expanded = NULL;
	while (1)
	{
		line = readline(GREEN "> " RESET);
		if (stop_here_doc(line, (*current)->next->token, (stat->line_num)++))
			break ;
		if ((*executable)->type != NEWL && (*executable)->type != PIPE)
		{
			expanded = remove_and_expand_quotes(line, env, stat->stat);
			write(stat->here_doc_fd, expanded, safe_strlen(expanded));
			write(stat->here_doc_fd, "\n", 1);
		}
		free(line);
		line = NULL;
		free(expanded);
		expanded = NULL;
	}
	if (line)
		free(line);
	if (expanded)
		free(expanded);
}

void	here_doc(t_tokens **current, t_tokens **executable,
	t_hash_table *env, t_stat *stat)
{
	pid_t		pid;

	if (!setup_heredoc(executable, stat))
		return ;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_heredoc);
		rl_catch_signals = 0;
		here_doc_loop(current, executable, env, stat);
		if (stat->here_doc_fd != -1)
			close(stat->here_doc_fd);
		exit(0);
	}
	finish_heredoc(executable, pid, stat);
	stat->here_doc_fd = -1;
	stat->line_num = 1;
	stat->here_doc_index = 0;
}
