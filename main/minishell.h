/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:33:19 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/06 16:13:50 by nasargsy         ###   ########.fr       */
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
# define RESET "\001\e[0m\002"
# define BOLD "\001\e[1m\002"

# define BREAK_LOOP 1
# define CONTINUE_LOOP 2

typedef struct s_tokens t_tokens;

//				Init
void		init_signals(void);

//				Shell
void		start_shell(t_hash_table *environment);

//				Execution
int			execute(t_tokens *tokens, t_hash_table *env, int stat);

//				Utils
char		*read_input(void);
int			check_input(char **input);
int			handle_input(t_tokens **cmd, t_hash_table *envp,
				char **input, int stat);
#endif
