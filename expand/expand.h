/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:15:19 by armarake          #+#    #+#             */
/*   Updated: 2025/05/30 21:57:47 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../libft/libft.h"
# include "../main/minishell.h"
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
int		quote_handle(t_tokens **tokens, t_hash_table *env, int stat, int index);
int		must_expand(char *str, int start, int end, int *doll_pos);
int		find_new_end(char *str, int start, char quote);
void	remove_quote_helper(char *str, char quote, char **new, int len);

#endif
