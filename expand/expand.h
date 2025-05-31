/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:15:19 by armarake          #+#    #+#             */
/*   Updated: 2025/05/31 16:55:46 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../libft/libft.h"
# include "../main/minishell.h"
# include "../builtins/builtins.h"
# include "../environment/environment.h"

typedef struct s_data
{
	int		i;
	int		j;
	int		len;
	int		stat;
	int		quote;
	char	*token;
}	t_data;

//			Expand
void	expand_tokens(t_tokens **tokens, t_hash_table *env, int stat);

//			Expand utils
char	*find_var(char *str, t_hash_table *env);
int		safe_strlen(char *str);
int		quote_start(char *token, int *quote, int *i);
int		quote_end(char *token, int *quote, int *i);

//			Final len utils
int		dollar_question_mark_len(int *i, int stat);
int		env_var_len(char *token, int *i, t_hash_table *env);
int		initialize_vars(int *i, int *quote, int *final_len, char *token);

//			Build utils
void	handle_dollar_question_mark(char **result, int *i, int *j, int stat);
void	handle_env_var(char **result, t_data *data, t_hash_table *env);
t_data	*init_data(char *token, int stat);

#endif
