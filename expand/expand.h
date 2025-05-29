/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:15:19 by armarake          #+#    #+#             */
/*   Updated: 2025/05/30 00:12:54 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../libft/libft.h"
# include "../minishell.h"
# include "../builtins/builtins.h"
# include "../environment/environment.h"

# define QUOTE_HANDLE 1
# define ENV_VAR_HANDLE 2

//			Env vars
void	dollar_question_mark(t_tokens **tokens, int doll_pos, int stat);
void	regular(t_tokens **tokens, t_hash_table *env, int doll_pos);
void	expand_tokens(t_tokens **tokens, t_hash_table *env, int stat);
void	add_the_rest(t_tokens **tokens, int doll_pos, char **new, int start);
int		safe_strlen(char *str);
int		calculate_len(char *old, int doll_pos, char *env_var, int *flag);
int		the_rest_len(char *old_token, int start);

//			Quotes
int	handle_token(t_tokens **tokens, t_hash_table *env, int stat, int index);

#endif
