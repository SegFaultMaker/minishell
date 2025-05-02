/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:20:01 by armarake          #+#    #+#             */
/*   Updated: 2025/05/02 13:57:37 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

static int	is_prime(int nb)
{
	int	i;

	if (nb <= 1)
		return (0);
	i = 2;
	while (i < nb)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int	next_prime(int nb)
{
	int	i;

	i = 0;
	while (1)
	{
		if (is_prime(nb + i) == 1)
			return (nb + i);
		i++;
	}
}

void	set_nulls(t_hash_table	*ht)
{
	int	i;

	i = 0;
	while (i < ht->size)
	{
		ht->items[i] = NULL;
		i++;
	}
}
