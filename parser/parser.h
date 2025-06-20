/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:42:02 by armarake          #+#    #+#             */
/*   Updated: 2025/06/20 17:26:25 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "../main/minishell.h"

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
	NEWL
}	t_types;

typedef struct s_tokens
{
	char			*token;
	t_types			type;
	int				input;
	int				output;
	bool			input_is_heredoc;
	bool			execute;
	struct s_tokens	*next;
}	t_tokens;

//				Parser
t_tokens	*parser(char *str);
t_tokens	*new_token(char *content);
t_types		get_type(char *token);
void		assign_types(t_tokens **tokens);
void		free_tokens(t_tokens **tokens);
int			syntax_check(t_tokens *tmp);
int			ft_isquote(char c);
int			check_redir_pipe_operator(char *token, int regime);
int			is_redir_pipe(t_types type);

#endif
