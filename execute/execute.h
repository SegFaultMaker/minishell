/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:44:26 by armarake          #+#    #+#             */
/*   Updated: 2025/06/06 23:10:32 by armarake         ###   ########.fr       */
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
# include "../parser/parser.h"

# define BREAK_REDIR_LOOP 1
# define CONTINUE_REDIR_LOOP 2
# define RETURN_FROM_FUNCTION 3

//				executes
int			handle_binary(t_tokens *cmd, t_hash_table *env);
int			handle_builtin(t_tokens *tokens, t_hash_table *envp);

//				handle redirs
void		undo_builtin_redirs(int saved_in, int saved_out);
int			except_here_doc(t_tokens *tokens, int *saved_in, int *saved_out);
int			open_infile(char *filename);
int			open_outfile(char *filename, int mode);
void		here_doc(t_tokens *tokens, int fd);

//				handle tokens redirs
int			handle_input_redir(t_tokens **current, t_tokens **executable);
int			handle_output_redir(t_tokens **current, t_tokens **executable);
void		handle_pipe_redir
(t_tokens **current, t_tokens **executable, int **pipe_fds, int *i);

//				utils
char		**tokens_to_strings(t_tokens *cmd);
int			check_pipes(t_tokens *tokens);
int			quit_with_error(int flag, char *target, char *description, int stat);
void		free_matrix(char **matrix);
char		*find_cmd(char *cmd, char **envp);
t_tokens	*find_executable(t_tokens *current);

#endif
