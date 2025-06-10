/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:29:49 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/10 12:47:36 by nasargsy         ###   ########.fr       */
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

int	get_last_stat(pid_t pid, int last_is_binary, int count, int last_stat)
{
	int	res;

	res = last_stat;
	if (last_is_binary)
		waitpid(pid, &res, 0);
	while (count)
	{
		wait(NULL);
		count--;
	}
	return (res);
}
