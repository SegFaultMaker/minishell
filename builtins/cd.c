/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:12:16 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/27 16:55:48 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd(t_tokens *tmp, t_hash_table *env)
{
	char	*new;
	char	*current;

	new = tmp->token;
	if (!new || !*new)
		return (0);
	current = ht_search(env, "PWD");
	if (!current)
		return (quit_with_error(1, "cd", "PWD not set", 1));
	if (chdir(new) == -1)
		return (quit_with_error(1, "cd", NULL, 1));
	new = getcwd(NULL, 0);
	if (!new || !*new)
		return (0);
	ht_insert(env, "OLDPWD", current);
	ht_insert(env, "PWD", new);
	free(new);
	return (0);
}
