/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:16:46 by armarake          #+#    #+#             */
/*   Updated: 2025/05/10 17:11:56 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	unset(t_tokens *tokens, t_hash_table *ht)
{
	while (tokens && !is_redir_pipe(tokens->type) && tokens->type != NEWL)
	{
		ht_delete(ht, tokens->token);
		tokens = tokens->next;
	}
	return (0);
}

// int	main(int argc, char *argv[], char *envp[])
//  {
//  	char			*line;
// 	t_tokens		*tokens;
// 	t_hash_table	*ht;

// 	(void)argc;
// 	(void)argv;
//  	line = readline("$ ");
//  	tokens = parser(line);
// 	ht = init_environment(envp);
//  	unset(tokens, ht);
// 	ft_printf("\n\n");
// 	env(ht, 0);
//  	free(line);
// 	del_hash_table(ht);
//  	free_tokens(&tokens);
//  }
