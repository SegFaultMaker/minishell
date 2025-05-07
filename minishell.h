/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:33:19 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/07 13:41:19 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

// Error MSGs
# define SYNTAX_ERR "minishell: syntax error near unexpected token "

typedef enum e_types
{
	BUILTIN,
	COMMAND,
	ARGUMENT,
	PIPE,
	INPUT,
	OUTPUT,
	HERE_DOC,
	APPEND,
	FILE_NAME,
	LIMITER,
	OPERATOR
}	t_types;

typedef struct s_tokens
{
	char			*token;
	t_types			type;			
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_commands
{
	t_tokens			*first;
	t_tokens			*second;
	struct s_commands	*next;
}	t_commands;

// Init
void		init_signals(void);

// Shell
void		start_shell(void);

// Parser
void		clean_commands(t_commands **commands);
t_tokens	*parser(char *str);
t_tokens	*new_token(char *content);
void		assign_types(t_tokens **tokens);
void		free_tokens(t_tokens **tokens);
int			syntax_check(t_tokens *tmp);
int			ft_isquote(char c);
int			check_redir_pipe_operator(char *token, int regime);
int			is_redir_pipe(t_types type);

// Builtins
int			echo(int argc, char	**argv);
int			cd(char *path);
int			pwd(void);

// Utils
void		quit_with_error(int code, char *msg);

#endif
