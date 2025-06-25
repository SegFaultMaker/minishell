/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:33:19 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/25 19:55:12 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <termios.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../environment/environment.h"
# include "../parser/parser.h"

//			Error MSGs
# define SYNTAX_ERR "minishell: syntax error near unexpected token "

//			Colors
# define BLUE "\001\e[1;36m\002"
# define GREEN "\001\e[1;32m\002"
# define RED "\001\e[1;31m\002"
# define RESET "\001\e[0m\002"
# define BOLD "\001\e[1m\002"

# define BREAK_LOOP 1
# define CONTINUE_LOOP 2

typedef struct s_tokens	t_tokens;

typedef struct s_status
{
	int		stat;
	int		here_doc_fd;
	int		here_doc_index;
	int		line_num;
	int		pipe_count;
	int		**pipe_fds;
	char	**argv;
	char	**envp;
	char	*path;
	bool	last_in_fork;
	bool	must_exit;
	pid_t	pid;

}	t_stat;

//				Signals
void		init_signals(void);
void		sig_handle_exec(int sig);
void		sigint_heredoc(int sig);

//				Execution
void		execute(t_tokens *tokens, t_hash_table *env, t_stat *stat_struct);

//				Utils
char		*read_input(void);
int			check_input(char **input);
void		handle_input(t_tokens **cmd, t_hash_table *envp,
				char **input, t_stat *stat_struct);

#endif
