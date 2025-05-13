/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:33:19 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/13 16:06:45 by armarake         ###   ########.fr       */
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
# include "./environment/environment.h"

// Error MSGs
# define SYNTAX_ERR "minishell: syntax error near unexpected token "

// Colors
# define BLUE "\001\e[1;36m\002"
# define PURPLE "\001\e[1;35m\002"
# define RESET "\001\e[0m\002"
# define BOLD "\001\e[1m\002"

typedef enum e_types
{
	NONE,
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
	OPERATOR,
	NEWL
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
void		start_shell(t_hash_table *environment);

// Execution
int	execute(t_tokens *tokens, t_hash_table *env, int stat);

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
t_types		get_type(char *token);
t_tokens	*handle_first(t_tokens **tokens);

#endif
