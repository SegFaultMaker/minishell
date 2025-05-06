/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:16:46 by armarake          #+#    #+#             */
/*   Updated: 2025/05/06 18:55:40 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	unset(int argc, char *argv[], t_hash_table *ht)
{
	int	i;

	if (argc == 1)
		return (0);
	i = 1;
	while (argv[i])
	{
		ht_delete(ht, argv[i]);
		i++;
	}
	return (0);
}
