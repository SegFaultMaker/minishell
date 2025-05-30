/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:44:26 by armarake          #+#    #+#             */
/*   Updated: 2025/05/30 20:57:04 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <sys/wait.h>
# include "../libft/libft.h"
# include "../main/minishell.h"
# include "../expand/expand.h"
# include "../builtins/builtins.h"
# include "../environment/environment.h"

//			executes
int		execute_no_pipes(t_tokens *cmd, t_hash_table *env);
int		execute_with_pipes(t_tokens *tokens, t_hash_table *envp);

//			handle redirs
int		do_redir(t_tokens *tokens, int *saved_in, int *saved_out);
void	undo_redir(int saved_in, int saved_out);
int		except_here_doc(t_tokens *tokens, int *saved_in, int *saved_out);
int		open_infile(char *filename);
int		open_outfile(char *filename, int mode);
void	here_doc(t_tokens *tokens);

//			utils
char	**tokens_to_strings(t_tokens *cmd);
int		check_pipes(t_tokens *tokens);
int		quit_with_error(int flag, char *target, char *description, int stat);
int		define_type(t_tokens *tokens);
void	free_matrix(char **matrix);
char	*find_cmd(char *cmd, char **envp);
int		get_commands(t_tokens *tokens);
char	***get_argvs(t_tokens *tokens, int i);

#endif
