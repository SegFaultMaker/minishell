/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:42:02 by armarake          #+#    #+#             */
/*   Updated: 2025/04/30 18:37:30 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

void 	ht_insert(t_hash_table *ht, char *key, char *value) // TODO with resize
{
	int			i;
	int			index;
	t_ht_item	*item;
	t_ht_item	*cur_item;

	i = 1;
	item = ht_new_item(key, value);
	index = ht_get_hash(item->key, ht->size, 0);
	cur_item = ht->items[index];
	// while (cur_item != NULL && cur_item != ht->deleted)
	// {
	// 	index = ht_get_hash(item->key, ht->size, i);
	// 	cur_item = ht->items[index];
	// 	i++;
	// }
	ht->items[index] = item;
	ht->count++;
}

char	*ht_search(t_hash_table *ht, char *key)
{
	int			i;
	int			index;
	t_ht_item	*item;
	
	i = 1;
	index = ht_get_hash(key, ht->size, 0);
	item = ht->items[index];
	while (item != NULL)
	{
		if (item != ht->deleted)
		{
			if (ft_strcmp(item->key, key) == 0)
				return (item->value);
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		i++;
	}
	return (NULL);
}

void 	ht_delete(t_hash_table *ht, char *key)
{
	int			i;
	int			index;
	t_ht_item	*item;

	i = 1;
	index = ht_get_hash(key, ht->size, 0);
	item = ht->items[index];
	while (item != NULL)
	{
		if (item != ht->deleted)
		{
			if (ft_strcmp(item->key, key) == 0)
			{
				ht_del_item(item);
				ht->items[index] = ht->deleted;
			}
		}
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		i++;
	}
	ht->count--;
}


