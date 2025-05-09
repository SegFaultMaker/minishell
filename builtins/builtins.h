/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:46:56 by armarake          #+#    #+#             */
/*   Updated: 2025/05/09 16:15:13 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "../minishell.h"
# include "../environment/environment.h"

# define ADD_MODE 1
# define JOIN_MODE 2

//			enviroment
int		export(int argc, char *argv[], t_hash_table *ht);
int		env(t_hash_table *ht, int mode);
int		unset(char *argv[], t_hash_table *ht);

//			other
int		cd(char *path);
int		echo(t_tokens *tokens);
int		pwd(void);

//			utils
void	invalid_identifier(char *arg);
char	*no_free_strjoin(char *s1, char *s2);
char	*get_key_end(char *arg, int mode);
char	*get_key(char *arg, char *key_end);
void	free_key_value(char *key, char *value, char *existing, int mode);

#endif
