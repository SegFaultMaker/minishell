/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:26:17 by armarake          #+#    #+#             */
/*   Updated: 2025/05/03 18:20:20 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

static void	swap_attributes(t_hash_table *ht, t_hash_table *new_ht)
{
	int				tmp_size;
	t_ht_item		**tmp_items;

	tmp_size = ht->size;
	ht->size = new_ht->size;
	new_ht->size = tmp_size;
	tmp_items = ht->items;
	ht->items = new_ht->items;
	new_ht->items = tmp_items;
}

static void	ht_resize(t_hash_table *ht, int base_size)
{
	int				i;
	t_ht_item		*item;
	t_hash_table	*new_ht;

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
	swap_attributes(ht, new_ht);
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
