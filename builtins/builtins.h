/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:46:56 by armarake          #+#    #+#             */
/*   Updated: 2025/06/09 12:42:34 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "../main/minishell.h"
# include "../execute/execute.h"
# include "../parser/parser.h"
# include "../environment/environment.h"

# define ADD_MODE INT_MAX
# define JOIN_MODE INT_MIN

//			enviroment
int		export(t_tokens *tokens, t_hash_table *ht);
int		env(t_hash_table *ht, int mode);
int		unset(t_tokens *tokens, t_hash_table *ht);

//			other
int		cd(t_tokens *tokens, t_hash_table *ht);
int		echo(t_tokens *tokens);
int		pwd(t_hash_table *envp);
int		exit_builtin(t_tokens *tmp, int prev_stat);

//			utils
char	*get_key_end(char *arg, int mode);
char	*get_key(char *arg, char *key_end);
void	free_key_value(char *key, char *value, char *existing, int mode);

#endif
