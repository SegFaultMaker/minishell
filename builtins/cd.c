/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:12:16 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/11 17:05:21 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd(t_tokens *tmp, t_hash_table *env)
{
	char	*new;
	char	*current;

	if (argument_count(tmp) > 1)
		return (quit_with_error(1, "cd", "too many arguments", 1));
	tmp = find_argument(tmp);
	if (!tmp)
		return (0);
	new = tmp->token;
	current = ht_search(env, "PWD");
	if (!current)
		return (quit_with_error(1, "cd", "PWD not set", 1));
	if (chdir(new) == -1)
		return (quit_with_error(1, "cd", NULL, errno), 1);
	new = getcwd(NULL, 0);
	if (!new || !*new)
		return (0);
	ht_insert(env, "OLDPWD", current);
	return (ht_insert(env, "PWD", new), free(new), 0);
}
