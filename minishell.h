/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:33:19 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/30 18:00:06 by nasargsy         ###   ########.fr       */
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
	FILE_NAME
}	t_types;

typedef struct s_tokens
{
	char			*token;
	t_types			type;			
	struct s_tokens	*next;
}	t_tokens;

// Init
void		init_signals(void);

// Parser
t_tokens	*parser(char *str);
t_tokens	*new_token(char *content);
t_tokens	*handle_redir_pipe(t_tokens **tokens);
void		assign_types(t_tokens **tokens);
void		free_tokens(t_tokens **tokens);
int			ft_isquote(char c);

// Builtins
int			echo(int argc, char	**argv);
int			cd(char *path);
int			pwd(void);

#endif
