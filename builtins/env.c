/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:23 by armarake          #+#    #+#             */
/*   Updated: 2025/06/19 11:36:30 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env(t_hash_table *ht, int mode)
{
	int		i;
	char	**result;

	i = 0;
	result = ht_to_strings(ht, mode);
	if (!result)
		return (1);
	while (result[i])
	{
		if (mode)
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(result[i], STDOUT_FILENO);
		i++;
	}
	free_result(&result);
	return (0);
}
