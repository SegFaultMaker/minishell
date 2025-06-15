/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:44:26 by armarake          #+#    #+#             */
/*   Updated: 2025/06/15 23:28:23 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <sys/wait.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "../main/minishell.h"
# include "../expand/expand.h"
# include "../builtins/builtins.h"
# include "../environment/environment.h"
# include "../parser/parser.h"

# define CONTINUE_THE_LOOP 1

//				handlers
pid_t		handle_binary(t_tokens *cmd, t_hash_table *env,
				t_stat *stat_struct);
pid_t		builtin_in_fork(t_tokens *tokens, t_hash_table *envp,
				t_stat *stat_struct);
void		handle_builtin(t_tokens *tokens, t_hash_table *envp,
				t_stat *stat_struct);

//				random redirs
void		undo_builtin_redirs(int saved_in, int saved_out);
void		here_doc(t_tokens *tokens, int fd);

//				handle tokens redirs
int			handle_input_redir(t_tokens **current, t_tokens **executable);
int			handle_output_redir(t_tokens **current, t_tokens **executable);
void		handle_pipe_redir(t_tokens **current, t_tokens **executable,
				int **pipe_fds, int *i);
void		free_pipes(int ***array);
int			**allocate_pipe_fds(int pipe_count);

//				file open
int			open_infile(char *filename);
int			open_outfile(char *filename, int mode);

//				utils
char		**tokens_to_strings(t_tokens *cmd);
int			check_pipes(t_tokens *tokens);
int			quit_with_error(int flag, char *target, char *description,
				int stat);
int			get_last_stat(t_stat *stat_struct);
void		free_matrix(char **matrix);
char		*find_cmd(char *cmd, char **envp);
t_tokens	*find_executable(t_tokens *current);
void		dup_and_close(t_tokens *tokens, t_stat *stat_struct);

#endif
