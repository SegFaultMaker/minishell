/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:12:16 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/18 16:01:42 by armarake         ###   ########.fr       */
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
		return (errno = 1, quit_with_error(1, "cd", "PWD not set", errno));
	if (!ft_strcmp(new, "-"))
	{
		new = ht_search(env, "OLDPWD");
		if (!new)
			return (errno = 1,
				quit_with_error(1, "cd", "OLDPWD not set", errno));
	}
	if (chdir(new) == -1)
		return (quit_with_error(1, "cd", NULL, errno));
	ht_insert(env, "OLDPWD", current);
	ht_insert(env, "PWD", new);
	return (0);
}
