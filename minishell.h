#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include "./libft/libft.h"

typedef struct s_tokens
{
	char						*token;
	struct s_tokens	*next;
}	t_tokens;

#endif
