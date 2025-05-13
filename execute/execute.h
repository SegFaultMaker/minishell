/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:44:26 by armarake          #+#    #+#             */
/*   Updated: 2025/05/13 16:47:26 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../libft/libft.h"
# include "../minishell.h"
# include "../builtins/builtins.h"
# include "../environment/environment.h"

//			no pipes
int		execute_command_no_pipes(t_tokens *cmd, t_hash_table *env);

//			handle redirs

//			utils
char	**tokens_to_strings(t_tokens *cmd);
int 	check_pipes(t_tokens *tokens);
int		quit_with_error(char *msg, int stat);
int		define_type(t_tokens *tokens);

#endif
