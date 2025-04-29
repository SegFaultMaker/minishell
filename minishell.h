/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:33:19 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/29 13:35:42 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef struct s_tokens
{
	char			*token;
	struct s_tokens	*next;
}	t_tokens;

// Parser
t_tokens	*parser(char *str);
t_tokens	*new_token(char *content);
void		free_tokens(t_tokens **tokens);

// Builtins
int			echo(int argc, char	**argv);
int			cd(char *path);
int			pwd(void);

#endif
