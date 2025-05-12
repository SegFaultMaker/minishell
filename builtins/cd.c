/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:12:16 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/12 15:17:54 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd(t_tokens *tmp, t_hash_table *env)
{
	char	*path;

	path = tmp->token;
	if (!path || !*path)
		return (0);
	if (!ft_strcmp(path, "-"))
	{
		path = ht_search(env, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
			return (1);
		}
		if (chdir(path) == -1)
			return (1);
	}
	else
	{
		if (chdir(path) == -1)
			return (1);
	}
	return (0);
}
