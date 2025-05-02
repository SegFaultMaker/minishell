/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:26:17 by armarake          #+#    #+#             */
/*   Updated: 2025/05/02 13:42:26 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

static void	ht_resize(t_hash_table *ht, int base_size)
{
	int				i;
	int				tmp_size;
	t_ht_item		*item;
	t_hash_table	*new_ht;
	t_ht_item		**tmp_items;

	if (base_size < HT_DEFAULT_BASE_SIZE)
		return ;
	i = 0;
	new_ht = ht_new(base_size);
	while (i < ht->size)
	{
		item = ht->items[i];
		if (item != NULL && item != ht->deleted)
			ht_insert(new_ht, item->key, item->value);
		i++;
	}
	ht->base_size = new_ht->base_size;
	ht->count = new_ht->count;
	// swapping attributes (move to separate function)
	tmp_size = ht->size;
	ht->size = new_ht->size;
	new_ht->size = tmp_size;
	tmp_items = ht->items;
	ht->items = new_ht->items;
	new_ht->items = tmp_items;
	del_hash_table(new_ht);
}

void	ht_resize_up(t_hash_table *ht)
{
	int	new_size;
	
	new_size = ht->base_size * 2;
	ht_resize(ht, new_size);
}

void	ht_resize_down(t_hash_table *ht)
{
	int	new_size;
	
	new_size = ht->base_size / 2;
	ht_resize(ht, new_size);
}
