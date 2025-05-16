/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:44:26 by armarake          #+#    #+#             */
/*   Updated: 2025/05/16 13:40:57 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <sys/wait.h>
# include "../libft/libft.h"
# include "../minishell.h"
# include "../builtins/builtins.h"
# include "../environment/environment.h"

//			no pipes
int		execute_command_no_pipes(t_tokens *cmd, t_hash_table *env);

//			handle redirs
int		do_redir(t_tokens *tokens, int *saved_in, int *saved_out);
void	undo_redir(int saved_in, int saved_out);

//			utils
char	**tokens_to_strings(t_tokens *cmd);
int 	check_pipes(t_tokens *tokens);
int		quit_with_error(int flag, char *target, int stat);
int		define_type(t_tokens *tokens);
void	free_matrix(char ***matrix);
char	*find_cmd(char *cmd, char **envp);

#endif
