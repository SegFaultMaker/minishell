/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:21:37 by armarake          #+#    #+#             */
/*   Updated: 2025/05/02 13:25:09 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

t_ht_item	*ht_new_item(char *k, char *v)
{
	t_ht_item *item = malloc(sizeof(t_ht_item));
	item->key = ft_strdup(k);
	item->value = ft_strdup(v);
	if (!item->key || !item->value)
		return (NULL);
	return (item);
}

static t_ht_item	*ht_deleted(void)
{
	t_ht_item *deleted = malloc(sizeof(t_ht_item));
	if (!deleted)
		return (NULL);
	deleted->key = NULL;
	deleted->value = NULL;
	return (deleted);
}

t_hash_table	*ht_new(int base_size)
{
	t_hash_table	*ht;
	
	ht = malloc(sizeof(t_hash_table));
	if (!ht)
		return (NULL);
	ht->base_size = base_size;
	ht->size = next_prime(ht->base_size);
	ht->count = 0;
	ht->deleted = ht_deleted();
	if (!ht->deleted)
		return (NULL);
	ht->items = malloc(ht->size * sizeof(t_ht_item *));
	if (!ht->items)
		return (NULL);
	set_nulls(ht);
	return (ht);
}
