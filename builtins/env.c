/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:54:23 by armarake          #+#    #+#             */
/*   Updated: 2025/05/04 20:07:29 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env(t_hash_table *ht)
{
	int		i;
	char	**result;

	i = 0;
	result = ht_to_strings(ht);
	if (!result)
		return (1);
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	free_result(result);
	return (0);
}
