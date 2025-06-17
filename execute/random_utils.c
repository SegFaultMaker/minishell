/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:29:49 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/17 12:19:54 by nasargsy         ###   ########.fr       */
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
