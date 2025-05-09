/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:22:21 by armarake          #+#    #+#             */
/*   Updated: 2025/05/04 14:36:19 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	ht_del_item(t_ht_item *item)
{
	free(item->key);
	free(item->value);
	free(item);
}

void	del_hash_table(t_hash_table *ht)
{
	int			i;
	t_ht_item	*item;

	i = 0;
	while (i < ht->size)
	{
		item = ht->items[i];
		if (item != NULL && item != ht->deleted)
			ht_del_item(item);
		i++;
	}
	free(ht->deleted);
	free(ht->items);
	free(ht);
}
